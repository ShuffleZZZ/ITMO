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
