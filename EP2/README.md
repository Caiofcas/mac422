# Relatório EP 2 - MAC0422

#### Artur Magalhães R. Santos, 10297734

#### Caio Fontes, 10692061

## Resumo

No EP2, implementamos duas chamadas: `batch()` e `unbatch()`. As duas chamadas tem a função de colocar e retirar elementos de uma fila, também implementada por nós,

chamada `BATCH_Q`.  A principal característica dessa fila é a de que todo novo processo roda até ter o número de *ticks* igual ao processo com menor número de *ticks* da fila. Quando todos possuem o mesmo número, os escalonamento é feito em *round robin*.

Nessa etapa, seguimos boas práticas de código e versionamento, trabalhando em *branches* separadas, e abrindo *pull requests* (PRs) a *master*. Dessa forma, conseguimos controle quando deparamos com erros.

O detalhamento do desenvolvimento, implementação, problemas enfrentados e testes, segue abaixo.

## Desenvolvimento

### Observações Gerais

​    Inicialmente, coletamos informações sobre quais arquivos necessitariam de modificação para que implementássemos nossa fila. Em relação a fila e o escalonamento, foram modificados os arquivos *proc.c* e *proc.h*. Para a implementação das chamadas, um número maior de arquivos teve de sofrer modificações, estes serão detalhados adiante.

​    Em suma, `BATCH_Q` foi inserida entre a fila `IDLE` e `MIN_USER_Q`, com valor `15`. Os responsáveis por lidar com a inserção e remoção da fila não foram modificados, mas sim as funções `sched()` e `pick_proc()`, já que estas são as responsáveis pela ordem das inserções, e lidam com as considerações necessárias para que implementássemos o desejado.

​    Para assegurar que nenhum processo entrásse indesejadamente na nossa fila, ou seja, acabasse sendo selecionado pelo `sched()` devido a uma diminuição de sua prioridade, alteramos essa função e a função `balance_queues`  (ambas no arquivo */usr/src/kernel/proc.c*) para que, nesse caso, o processo passasse para `IDLE` imediatamente. Em `pick_proc()`, percorremos os processos em busca do menor número de ticks, e o guardamos. Em seguida, quando iremos selecionar o próximo processo, levamos em consideração: se o processo possui um número de ticks maior do que o processo com o menor valor, e nesse caso, ele será o próximo; caso contrário - processo tenha menor número de ticks - procuramos o próximo que tenha maior número de ticks.

### Implementação das Chamadas

​    As funções `batch()` e `unbatch()` foram implementadas cada uma por uma *syscall* e uma *kernel call.* O fluxo de execução para cada uma das duas chamadas é basicamente o mesmo e será descrito abaixo:

1. Chamada da função `int batch(int pid)` ou `int unbatch(int pid)` no código C do usuário.

2. Essas funções estão definidas em */usr/src/lib/posix/_batch.c* e */usr/src/lib/posix/_unbatch.c* respectivamente. Executam a função `_syscall()` com os argumentos apropriados para a chamada.

3. 1. Os argumentos passados, por mensagem, são o `pid` do processo alvo passado na chamada da função em (1) e o `pid` do processo que está executando essa chamada (para fazermos a verificação de se é o processo pai).
   2. Esses dois arquivos foram incluídos em */usr/src/lib/posix/Makefile.in*

4. As duas chamadas de sistema foram definidas no final do arquivo */usr/src/servers/pm/misc.c* .

5. 1. Elas recuperam os números do processo alvo e o processo que executou a chamada da tabela e fazem a verificação de se o processo que chamou é o pai do processo alvo, se não for o fluxo é interrompido aqui.

   2. Essas syscalls tiveram que ser incluídas em :

   3. 1. */usr/src/servers/pm/proto.h*
      2. */usr/src/servers/pm/table.c*
      3. */usr/src/include/minix/callnr.h*

   4. Executam as funções `int sys_batch(int pid)` e `int sys_unbatch(int pid)` passando como argumento o número do processo que será colocado/retirado de `BATCH_Q`.

6. Os handlers para as kernel calls foram definidas em */usr/src/lib/syslib/sys_batch.c* e */usr/src/lib/syslib/sys_unbatch.c* .Executam a função `_taskcall()` com os argumentos apropriados para a chamada.

7. 1. O argumento passado, também, por mensagem, é o número do processo alvo das chamadas.
   2. Esses dois arquivos foram incluídos em /usr/src/lib/syslib/Makefile.in

8. As duas kernel calls foram definidas em */usr/src/kernel/do_sysbatch.c* e */usr/src/kernel/do_sysunbatch.c* 

9. 1. As kernel calls são definidas nesses dois arquivos. As duas recuperam o endereço do processo associado ao número de processo passado como argumento e fazem as verificações necessárias.

   2. Em *do_sysbatch.c* o processo é retirado da fila em que está, sua prioridade é alterada e ele é recolocado em `BATCH_Q`.

   3. Em *do_sysunbatch.c*  se verifica se o processo está em `BATCH_Q`, se estiver é retirado da fila , sua prioridade é alterada e ele é recolocado nas outras filas.

   4. Essas kernel calls foram incluídas também em:

   5. 1. */usr/src/kernel/Makefile*
      2. */usr/src/include/minix/com.h*
      3. */usr/src/kernel/system.c* - em `initialize()`
      4. */usr/src/kernel/system.h*



