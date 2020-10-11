# Trabalho 1 [:link:](https://github.com/ruanpato/sistemasOperacionais/tree/main/trabalhos/1) #

## Sumário ##

- [Trabalho 1 :link:](#trabalho-1-link)
  - [Sumário](#sumário)
  - [Descrição](#descrição)
  - [Ferramentas utilizadas 🛠️](#ferramentas-utilizadas-️)
  - [Autor](#autor)

## Descrição ##

Considere o código anexo (deadlock.c) como referência para esse trabalho.

O desenvolvedor assumiu as seguintes hipóteses:

- duas threads competem por dois mutexes: mutex1 e mutex2
- para o seu correto funcionamento, a thread1 precisa adquirir mutex1 E mutex2 (nessa ordem)
- para o seu correto funcionamento, a thread2 precisa adquirir mutex2 E mutex1 (nessa ordem)

O trabalho consite em apresentar uma solução (funcional) para o problema, já que a solução de referência apresenta a possibilidade de resultar em um deadlock (impasse).

Para tanto, deve-se empregar a chamada de sistema "pthread_mutex_trylock" que é a variante não bloqueante de acesso (lock) em mutexes. Consulte a página do manual no sistema para obter todos os detalhes sobre essa chamada.

O que submeter: o código fonte, via moodle até 11/10

Para compilar use:

>gcc deadlock.c -lpthread -o deadlock

## Ferramentas utilizadas 🛠️ ##

- [GNU-GCC](https://gcc.gnu.org/) - GNU gcc and g++ compiler

## Autor ##

- **[Ruan Pato](https://github.com/ruanpato)** - *Criador do repositório, descrições em README.md e resoução de exercícios e trabalhos*.
