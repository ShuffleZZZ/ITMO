# Jit-compiler

Self made jit-compiler, which implements the factorial function.

## Usage:

### Commands in current repository:
+ `make` — just creates an executable file 
+ `make run` — runs the program (creates file before, if not done yet)
+ `make clean` — deletes executable file
### Program arguments:
+ Expected 1 non-negative integer value OR no arguments
### Output:
+ Returns factorial of given number OR factorial of default value `0`

## Task

###  Кусочек JIT компилятора

Цель - получить знакомство с системными вызывами, используемыми для получения/освобождения
памяти от ядра. Получить представление о том, как может работать JIT компилятор.

#### Программа должна
 * Выделить память с помощью mmap(2).
 * Записать в выделенную память машинный код, соответсвующий какой-либо функции.
 * Изменить права на выделенную память - чтение и исполнение. See: mprotect(2).
 * Вызвать функцию по указателю на выделенную память.
 * Освободить выделенную память.

#### Что может помочь?
 * man objdump
 * help disassemble в gdb

#### Extra points
Сильные духом призываются к возможности модификации кода выполняемой функции
в runtime. Например, вы можете получить аргументом вызова вашей программы
какое-то число и пропатчить машинный код этим числом. Эта часть задания будет
оцениваться в дополнительные баллы.
