# Kidshell

Self made program executor.

## Usage:

### Commands in current repository:
+ `make` — just creates an executable file 
+ `make run` — runs the program (creates file before, if not done yet)

### Program arguments:
+ `empty input OR white spaces OR end of console input` — terminates the program
+ `path to executable file + arguments` — executes given file with it's arguments

## Task

### Необходимо создать игрушечный интерпретатор.

#### Цель - получить представление о том, как работают командные интерпретаторы.

Программа должна в бесконечном цикле считывать с stdin полный путь к
исполняемому файлу, который необходимо запустить и аргументы запуска.
Дождавшись завершения процесса необходимо вывести на stdout код его завершения.

Необходимо использовать прямые системные вызовы для порождения новых процессов,
запуска новых исполняемых файлов и получения статуса завершения процесса.
Все возвращаемые значения системных вызовов должны быть проверены и в случае
обнаружения ошибок необходимо выводить текстовое описание ошибки.

На входе могут быть некорректные данные.

Дополнительные баллы - поддержка переменных окружения.

Язык имплементации - C или C++.
