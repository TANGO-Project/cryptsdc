# cryptdsdc
&copy; James Dyer and University of Leeds 2018

Crypto library for European Project TANGO (http://tango-project.eu).

## Description
This C++ library provides symmetric cryptographic algorithms which produce ciphertexts that may be computed on. Each algorithm is implemented by two classes: an Encrypter, which implements the key generation and encryption algorithms, and Decrypter, which implements the decryption algorithm.

## Compilation
To compile:

```shell
cd cryptsdc
make
```
This builds a static and shared library in the `lib/` subfolder. You may need to edit the `LDFLAGS` make variable in `Makefile` to target the correct system library directories for your flavour of Linux.

To build and run the unit tests:
```shell
cd tests
make
./cryptsdc-tests
```
### Requirements
- gcc 4.8+ 
- NTL: Number Theory Library (http://www.shoup.net/ntl/)
- jsoncpp: JSON C++ library (https://github.com/open-source-parsers/jsoncpp)
- Crypto++: C++ cryptographic library (https://www.cryptopp.com/)
