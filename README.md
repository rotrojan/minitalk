# minitalk
The purpose of this 42 project is to code a small data exchange program using UNIX signals.

## Usage
Compile with `make`.

First, lauch the server:
```
./server
```
The server will display his PID.

Then, in another terminal window, send a message with the client:
```
./client <server_pid> <message>
```
Example: `./client 42424 "Hello world!"`

The message will be displayed by the server (emojis are supported 😅).

To quit the server, use `Ctrl` + `C`.
