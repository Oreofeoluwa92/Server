Ademuyiwa Adebunmi
Client server model..
This project consists of a server and client program that communicate over a named pipe (/tmp/server_pipe) to calculate prime numbers within a specified range.
The client sends a range request to the server in whichever case of RANGE is written, and the server responds with all prime numbers within that range or with an error message if the request is malformed.


- server.cpp`: The server program  listens on a named pipe for range requests and returns calculated primes.
- client.c`: The client program  sends range requests to the server and displays the response.

- Ubuntu OS or any Linux environment that supports named pipes.
- `g++` compiler for the server (C++).
- `gcc` compiler for the client (C).
How to run it.
1. Open two terminal and navigate to the project directory.
2. Compile the server and client:
   g++ server.cpp -o server
   gcc client.c -o client
3. On the second terminal also navigate the project directory
4. After which we call the name of the projects.On one run the ./server and the other ./client
   
