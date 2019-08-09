# Despite the greater functionality, this version does NOT guarantee that message will be sent fully or sent at all!!!

# Multiplexing

Same modified echo from <a href="https://github.com/ShuffleZZZ/ITMO/tree/master/OperationSystems/net/FirstVersion">previous task's first version</a>.

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
+ server returns reversed copy of received string
+ if sended string is `shutdown` - shuts down server (it returns terminating string and notifies user through the console, other clients stop working as well due to absence of response)
+ if sended string is `disconnect` - return terminating string to client and notifies user through the console which client is disconnected
+ client shows server response on the new line
+ client stops it's work after receiving termination string with specific message ☺