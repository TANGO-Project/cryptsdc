#ifndef DETDECRYPTER_H
#define DETDECRYPTER_H

#include <string>
#include <vector>
#include <cryptopp/cryptlib.h>
#include <cryptopp/aes.h>
#include <cryptopp/ccm.h>
#include <cryptopp/secblock.h>

#include "Decipher.hpp"

class DETDecrypter : public Decipher<std::string,std::string>
{
private:
	CryptoPP::SecByteBlock key;
	CryptoPP::SecByteBlock iv;
	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption d;
public:
    void readSecretsFromJSON(std::string& reader) override;
    std::string decrypt(std::string& ciphertext) override;
    std::string decrypt(CryptoPP::SecByteBlock& ciphertext);
    std::string decryptFromHex(std::string& hexString);
    void setKeyWithIV(CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv);
    void setKeyWithIV(std::string& hexkey, std::string& hexiv);

    DETDecrypter(){};
    virtual ~DETDecrypter(){};
};

#endif
