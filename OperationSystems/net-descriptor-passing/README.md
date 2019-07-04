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
