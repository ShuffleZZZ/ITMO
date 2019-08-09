# Sockets

Simple echo server

## Usage:

### Commands in current repository:
+ `make` — creates server and client executable files
+ `make server` — creates server executable file
+ `make client` — creates client executable file
+ `make serverRun` — runs the server with 0 arguments (creates server executable file, if not done yet)
+ `make clientRun` — runs the client with default string `message` (creates client executable file, if not done yet)
### Server arguments:
+ 0 argument case: server will use default port `8080`
+ 1 argument case: port number (integer)
### Client arguments:
+ 1 argument case: client will send your string by default port `8080`
+ 2 argument case: client will take first argument as port number (integer) and send second argument (string)
### Expected behavior:
+ server returns same string
+ client shows taken string and server response

## Task

### Знакомство с сокетами

Необходимо попробовать клиент-серверное взаимодействие через синхронные сокеты.
Помимо этого нужен Makefile, с помощью которого можно будет собрать клиент и сервер.
Семейство протоколов для использования на выбор: AF_UNIX, AF_INET, AF_INET6.

#### Сервер должен:
 * В качестве аргументов принимать адрес, на котором будет ожидать входящих соединений
 * Стартовать, делать bind(2) на заданный адрес и ожидать входящих соединений
 * При получении соединения, выполнять серверную часть придуманного вами протокола
 * После обработки принятого соединения возвращаться в режим ожидания входящих соединений

#### Клиент должен:
 * Принимать параметром адрес, к которому стоит подключиться
 * Выполнять клиентскую часть придуманного вами протокола
 * Завершаться

Для сильных духом предлагается выбрать какой-то существующий протокол и имплементировать его, или его разумное подмножество.
Сильность духа будет оцениваться в два балла, при условии что выбранный протокол сложнее чем ECHO(https://tools.ietf.org/html/rfc862).
