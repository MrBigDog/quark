
#ifndef __QKC_BUILTIN_H
#define __QKC_BUILTIN_H 1

#include <quark_compile.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
    ʵ��gcc�ڽ����������ںܶ�linux��Դ���õ�������֧�֡�
*/
QKCAPI int __builtin_ffs (int x)  ;
QKCAPI int __builtin_ffsl(long x)  ;
QKCAPI int __builtin_ffsll (long long x) ;

#ifdef __cplusplus
}
#endif


#endif /* __QKC_BUILTIN_H */
