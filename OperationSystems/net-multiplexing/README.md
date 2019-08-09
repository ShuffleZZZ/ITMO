# Multiplexing

Same echo from <a href="https://github.com/ShuffleZZZ/os-net">previous task</a>.

## Usage:

### Commands in current repository:
+ `make` — creates server and client executable files
+ `make server` — creates server executable file
+ `make client` — creates client executable file
+ `make serverRun` — runs the server with 0 arguments (creates server executable file, if not done yet)
+ `make clientRun` — runs the client with 0 arguments (creates client executable file, if not done yet)
### Server (or Client) arguments:
+ 0 argument case: server (client) will use default port `8080`
+ 1 argument case: port number (integer)
### Expected behavior:
+ server notifies user through the console which client is connected after the first connection of client
+ server returns same string
+ client shows server response

## Task

### Знакомство с мультиплексированием

Необходимо попробовать клиент-серверное взаимодействие с использованием механизмов мультиплексирования.
Помимо этого нужен Makefile, с помощью которого можно будет собрать клиент и сервер.
Семейство протоколов для использования на выбор: AF_UNIX, AF_INET, AF_INET6.

#### Сервер должен:
 * В качестве аргументов принимать адрес, на котором будет ожидать входящих соединений
 * Стартовать, делать bind(2) на заданный адрес и ожидать входящих соединений с использованием одного из механизмов мультиплексирования
 * При получении соединения, добавлять дескриптор в механизм мультиплексирования и ожидать событий и на нем
 * Выполнять на принятых соединениях серверную часть протокола
 * По завершении обработки соединения удалять все события из механизмов мультиплексирования

#### Клиент должен:
 * Принимать параметром адрес, к которому стоит подключиться
 * Используя механизмы мультиплексирования подключаться к серверу
 * Используя механизмы мультиплексирования выполнять клиентскую часть протокола
 * Завершаться

Для сильных духом предлагается реализовать код, который будет работать на двух разных ОС, используя на каждой специфичные механизмы мультиплексирования.
Сильность духа будет оцениваться в два балла.