### Implementação da Política de Escalonamento



## Problemas

​    Ao decorrer do desenvolvimento, nos deparamos com certos problemas. O primeiro deles foi o fato de necessitarmos modificar diversos arquivos do Minix, e portanto, seria sensato utilizarmos git. 
​	Além disso, alguns problemas inesperados aconteceram ao modificar os arquivos do Minix dentro de nossas máquinas, pois alguns espaços e *newlines*, ao serem passados de volta a máquina virtual - usando netcat - geravam problemas de compilação.
​	Tivemos dificuldades em determinar se deveríamos implementar as chamadas `batch()` e `unbatch()` como *syscalls* e mudar a prioridade dos processos modificando a chamada `nice()` ou se deveríamos implementar novas *kernel calls*. No final, concluímos que a segunda solução seria mais adequada e facilitaria os testes.



## Testes

​	Para testar se as chamadas verificavam se o processo que as chamava era pai do processo "alvo", rodamos o seguinte teste:

```C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


pid_t efork(){
    pid_t child_pid;

    child_pid = fork();
    if (child_pid < 0) {
        perror("Forking child has failed");
        exit(1);
    }
    return child_pid;
}

void testa_chamadas(pid_t alvo, int opc){
    pid_t child_pid;

    child_pid = fork();

    if(child_pid == 0) { /*child*/
        printf("Processo nao pai chamou batch\nRetornou: %d\n",batch(alvo));
        if(opc){
            sleep(6);
            printf("Processo nao pai chamou unbatch\nRetornou: %d\n",unbatch(alvo)); 
        }
        exit(0);
    } else { /*parent*/
        printf("Processo pai chamou batch\nRetornou: %d\n",batch(alvo));
        if(opc){
            sleep(6);
            printf("Processo pai chamou unbatch\nRetornou: %d\n",unbatch(alvo)); 
        }
        return;
    }

}

int main(int argc, char* argv[]){
    
    int opc = 0;
    pid_t alvo_pid;

    if(argc > 1) opc = atoi(argv[1]);

    /* opc == 0 -> testa somente batch()
     * opc == 1 -> testa  batch() e unbatch()*/
    
    alvo_pid = efork();
    
    if(alvo_pid == 0) { /*child*/
        exit(execve("alvo.out",NULL,NULL));
    } else { /*parent*/
        testa_chamadas(alvo_pid,opc);
    }

    return 0;
}
```

​	Tivemos dificuldades em testar se a política de escalonamento estava funcionando de maneira apropriada. Acabamos usando uma versão modificada do código de teste compartilhado pelo nosso colega Eduardo Yukio Rodrigues no fórum em combinação com as seguintes linhas adicionadas no arquivo */usr/src/kernel/clock.c* :

```C
214	/* ######################################################## */
215    	/*testing,can be deleted after*/
216    	if(proc_ptr->p_priority == BATCH_Q) {
217        	kprintf("(%d,%d)  ",proc_ptr->p_nr,proc_ptr->p_ticks_left);
218    	}
219	/* ######################################################## */
```

​	Para que o número do processo e o número de ticks restantes fossem impressos sempre que um processo presente em `BATCH_Q` executasse. Esse código foi removido na versão entregue para não interferir em testes que o monitor queira rodar. A versão modificada do teste era essa:

```C
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
 
#define DIE(msg) \
do { \
  printf("%s\n", msg); \
  exit(EXIT_FAILURE); \
} while(0)
 
void busy_wait()
{
  int x;
  while(1){
      x = 1;
  }    
  return;  
}
 
void batch_wait(pid_t pid)
{
  int batch_ret, unbatch_ret;
  if ((batch_ret = batch(pid)) != 0) {
    printf("batch retornou %d\n", batch_ret);
  }
  busy_wait();
  waitpid(pid, NULL, 0);
}
 
int main()
{
  pid_t child_pid = fork();
  if (child_pid < 0) {
    DIE("fork falhou");
  }
  if (child_pid == 0) {
    pid_t grandchild_pid = fork();
    if (grandchild_pid < 0) {
      DIE("fork do grandchild falhou");
    }
    if (grandchild_pid == 0) {
      pid_t last_pid = fork();
      printf("last_pid = %d\n", last_pid);
      if (last_pid < 0) {
        DIE("fork do last_child falhou");
      }
      if (last_pid == 0) {
        busy_wait();
      } else {
        printf("grandchild para last\n");
        batch_wait(last_pid);
      }
    } else {
      printf("child para grandchild\n");
      batch_wait(grandchild_pid);
    }
  } else {
    printf("parent para child\n");
    batch_wait(child_pid);
  }
  return
```

