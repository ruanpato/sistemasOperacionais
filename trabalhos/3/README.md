# Trabalho 3 [:link:](https://github.com/ruanpato/sistemasOperacionais/tree/main/trabalhos/3) #

## Sumário ##

- [Trabalho 3 :link:](#trabalho-3-link)
  - [Sumário](#sumário)
  - [Descrição](#descrição)
  - [Ferramentas utilizadas 🛠️](#ferramentas-utilizadas-️)
  - [Autor](#autor)

## Descrição ##

Apresentar duas soluções (i.e., dois programas distintos) para o problema descrito abaixo: a primeira solução

empregando mutexes e semáforos e, a segunda solução empregando mutexes e variáveis condicionais.

Descrição do problema:

- A partir da thread principal criar 3 threads;

- Cada thread executa, basicamente, a mesma tarefa que consiste em incrementar uma variável global inicializada com valor zero (0); no entanto, a cada rodada envolvendo todas as threads, cada thread incrementa a variável global uma única vez. Além disso, a alternância entre as threads dá-se sempre em ordem crescente de identificadores. Assumir identificadores das threads incrementais iniciando-se a primeira thread com ID=0. Exemplo: assumindo-se que  as 3 threads tem ids 0, 1 e 2, ter-se-á a seguinte apresentação de incremento da variável global:

- thread 0: global = 1;

- thead 1: global = 2;

-thread 2: global = 3;

-thread 0: global = 4;

-thread 1: global = 5;

...

O incremento da variável global finaliza quando atingir um valor pré-estabelecido MAX (definido também pelo usuário).

PRAZO DE ENTREGA: 07/11

## Ferramentas utilizadas 🛠️ ##

- [GNU-GCC](https://gcc.gnu.org/) - GNU gcc and g++ compiler

## Autor ##

- **[Ruan Pato](https://github.com/ruanpato)** - *Criador do repositório, descrições em README.md e resoução de exercícios e trabalhos*.
