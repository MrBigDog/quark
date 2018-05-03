
#include "ring_buffer.h"
#include <errno.h>

bool ring_buffer_init(ring_buffer_t * ring , size_t size)
{
    ::memset(ring , 0 , sizeof(ring_buffer_t)) ;
    char * buffer = (char *)::malloc(size) ;
    if(buffer == NULL)
    {
        errno = ENOMEM ;
        return false ;
    }

    ring->buffer = buffer ;
    ring->bufsize = size ;
    return true ;
}

bool ring_buffer_final(ring_buffer_t * ring)
{
    if(ring == NULL)
        return false ;

    char * buffer = ring->buffer ;
    ring->buffer = NULL ;
    if(buffer != NULL)
        ::free(buffer) ;
    ::free(ring) ;
    return true ;
}

size_t ring_buffer_write_stream(ring_buffer_t * ring , const void * buf , size_t size)
{
    size_t head = ring->head , tail = ring->tail , bufsize = ring->bufsize;
    size_t left_size = 0 ;
    if(head >= tail)
        left_size = bufsize + tail - head ;
    else
        left_size = tail - head ;
    --left_size ;

    size_t copy_size = (left_size >= size)? size : left_size ;
    if(head > tail)
    {
        //β�����ƣ�ֱ�Ӵ�tail����head
        ::memcpy(ring->buffer + tail , buf , copy_size) ;
        ring->tail += copy_size ;
    }
    else
    {
        //�ֶο���
        size_t cont_size = bufsize - tail ;
        if(cont_size > copy_size)
            cont_size = copy_size ;
        ::memcpy(ring->buffer + tail , buf , cont_size) ;
        size_t broken_size = copy_size - cont_size ;
        if(broken_size > 0)
        {
            ::memcpy(ring->buffer , (const char *)buf + cont_size , broken_size) ;
            ring->tail = broken_size ;
        }
        else
        {
            ring->tail += cont_size ;
        }
    }

    return copy_size ;
}

bool ring_buffer_refer_stream(ring_buffer_t * ring , char *&buf , size_t& size)
{
    if(ring->head <= ring->tail)
    {
        size = ring->tail - ring->head ;
        buf = ring->buffer + ring->head ;
        return true ;
    }

    size = ring->bufsize - ring->head ;
    buf = ring->buffer + ring->head ;
    return true ;
}

size_t ring_buffer_write_message(ring_buffer_t * ring , const void * buf , size_t size)
{    
    if(buf == NULL || size == 0 || size >= 0xFFFF)
        return -1 ;

    size_t head = ring->head , tail = ring->tail , bufsize = ring->bufsize;
    size_t left_size = bufsize - tail ;
    if(left_size < size + 4)
    {
        //ʣ��ռ䲻�㣬�����Ի��ƣ��������׳����⡣
        //ֻ�������е���Ϣ�����ͳ�ȥ������ƫ����
        if(head != tail)
            return -1 ;
        head = tail = 0 ;
        left_size = ring->bufsize ;
    }

    char * buffer = ring->buffer + tail ;
    buffer[0] = 0x55 ;
    buffer[1] = 0x55 ;
    ::memcpy(buffer + 2 , &size , 2) ;
    ::memcpy(buffer + 4 , buf , size) ;

    size_t copy_size = size + 4 ;
    ring->tail += copy_size ;
    return copy_size ;
}

bool ring_buffer_refer_message(ring_buffer_t * ring , char *&buf , size_t& size)
{
    size_t head = ring->head , tail = ring->tail , bufsize = ring->bufsize ;
    if(head == tail)
    {
        //�յ�
        buf = NULL ;
        size = 0 ;
        return true ;
    }

    char * buffer = ring->buffer;
    size_t magic_size = 0 , idx = head;

    for(; idx < tail ; ++idx)
    {
        char ch = buffer[idx] ;
        if(ch == 0x55)
            ++magic_size ;
        else if(magic_size != 0)
            magic_size = 0 ;

        if(magic_size == 2)
            break ;
    }
    if(magic_size != 2)
    {
        ring->head = tail ;
        return false ;
    }

    size_t msg_size = 0 ;
    ::memcpy(&msg_size , buffer + idx , 2) ;
    if((idx + 2 + msg_size) > tail)
    {
        ring->head = idx ;  //�Թ�ħ�����������Ϣ��������
        idx -= 2 ;
        buffer[idx] = -1 ;    //���ħ��������������±���λ
        buffer[idx+1] = -1 ;
        return false ;
    }

    buf = buffer + idx + 2 ;
    size = msg_size ;   
    return true ;
}

bool ring_buffer_move_size(ring_buffer_t * ring , size_t size)
{
    size_t head = ring->head + size ;
    if(head >= ring->bufsize)
        head -= ring->bufsize ;

    ring->head = head ;
    return true ;
}

