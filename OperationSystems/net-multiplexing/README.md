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
