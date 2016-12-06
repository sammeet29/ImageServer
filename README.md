# ImageServer
A multithreaded image processing server in C

Compile Threaded Server:
Client:
g++ threadedclient.cpp csapp.cpp -o threadedclient -pthread -fpermissive

Server:
g++ `pkg-config --cflags opencv` test.cpp echo.cpp csapp.cpp colortogray.cpp `pkg-config --libs opencv` -o test -fpermissive -pthread
