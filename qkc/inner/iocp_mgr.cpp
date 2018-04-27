
#include "iocp_mgr.h"
#include <errno.h>
#include <wintf/wobj.h>
#include <windows.h>
#include <sys/socket.h>

int iocp_mgr_new()
{
    iocp_mgr_t * mgr = (iocp_mgr_t *)::malloc(sizeof(iocp_mgr_t)) ;
    if(mgr == NULL)
    {
        errno = ENOMEM ;
        return -1 ;
    }

    if(iocp_mgr_init(mgr) == false)
    {
        ::free(mgr) ;
        return -1 ;
    }

    int epfd = wobj_set(WOBJ_IOCP , mgr->iocp , mgr) ;
    if(epfd == INVALID_WOBJ_ID)
        return -1 ;
    mgr->epfd = epfd ;
    return epfd ;
}

int iocp_mgr_free(iocp_mgr_t * mgr)
{
    if(mgr == NULL)
        return -1 ;

    int oid = mgr->epfd ;
    iocp_mgr_final(mgr) ;
    wobj_del(oid) ;
    ::free(mgr) ;
    return 0 ;
}

bool iocp_mgr_init(iocp_mgr_t * mgr)
{
    if(mgr == NULL)
        return false ;
    ::memset(mgr , 0 , sizeof(iocp_mgr_t)) ;
    mgr->iocp = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE , NULL , 0 , 0) ;
    if(mgr->iocp == INVALID_HANDLE_VALUE)
    {
        errno = EIO ;
        return false ;
    }

    mgr->locker = ::CreateMutex(NULL , FALSE , NULL) ;

    rlist_init(&mgr->ready) ;
    //rlist_init(&mgr->monitored) ;

    return true ;
}

bool iocp_mgr_final(iocp_mgr_t * mgr)
{
    if(mgr == NULL)
        return false ;
   
    ::WaitForSingleObject(mgr->locker , INFINITE) ;
    //iocp_mgr_items_free(&mgr->monitored) ;
    iocp_mgr_items_free(&mgr->ready) ;

    if(mgr->iocp != INVALID_HANDLE_VALUE)
    {
        ::CloseHandle(mgr->iocp) ;
        mgr->iocp = INVALID_HANDLE_VALUE ;
    }

    ::ReleaseMutex(mgr->locker) ;
    ::CloseHandle(mgr->locker) ;

    ::memset(mgr , 0 , sizeof(iocp_mgr_t)) ;
    return true ;
}

bool iocp_mgr_items_free(rlist_t * rlist) 
{
    if(rlist == NULL)
        return false ;
    rlist_t * next = NULL ;
    while((next = rlist->next) != rlist)
    {
        rlist_del(rlist , next) ;
        iocp_mgr_item_free((iocp_item_t *)next) ;
    }
    return true ;
}

bool iocp_mgr_item_free(iocp_item_t * item) 
{
    rlist_del(NULL , &item->link) ;

    socket_t * s = item->socket ;
    item->socket = NULL ;
    s->addition = NULL ;
    s->callback = NULL ;
    
    free(item) ;
    return true ;
}

bool iocp_mgr_item_ready(iocp_mgr_t * mgr , iocp_item_t * item) 
{
    if(mgr == NULL || item == NULL)
        return false ;

    ::WaitForSingleObject(mgr->locker , INFINITE) ;

    if(rlist_empty(&item->link) == true && item->occur != 0)
    {
        rlist_add_tail(&mgr->ready , &item->link) ;
    }

    ::ReleaseMutex(mgr->locker) ;
    return true ;
}

bool iocp_mgr_item_unready(iocp_mgr_t * mgr , iocp_item_t * item) 
{
    if(mgr == NULL || item == NULL)
        return false ;

    ::WaitForSingleObject(mgr->locker , INFINITE) ;

    if(rlist_empty(&item->link) == false && item->occur == 0)
    {
        rlist_del(NULL , &item->link) ;
    }

    ::ReleaseMutex(mgr->locker) ;
    return true ;
}

bool iocp_mgr_add(iocp_mgr_t * mgr , socket_t * s , struct epoll_event * ev)
{
    if(mgr == NULL || s == NULL || ev == NULL)
        return false ;

    iocp_item_t * item = (iocp_item_t *)::malloc(sizeof(iocp_item_t)) ;
    if(item == NULL)
        return false ;
    ::memset(item , 0 , sizeof(iocp_item_t)) ;

    item->socket = s ;
    item->owner = mgr ;
    rlist_init(&item->link) ;
    ::memcpy(&item->data , ev , sizeof(struct epoll_event)) ;

    s->addition = item ;
    s->callback = iocp_socket_callback ;

    //绑定到iocp中
    if(::CreateIoCompletionPort((HANDLE)s->socket , mgr->iocp , 0 , 0) == NULL)
        return false ;

    if((ev->events & EPOLLIN) == EPOLLIN)
    {
        if(s->stage == SOCKET_STAGE_LISTEN)
            socket_start_accept(s->acceptor) ;
        else if(s->stage == SOCKET_STAGE_CONNECT && s->type == SOCK_STREAM)
            ::socket_start_recv(s->receiver) ;
        else if(s->type == SOCK_DGRAM)
        {
            struct sockaddr addr ;
            int addr_len = sizeof(struct sockaddr) ;
            ::socket_start_recvfrom(s->receiver , 0 , &addr , &addr_len) ;
        }
    }

    return true ;
}

