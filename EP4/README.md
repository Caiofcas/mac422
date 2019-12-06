# Relatório EP 4 - MAC0422

### Artur Magalhães R. Santos, 10297734

### Caio Fontes, 10692061

## Resumo

​	Nesse EP implementamos arquivos temporários no sistema Minix, ou seja, arquivos que são criados por algum programa e eliminados assim que o programa é terminado.
​	Para tal implementamos a syscall `open_tmp`, a Macro `I_TEMPORARY` e modificamos as funções de gerenciamento de arquivos do servidor *FS* do minix.

## Desenvolvimento

Procuramos trabalhar juntos fisicamente, pois isso facilitou o desenvolver do projeto. Utilizamos git para versionamento de código.

Primeiro, mapeamos quais os arquivos seriam necessários para completar o EP, ou seja, aqueles que necessitariam de modificação.
Também, tentamos pensar conforme o que foi visto em aula: a chamada LINK cria um novo arquivo, UNLINK "apaga", e etc, mas por fim,
optamos por alterar `free_proc.c` em misc.c, no server do fs. Nele, verificamos se o arquivo possuia a flag necessária, para assim,
chamar o unlink.

Além disso, como nos outros EPs, implementamos uma chamada de sistema, que permitia a abertura dos arquivos temporários.
Os arquivos necessários para essa implementação estão descritos abaixo.

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

Para a implementação da macro de temporário:

- *src/include/const.h*

### Mudanças no FS

A nova macro para os arquivos temporários foi criada. Outras alterações foram mencionadas em **Desenvolvimento**.

## Testes

Fizemos alguns testes simples para testar se os arquivos estavam sendo criados. Não foram exaustivos, 
mas pareceram demonstrar que o código funcionava de maneira apropriada.
