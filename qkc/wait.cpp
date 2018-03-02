
#include <wait.h>
#include <errno.h>
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

QUARK_LINKAGE intptr_t _cwait(int * status , intptr_t process , int action);

#ifdef __cplusplus
}
#endif


pid_t wait(__WAIT_STATUS stat_loc)
{
    return 0 ;
}

pid_t waitpid(pid_t pid , int * stat_loc, int options)
{
    /**
        getpid�ķ���ֵ��GetProcessId������_cwait�Ĳ���process��HANDLE��������֮����Ҫת��
    */
    HANDLE handle = ::OpenProcess(0 , TRUE , pid) ;
    if(handle == INVALID_HANDLE_VALUE)
    {
        errno = ECHILD ;
        return -1 ;
    }

    intptr_t ret = ::_cwait(stat_loc , (intptr_t)handle , options) ;
    if(ret == (intptr_t)handle)
        return pid ;

    return -2 ;
}
