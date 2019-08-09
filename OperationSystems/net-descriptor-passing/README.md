# Descriptor passing and IPC

Client and server on `UNIX` socket

## Usage:

### Commands in current repository:
+ `make` — creates server and client executable files
+ `make Server` — creates server executable file
+ `make Client` — creates client executable file
+ `make ServerRun` — runs the server (creates server executable file, if not done yet)
+ `make ClientRun` — runs the client with 0 arguments (creates client executable file, if not done yet)
### Program arguments:
+ Server doesn't use arguments
+ Client takes first argument as Client's id or uses default id `0` if none given
### Expected behavior:
+ Server notifies user when it's up and ready to work
+ Server shows the message and it's author
+ Server notifies user if Client is disconnected
+ Client reading the messages in infinite loop
+ Client terminating it's work if string `exit` is given

## Task

### Знакомство с передачей дескрипторов и IPC

Необходимо получить опыт работы с IPC. Нужно создать приложение клиента и сервера.
 * Клиент и сервер обшаются через UNIX сокет
 * Клиент подключается к серверу через UNIX сокет, получает от сервера файловый дескриптор, соответсвующий объекту какого-либо вида IPC
 * Клиент и сервер выполняют какое-то взаимодействие используя IPC

#### Сервер должен:
 * Ожидать подключений на UNIX сокете
 * Для новых соединений создавать новый вид IPC, объекты которого представимы в виде файловых дескрипторов
 * Передавать через UNIX сокет клиенту файловый дескриптор IPC соответсвующий клиенту
 * Ожидать выполнения какого-либо протокола поверх IPC с клиентом

#### Клиент должен:
 * Подключиться на UNIX сокет к серверу</li>
 * Получать в виде файлового дескриптора клиентскую часть IPC</li>
 * Взаимодействовать с сервером через IPC для выполнения какого-либо протокола</li>

Примерами IPC могут служить: PIPE, socket, файловые дескрипторы для разделямой памяти или сообщений(POSIX), файловые дескрипторы для анонимной памяти.

#### Что может помочь при выполнении задания?
 * man 7 unix
