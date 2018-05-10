
#ifndef __QKC_WINTF_WIPC_H
#define __QKC_WINTF_WIPC_H 1

#include <quark_compile.h>
#include <windows.h>
#include <stdint.h>
#include <sys/ipc.h>

#ifdef	__cplusplus
extern "C" {
#endif

/**
    2018-03-16
    cygwinͨ��һ��service���������֮���ͨѶ��qkc�����Ƕ�̬�⣬����ʹ��windows
    ԭ�������ڴ洦�����ȴ���һ��ȫ�ֵĽ��̼乲���ڴ�������IPC�����ֽ����boost��
    IPC�����������������ԭ���������������ʵ�ֵĴ��ۡ�

    2018-03-20
    WIPC�ڿռ��������˷��Ķ࣬�ȴ��������ơ�

    2018-05-10
    ����һ�������Ĺ�������������һ�������飬һ�������飬���ڿ��ټ��key_t�Ƿ���ڣ�
    һ����ϸ�飬��������������Լ�����ϸ�ڡ�
*/

//��linux��ֻ֧���ź�����Ϊ����ͬ��������Ϣ������ʱ�����ˡ�
#define IPC_TYPE_UNK        0
#define IPC_TYPE_SHM        1
#define IPC_TYPE_SEM        2
#define IPC_TYPE_MAX        3

static const char * ipc_type_names[IPC_TYPE_MAX] = {"\0" , "shm" , "sem"} ;

#define IPC_NAME_UNK        {'\0' , '\0' , '\0'}
#define IPC_NAME_SHM        {'s' , 'h' , 'm'}
#define IPC_NAME_SEM        {'s' , 'e' , 'm'}

typedef struct __st_ipc_item{
    uint8_t     magic[2]    ;
    uint8_t     isize   ;
    uint8_t     type    ;

    uint16_t    id ;
    uint16_t    nattch ;
    
    uint32_t    key ;
    uint32_t    bytes ;
} ipc_item_t;

#define INFO_BITMAP_SIZE    2048 
#define ITEM_COUNT          16384
#define IPC_SUPER_SIZE      4096
#define GLOBAL_IPC_SIZE     0X40000     //256K
typedef struct __st_ipc_section_info{
    uint16_t    offset    ;
    uint16_t    count     ;
    uint32_t    last_id   ;     //������BITMAP�����۵�
    uint8_t     unused[248] ;
} ipc_section_info_t ;

//������
typedef struct __st_ipc_super{
    char        magic[4] ;      //4
    uint32_t    ipc_size ;      //8
    uint8_t     major ;
    uint8_t     minor ;
    uint16_t    build ;         //12

    uint16_t    offset ;
    uint16_t    count   ;       //16
    uint32_t    last_id ;       //20

    uint8_t     unused[236] ;   //�ճ�256
    uint8_t     bitmap[INFO_BITMAP_SIZE] ;
}ipc_super_t ;

//���������ڴ��Ķ���
typedef struct __st_ipc_global{
    uint8_t super[IPC_SUPER_SIZE] ;
    ipc_item_t  items[ITEM_COUNT] ;
}ipc_global_t ;

QKCAPI const char * ipc_mtx_name() ;
QKCAPI const char * ipc_shm_name() ;

QKCAPI bool ipc_super_init(ipc_super_t * super) ;
QKCAPI bool ipc_super_final(ipc_super_t * super) ;
QKCAPI bool ipc_super_validate_magic(ipc_super_t * super) ;
QKCAPI void ipc_super_assign_magic(ipc_super_t * super) ;


QKCAPI bool ipc_global_init(ipc_global_t * global) ;
QKCAPI bool ipc_global_final(ipc_global_t * global) ;

QKCAPI int ipc_alloc_id(key_t key , int type) ;
QKCAPI void ipc_free_id(int id) ;

#ifdef	__cplusplus
}
#endif

#endif /** __QKC_WINTF_WIPC_H */
