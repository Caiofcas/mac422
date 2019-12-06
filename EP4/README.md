# Relatório EP 4 - MAC0422

### Artur Magalhães R. Santos, 10297734

### Caio Fontes, 10692061

## Resumo

​	Nesse EP implementamos arquivos temporários no sistema Minix, ou seja, arquivos que são criados por algum programa e eliminados assim que o programa é terminado.
​	Para tal implementamos a syscall `open_tmp`, a Macro `I_TEMPORARY` e modificamos as funções de gerenciamento de arquivos do servidor *FS* do minix.

## Desenvolvimento

### open_tmp

Adicionamos a syscall no servidor *FS*, alterando os arquivos:

Em *src/servers/fs*:

- *table.c* : adicionar `do_open_tmp`
- *proto.h* : protótipo
- *misc.c*  : definição de `do_open_tmp()`

Em *src/include*:

- *minix/callnr.h* : definição de `OPEN_TMP`
- *unistd.h* : protótipo de `open_tmp()`

Em *src/lib/posix*:

- *Makefile.in* : compilação do arquivo
- *_open_tmp* : função para programas de usuário `open_tmp()`

### Mudanças no FS

## Testes
