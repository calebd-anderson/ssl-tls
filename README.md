# Implementing SSL/TLS
My progress through the book [Implementing SSL/TLS Using Cryptography and PKI](https://onlinelibrary.wiley.com/doi/book/10.1002/9781118255797) by Joshua Davies.

> [!TIP]
> Decode hex with [CyberChef](https://cyberchef.org/#recipe=From_Hex('None')).

## Environment
- [VSCode](https://code.visualstudio.com/download)
  - [Windows](https://code.visualstudio.com/docs/cpp/config-mingw)
  - [Linux](https://code.visualstudio.com/docs/cpp/config-linux)
- [Code::Blocks](https://www.codeblocks.org/)

## Build the whole project with [CMake](https://cmake.org/download/)
```bash
# generate the build system
cmake -S ./ -B ./build
# build the main project
cmake --build ./build
# build just one target
cmake --build ./build [-t <webserver|http|base64|hex|des|aes>]
```
## Compile & Test Manually
### GCC Options
- `-g`: https://gcc.gnu.org/onlinedocs/gcc-15.2.0/gcc/Debugging-Options.html#index-g
- `-I`: https://gcc.gnu.org/onlinedocs/gcc-15.2.0/gcc/Directory-Options.html#index-I
- `-o`: https://gcc.gnu.org/onlinedocs/gcc-15.2.0/gcc/Overall-Options.html#index-output-file-option
### HTTP Client/Server
```bash
# linux can omit linking ws2_32
gcc -o webserver.exe ./src/webserver/webserver.c -lws2_32
gcc -o http.exe ./src/http/http.c -lws2_32
```
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

### [Data Encryption Standard (DES)](https://csrc.nist.gov/pubs/fips/46-3/final)
> [!NOTE]
> DES is intended to be used as a library. Yet, a test routine is included that can be enabled with the compiler option `-DTEST_DES`.  
```sh
# Manual compilation
gcc -DTEST_DES -g -o des -Isrc/lib/hex -Isrc/lib/utility src/lib/hex/hex.c src/lib/utility/utility.c src/lib/des/des.c
```

> [!IMPORTANT]
> DES is an 8 byte block cipher. Hence, the `key` and initialization vector (`iv`) must be 8 bytes and the `input` must be a multiple of 8 bytes.
```sh
# DES
# ./des.exe [-e|-d] <key> <iv> <input>
./des.exe -e password initialz abcdefgh
# 71828547387b18e5
./des.exe -d password initialz 0x71828547387b18e5
# 6162636465666768
```
> [!NOTE]
> DES3 uses a 24 byte ($8*3$) `key`.
```sh
# DES3
./des -e twentyfourcharacterinput initialz abcdefgh
# c0c48bc47e87ce17
./des -d twentyfourcharacterinput initialz 0xc0c48bc47e87ce17
# 6162636465666768
```

### [Advanced Encryption Standard (AES)](https://csrc.nist.gov/pubs/fips/197/final)
```sh
# Manual compilation
gcc -DTEST_AES -g -o aes -Isrc/lib/hex -Isrc/lib/utility src/lib/aes/aes.c src/lib/utility/utility.c src/lib/hex/hex.c
```
#### CLI Usage
```sh
# encrypt
./aes -e passwordpassword initialzinitialz abcdefghabcdefgh 
# eb4703ae3d8212c64c5a91ccc2c4078f

# decrypt
./aes -d passwordpassword initialzinitialz 0xeb4703ae3d8212c64c5a91ccc2c4078f
# 61626364656667686162636465666768
```

#### Compare to OpenSSL
```sh
# encryption
printf 'abcdefghabcdefgh' | openssl enc -aes-128-cbc -K 70617373776f726470617373776f7264 -iv 696e697469616c7a696e697469616c7a -nopad -nosalt | xxd -p
# eb4703ae3d8212c64c5a91ccc2c4078f

# decryption
printf 'eb4703ae3d8212c64c5a91ccc2c4078f' | xxd -r -p | openssl enc -d -aes-128-cbc -K 70617373776f726470617373776f7264 -iv 696e697469616c7a696e697469616c7a -nopad -nosalt | xxd -p
# 61626364656667686162636465666768
```

## Other Ciphers
- blowfish
- twofish
- FEAL
- LOKI
- Camelia