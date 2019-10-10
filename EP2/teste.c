#include "unistd.h"

typedef struct {
        unsigned char bytes[256]; /* Espero que seja espaço suficiente para guardar a msg*/
} message;

static message m; /* Aloca espaço para a msg */

void _syscall(int who, int syscallnr, register message* msgptr); /* declara o simbolo _syscall pro compilador*/
int printf(const char* fmt, ...); /* declara o simbolo printf sem incluir o stdio.h */

int main(int argc, char* argv[])
{
        _syscall(0, 57, &m); /* 0 = MM, 1 = FS*/
        _syscall(0, 58, &m); /* 0 = MM, 1 = FS*/
        return 0;
}