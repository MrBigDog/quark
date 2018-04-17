
#ifndef __QKC_INNER_FSOCKET_H
#define __QKC_INNER_FSOCKET_H 1

#include <quark_compile.h>
#include <stdint.h>
#include <windows.h>
#include <winsock2.h>

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
#define SOCKET_STAGE_NOTUSED    -1

typedef struct __st_socket{
    SOCKET socket ;
    int type ;                  //SOCK_STREAM��SOCK_DGRAM
    int stage ;  
    int8_t noblocking ;         //Ĭ����������һ������Ҫ�ı�ʶ!!!
    int8_t nodelay ;            //Ĭ���ӳ�
    int8_t keepalive ;          //���ֻ�Ծ��Ĭ��false
} socket_t;

typedef enum{
    OVLP_VOID   =   0 ,
    OVLP_ACCEPT =   1 ,
    OVLP_INPUT  =   2 ,
    OVLP_OUTPUT =   3 
} ovlp_type_t ;

typedef struct __st_socket_ovlp
{
    OVERLAPPED ovlp ;
    int                 status ;
    ovlp_type_t         type ;
} socket_ovlp_t;

typedef struct __st_send_result{
    socket_ovlp_t   header ;

    WSABUF data ;
    int bufsize ;               //�׽��ֱ��������Ĵ�С
    int sending_bytes ;         //�������ڷ����е��ֽ���
    size_t to_bytes ;           //���ڷ��͵����ֽ���
    size_t completed_bytes ;    //��ɷ��͵����ֽ���
} send_result_t ;

typedef struct __st_recv_result{
    socket_ovlp_t   header ;

    WSABUF data ;
    size_t from_bytes ;
    size_t complete_bytes ;
} recv_result_t ;

#define ACCEPT_ADDRESS_SIZE 256
typedef struct __st_accept_result{
    socket_ovlp_t   header ;
    SOCKET insocket ;           //���յ��ͻ�������������׽���   
    char address[ACCEPT_ADDRESS_SIZE] ;
} accept_result_t;

LPFN_ACCEPTEX look_up_acceptex(SOCKET& s) ;

void update_contex_acceptex(SOCKET& new_socket , SOCKET& listen_socket) ;


#ifdef	__cplusplus
}
#endif

#endif /** __QKC_INNER_FSOCKET_H */
