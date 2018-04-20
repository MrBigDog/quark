
#ifndef __QKC_INNER_FSOCKET_H
#define __QKC_INNER_FSOCKET_H 1

#include <quark_compile.h>
#include <stdint.h>
#include <windows.h>
#include <winsock2.h>
#include "ring_buffer.h"

#ifdef	__cplusplus
extern "C" {
#endif

/**
    Ϊ��ʵ��epoll���ԣ���Ҫ��ԭ����socket��Щ���죬��Ӹ�����Ϣ������ֱ��ʹ�á�
*/
#define SOCKET_STAGE_VOID       0 
#define SOCKET_STAGE_BIND       1
#define SOCKET_STAGE_LISTEN     2
#define SOCKET_STAGE_CONNECT    3
#define SOCKET_STAGE_DESROTY    -1

typedef struct __st_socket_ovlp     socket_ovlp_t ;
typedef struct __st_send_result     send_result_t ;
typedef struct __st_recv_result     recv_result_t ;
typedef struct __st_accept_result   accept_result_t;

typedef struct __st_socket{
    SOCKET socket ;
    int8_t type ;                  //SOCK_STREAM��SOCK_DGRAM
    int8_t stage ;  
    int8_t noblock :1;            //Ĭ����������һ������Ҫ�ı�ʶ!!!������ò��û�б�Ҫ��

    HANDLE            locker ;    //�������ٱ���
    accept_result_t * acceptor ;
    send_result_t   * sender ;
    recv_result_t   * receiver ;
} socket_t;

typedef enum{
    OVLP_VOID   =   0 ,
    OVLP_ACCEPT =   1 ,
    OVLP_INPUT  =   2 ,
    OVLP_OUTPUT =   3 
} ovlp_type_t ;

struct __st_socket_ovlp
{
    OVERLAPPED          ovlp ;
    int                 status ;
    ovlp_type_t         type ;
    socket_t    *       owner ;
    volatile LONG       counter ;
} ;

/**
    2018-04-19
    ��iocp��preactorģʽת����epoll��actor�ѶȱȽϴ���Ҫ������sendʱ����֪�����Է��������ֽ�����
    send�Ŀɷ��ֽ���ͬʱ����ס��ͬʱ�����������շ�˫���Ļ�������С���ƣ������ǵ������ɱ��ط��ͻ�����������
    immediately���ص��ֽ���ֻ�����ο��ã�����������ɵ��ֽ������������͵��ֽ������������Ϸ���ʱ��
    �������ͻᱻ�������������������Ч�ʡ���ˣ���Ҫ���һ������������ȷ���ֽ����ǿɿصġ�����Ϊ������
    ���������½��������������˵��Ӧ�÷������һ�㡣
    ���ͨ��TCP��ͬһ������ͬʱ�������ӷ��ͣ���ô������ʧ����Ϊ�������½��������ء�
*/
#define SNDBUFSIZE      8192
struct __st_send_result{
    socket_ovlp_t   link ;

    WSABUF          data ;
    ring_buffer_t   ring_buffer ;
};

struct __st_recv_result{
    socket_ovlp_t   link ;
    WSABUF data ;
};

#define ACCEPT_ADDRESS_SIZE 256
struct __st_accept_result{
    socket_ovlp_t   link ;

    SOCKET insocket ;           //���յ��ͻ�������������׽���   
    char address[ACCEPT_ADDRESS_SIZE] ;
    size_t bytes ;
};

void update_contex_acceptex(SOCKET& new_socket , SOCKET& listen_socket) ;

bool sockopt_get_keepalive(SOCKET& s , bool &optval) ;
bool sockopt_set_keepalive(SOCKET& s , bool optval) ;

bool sockopt_get_recv_buffer_size(SOCKET& s , int& optval) ;
bool sockopt_set_recv_buffer_size(SOCKET& s , int optval) ;

bool sockopt_get_send_buffer_size(SOCKET& s , int& optval) ;
bool sockopt_set_send_buffer_size(SOCKET& s , int optval) ;

bool sockopt_get_recv_timeout(SOCKET& s , DWORD& optval) ;
bool sockopt_set_recv_timeout(SOCKET& s , DWORD optval) ;

bool sockopt_get_send_timeout(SOCKET& s , DWORD& optval) ;
bool sockopt_set_send_timeout(SOCKET& s , DWORD optval) ;

bool socket_init(socket_t *& s) ;

bool send_result_init(send_result_t *& result) ;
bool socket_send(send_result_t * result , int flags) ;
bool socket_sendto(send_result_t * result , int flags , const struct sockaddr * addr , socklen_t addr_len) ;

bool recv_result_init(recv_result_t *& result) ;
bool socket_start_recv(recv_result_t * result) ;
bool socket_start_recvfrom(recv_result_t * result , int flags , const struct sockaddr * addr , socklen_t addr_len) ;

bool socket_ovlp_lock(socket_ovlp_t * ovlp) ;
bool socket_ovlp_unlock(socket_ovlp_t * ovlp) ;

#ifdef	__cplusplus
}
#endif

#endif /** __QKC_INNER_FSOCKET_H */
