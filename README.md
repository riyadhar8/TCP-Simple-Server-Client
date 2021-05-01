# TCP-Simple-Server-Client
C socket programming to send a message from the client to server and vice-versa.  
  
1. The server as a command line argument accepts the port number to which it should bind.  
2. The client, as command line arguments, accepts the IP address and the port number at which it will find the server.  
3. After connecting to the server, the client reads a line from the standard input and sends it to the server.  
4. The server prints the received line in the reverser order and reads a line from the standard input and sends it to the client.  
5. The client prints the received line in the reverse order and exits. The server is ready to accept a new client.  

## Step1: Code Compilation
`make`

## Step2: Execute server.c
`./server 12000`

## Step3: Execute client.c
`./client 127.0.0.1 12000`  
  
Server keeps waiting for a new client till `Ctrl + C` is pressed.
