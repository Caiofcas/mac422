# Relatório EP1 - MAC0422

#### Artur Magalhaes, 10297734 

#### Caio Fontes, 10692061

## Resumo

A shell foi implementada seguindo um loop de execução simples:

1. Lê o input do usuário da Entrada padrão.
2. Processa esse input e identifica o comando chamado.
3. Se for um dos comandos conhecidos, cria o processo filho.
4. Executa as ações pertinentes ao comando.
5. Volta para o passo 1.

## Recursos Utilizados

A leitura foi realizada utilizando a função *scanf()*, e as informações foram mostradas através da função *printf()*, ambas da biblioteca padrão do C.

A identificação do comando foi feita utilizando as funções *strcmp* e *strtok* , da biblioteca **string.h**.

As chamadas de sistema foram utilizadas no código através das biliotecas **unistd.h** , **fcntl.h** ,**sys/wait.h** e **sys/stat.h**.

A criação do processo filho utilizou a chamada de sistema `fork`.

O término do processo filho foi realizado através da função `exit`.

Os comandos *liberageral* e *protegepracaramba* foram implementados através da chamada `chmod`, que muda a permissão do arquivo passado como argumento.

O comando *rodeveja* foi implementado utilizando as chamadas `execve` - chamada pelo processo filho para executar o programa passado como argumento - e `waitpid` - chamada pelo processo pai para que ele espere a execução do processo filho.

O comando *rode* também utilizou a chamada *execve*, no entanto sua entrada foi desviada da entrada padrão, de maneira a não interferir com chamadas de outros comandos na shell, isso foi feito com a chamada `close`.

## Problemas Enfrentados

Tivemos alguns problemas relacionados ao retorno do filho, e em qual seria a forma apropriada de implementar essa solução. 

Outro problema foi o redirecionamento da entrada na questão do rode, mas no final conseguimos uma solução que aparenta ser satisfatória.

Ler o livro recomendado na disciplina junto a tutoriais, conseguimos alcançar o formato desejado.