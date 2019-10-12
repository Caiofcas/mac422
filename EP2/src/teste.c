#include "unistd.h"
#include <lib.h>

int printf(const char* fmt, ...); /* declara o simbolo printf sem incluir o stdio.h */

int main(int argc, char* argv[])
{
        message m;
        m.m1_i1 = 45;
        _syscall(0, 57, &m); /* 0 = MM, 1 = FS*/
        _syscall(0, 58, &m); /* 0 = MM, 1 = FS*/
        return 0;
}