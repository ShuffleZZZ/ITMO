# Lib-linking

Small project which shows usage of different kinds of libraries.

## Usage:

### Commands in current repository:
+ `make` — creates libraries and executable file 
+ `make run` — runs the program (creates all files before, if not done yet)
+ `make clean` — deletes executable file and libraries aswell as all temporary files
### Program arguments:
+ Expected more than 1 string argument
### Output:
+ Returns same arguments with some particular letters replaced with simillar ones in swedish, estonian and norwegian languages(in that order)

## Task

###  Знакомство с библиотеками

Необходимо создать статическую, и две динамических библиотеки и программу, которая будет их использовать.
Помимо этого нужен Makefile(либо другой инструмент автоматизации сборки), с помощью которого можно будет собрать все части.

#### Статическая библиотека должна:
 * Собираться статически
 * Предоставлять какие-то функции<

#### Первая динамическая библиотека должна:
 * Собираться динамически
 * Динамически линковаться с программой на этапе линковки
 * Предоставлять какие-то функции

#### Вторая динамическая библиотека должна:
 * Собираться динамически
 * Предоставлять какие-то функции

#### Программа должна
 * Статически линковаться с статической библиотекой и вызывать предоставляемые ей функции
 * Динамически линковаться с первой динамической библиотекой и вызывать предоставляемые ей функции
 * Во время выполнения в явном виде загружать вторую динамическию библиотеку с помощью dlopen(3) и вызывать какие-то функции из нее

### Что может помочь при выполнении задания?
 * man dlopen(3), man ld(1), man gcc(1)
