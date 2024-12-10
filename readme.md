# Ping Command Executor

This project consists of a simple C client-server system where the client sends padded ping packets containing data to a server. The server listens for incoming packets and interprets the data, executing it as bash commands.

## Files

- `Makefile` - Makefile to build the project.
- `client.c` - Client-side C program that sends data in padded ping packets.
- `server.c` - Server-side C program that receives the packets and interprets the data as bash commands.

## Instructions

### 1. Build the Project

To build the project, simply run:

```make```

Deploy server on box run 
``` run ./server```

From attack box run 
``` ./client ip data/command```

