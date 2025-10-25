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
gcc -o http.exe ./src/http/http.c -lws2_32
# Test DES
gcc -DTEST_DES -g -o des -Isrc/hex src/des/des.c src/hex/hex.c
./des.exe -e password initialz abcdefgh
# 71828547387b18e5
./des.exe -d password initialz 0x71828547387b18e5
# 6162636465666768 (hex encoded)
```

## Build with [CMake](https://cmake.org/download/)
```bash
# generate the build system
cmake -S ./ -B ./build
# build the main project
cmake --build ./build
# build just one target
cmake --build ./build [-t <webserver|http|des|base64|hex>]
```
## Manual Test
1. Start the webserver listening on port 80
```bash
./build/ssl-tls/webserver/Debug/webserver.exe
```
2. In a new terminal make a request with the http client to `http://localhost/test`
```bash
./build/ssl-tls/http/Debug/http.exe http://localhost/test
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
## Free C/C++ IDE
[Code::Blocks](https://www.codeblocks.org/)