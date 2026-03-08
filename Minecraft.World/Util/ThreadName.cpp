#include "../Build/stdafx.h"

// From Xbox documentation

typedef struct tagTHREADNAME_INFO {
    uint32_t dwType;     // Must be 0x1000
    const char* szName;    // Pointer to name (in user address space)
    uint32_t dwThreadID; // Thread ID (-1 for caller thread)
    uint32_t dwFlags;    // Reserved for future use; must be zero
} THREADNAME_INFO;

void SetThreadName( uint32_t dwThreadID, const char* szThreadName )
{
#ifndef __PS3__
    THREADNAME_INFO info;
	
    info.dwType = 0x1000;
    info.szName = szThreadName;
    info.dwThreadID = dwThreadID;
    info.dwFlags = 0;
	
#if ( defined _WINDOWS64 | defined _DURANGO )
	__try
	{
		RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(uint32_t), (uintptr_t *)&info );
	}
	__except( GetExceptionCode()==0x406D1388 ? EXCEPTION_CONTINUE_EXECUTION : EXCEPTION_EXECUTE_HANDLER )
	{
	}
#endif
#ifdef _XBOX
    __try
    {
        RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(uint32_t), (uint32_t *)&info );
    }
    __except( GetExceptionCode()==0x406D1388 ? EXCEPTION_CONTINUE_EXECUTION : EXCEPTION_EXECUTE_HANDLER )
    {
    }
#endif
#endif // __PS3__
}
