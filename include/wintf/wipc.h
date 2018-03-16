
#ifndef __QKC_WINTF_WIPC_H
#define __QKC_WINTF_WIPC_H 1

#include <quark_compile.h>
#include <windows.h>

#ifdef	__cplusplus
extern "C" {
#endif

/**
    2018-03-16
    cygwinͨ��һ��service���������֮���ͨѶ��qkcʹ��windowsԭ�������ڴ洦��
    ���ȴ���һ��ȫ�ֵĽ��̼乲���ڴ�������IPC�����ֽ����boost��IPC�����������
    ������ԭ���������������ʵ�ֵĴ��ۡ�
*/
#define IPC_ITEM_SIZE       64 
#define IPC_ITEM_COUNT      1024
#define IPC_SECTION_SIZE    65536

typedef char[IPC_ITEM_SIZE] ipc_item_t ;

typedef struct __st_ipc_section_head{
    uint32_t section_size ;

} ipc_section_head_t;

typedef struct __st_ipc_section{
    ipc_item_t items[1] ;    
} ipc_section_t ;

QKCAPI ipc_section_t * ipc_section_init() ;

QKCAPI void ipc_section_final(ipc_section_t * section) ;

#ifdef	__cplusplus
}
#endif

#endif /** __QKC_WINTF_WIPC_H */
