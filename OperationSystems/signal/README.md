# Signals handling

`SIGSEGV` signal handler

## Usage:

### Commands in current repository:
+ `make` — just creates an executable file
+ `make run` — runs the program (creates file before, if not done yet)
+ `make clean` — deletes executable file
### Program arguments:
+ Not used
### Input:
+ User is choosing one of the given options and types in number of needed test
### Output:
+ Result of signal as well as dumped registers and memory nearby

## Task

### Обработка сигналов

Необходимо написать обработчик сигнала SIGSEGV. Обработчик должен:
 * Дампить значения general purpose регистров, соответствуюших моменту падения
 * Дампить память поблизости от адреса, по которому произошло нарушение защиты памяти

Стоит быть готовым, что:
 * Адрес, по которому был сгенерирован SIGSEGV - NULL
 * Адрес, по которому был сгенерирован SIGSEGV - находится на границе валидной памяти и нет

#### Что может помочь при выполнении задания?
 * man 2 sigaction
 * man 2 getcontext
