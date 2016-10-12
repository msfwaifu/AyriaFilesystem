/*
    Initial author: (https://github.com/)Convery for Ayria.se
    License: MIT
    Started: 2016-10-12
    Notes:
        Adds or removes protection from a range of pages.
*/

#include "Memprotect.h"

#ifdef _WIN32
#include <Windows.h>

void COAL::Memprotect::Protectrange(void *Address, const size_t Length, unsigned long Oldprotect)
{
    unsigned long Temp;
    VirtualProtect(Address, Length, Oldprotect, &Temp);
}
unsigned long COAL::Memprotect::Unprotectrange(void *Address, const size_t Length)
{
    unsigned long Oldprotect;
    VirtualProtect(Address, Length, PAGE_EXECUTE_READWRITE, &Oldprotect);
    return Oldprotect;
}

#else
#include <sys/mman.h>

void COAL::Memprotect::Protectrange(void *Address, const size_t Length, unsigned long Oldprotect)
{
    mprotect(Address, Length, Oldprotect);
}
unsigned long COAL::Memprotect::Unprotectrange(void *Address, const size_t Length)
{
    /*
        TODO(Convery):
        We need to parse /proc/self/maps to get the access.
        Implement this when needed.
    */

    mprotect(Address, Length, (PROT_READ | PROT_WRITE | PROT_EXEC));
    return (PROT_READ | PROT_EXEC);
}

#endif
