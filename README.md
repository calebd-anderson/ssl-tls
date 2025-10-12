# Implementing SSL/TLS
This source is my progress through the book by Joshua Davies: "[Implementing SSL/TLS Using Cryptography and PKI](https://onlinelibrary.wiley.com/doi/book/10.1002/9781118255797)".

## Environment
- [VSCode](https://code.visualstudio.com/download)
  - [Windows](https://code.visualstudio.com/docs/cpp/config-mingw)
  - [Linux](https://code.visualstudio.com/docs/cpp/config-linux)
### Manual Compilation
```bash
# linux can omit linking ws2_32
gcc -o webserver.exe ./src/webserver/webserver.c -lws2_32
gcc -o http.exe ./src/http.c -lws2_32
```

## Build with [CMake](https://cmake.org/download/)
### Build the Webserver
```bash
# generate a seperate webserver build system
cmake -S ./src/webserver -B ./webserver_build
# build the webserver target project
cmake --build ./webserver_build -t webserver
```
### Build the HTTP client
```bash
# generate the build system
cmake -S ./ -B ./build
# build the main project
cmake --build ./build
```
## Manual Test
1. Start the webserver listening on port 80
```bash
./webserver_build/Debug/webserver.exe
```
2. In a new terminal make a request with the http client to `http://localhost/test`
```bash
./build/src/Debug/http.exe http://localhost/test
# Connecting to host 'localhost'
# Retrieving document: 'test'
# HTTP/1.1 200 Success
# Connection: Close
# Content-Type:text/html

# <html><head><title>Test Page</title></head><body>Nothing here</body></html>

# shutting down.
```
3. Quit the webserver
```
CTRL[CMD]+C
```