bool iocp_mgr_mod(iocp_mgr_t * mgr , socket_t * s , struct epoll_event * ev)
{
    if(mgr == NULL || s == NULL || ev == NULL || s->addition == NULL)
        return false ;

    iocp_item_t * item = (iocp_item_t *)s->addition ;
    if(item->socket != s)
        return false ;

    ::WaitForSingleObject(mgr->locker , INFINITE) ;
    rlist_del(NULL , &item->link) ;
    ::memcpy(&item->data , ev , sizeof(struct epoll_event)) ;
    ::ReleaseMutex(mgr->locker) ;
    
    return true ;
}

bool iocp_mgr_del(iocp_mgr_t * mgr , socket_t * s , struct epoll_event * ev)
{
    if(mgr == NULL || s == NULL || ev == NULL || s->addition == NULL)
        return false ;

    iocp_item_t * item = (iocp_item_t *)s->addition ;
    s->addition = NULL ;
    s->callback = NULL ;
    item->socket = NULL ;

    ::WaitForSingleObject(mgr->locker , INFINITE) ;
    rlist_del(NULL , &item->link) ;
    iocp_mgr_item_free(item) ;
    ::ReleaseMutex(mgr->locker) ;

    return true ;
}

int iocp_mgr_wait(iocp_mgr_t * mgr , int timeout) 
{
    DWORD start_time = ::GetTickCount() ;
    DWORD bytes_transferred = 0 ;
    ULONG_PTR completion_key = 0 ;
    LPOVERLAPPED overlapped = NULL ;
    
    ::InterlockedIncrement(&mgr->thread_counter) ;
    BOOL result = ::GetQueuedCompletionStatus(mgr->iocp , &bytes_transferred , &completion_key , &overlapped , timeout) ;
    LONG now_threads =  ::InterlockedDecrement(&mgr->thread_counter) ;
    if(result == TRUE)
    {
        if(overlapped == NULL && completion_key == 1)
        {
            if(now_threads > 0)
                ::PostQueuedCompletionStatus(mgr->iocp , 0 , completion_key , NULL) ;
            return 0 ;
        }

        socket_ovlp_t * ovlp = (socket_ovlp_t *)overlapped ;
        socket_t * owner = ovlp->owner ;
        iocp_item_t * item = NULL ;
        if(owner != NULL)
            item = (iocp_item_t *)owner->addition ;

        bool ready = false ;
        ovlp_type_t type = ovlp->type ;
        if(type == OVLP_INPUT)
        {
            recv_result_t * receiver = (recv_result_t *)ovlp ;
            if((item->data.events & EPOLLIN) == EPOLLIN)
            {
                //标记可读
                item->occur |= EPOLLIN ;
                ready = true ;
            }
        }
        else if(type == OVLP_OUTPUT)
        {
            send_result_t * sender = (send_result_t *)ovlp ;
            if((item->data.events & EPOLLOUT) == EPOLLOUT)
            {
                //标记可写
                item->occur |= EPOLLOUT ;
                ready = true ;
            }
        }
        else if(type == OVLP_ACCEPT)
        {
            accept_result_t * acceptor = (accept_result_t *)ovlp ;
            if((item->data.events & EPOLLIN) == EPOLLIN)
            {
                item->occur |= EPOLLIN ;
                ready = true ;
            }
        }

        if(ready == true)
            iocp_mgr_item_ready(mgr , item) ;

        socket_ovlp_unlock(ovlp) ;
    }

    return 0 ;
}

int iocp_socket_callback(socket_t * s , int evt , int result) 
{
    /**
    #define kBeforeSocketClose      1 
    #define kSocketConnect          2
    #define kSocketSend             3
    #define kSocketSendTo           4
    #define kSocketRecv             5
    #define kSocketRecvFrom         6
    */
    if(s == NULL || s->addition == NULL)
        return 0 ;

    bool ready = false ;
    iocp_item_t * item = (iocp_item_t *)s->addition ;
    uint32_t events = item->data.events ;
    
    if(evt == kSocketConnect || evt == kSocketSend || evt == kSocketSendTo ||
        evt == kSocketRecv || evt == kSocketRecvFrom)
    {
        if(((events & EPOLLERR) == EPOLLERR) && (result != 0))
        {
            item->occur |= EPOLLERR ;
            ready = true ;
        }
    }

    return 0 ;
}

