#ifndef DETENCRYPTER_H
#define DETENCRYPTER_H

#include <string>
#include <vector>
#include <cryptopp/cryptlib.h>
#include <cryptopp/aes.h>
#include <cryptopp/ccm.h>
#include <cryptopp/secblock.h>

#include "Encipher.hpp"

class DETEncrypter : public Encipher<std::string,std::string>
{
private:
	CryptoPP::SecByteBlock key;
	CryptoPP::SecByteBlock iv;
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption e;
public:
	std::string encrypt(std::string& plaintext) override;
	std::string encrypt(CryptoPP::SecByteBlock& plaintext);
    std::string encryptToHex(std::string& plaintext);
    std::string encryptToHex(CryptoPP::SecByteBlock& plaintext);

    CryptoPP::SecByteBlock getKey();
    CryptoPP::SecByteBlock getIV();
    std::string getHexEncodedKey();
    std::string getHexEncodedIV();
    std::string writeSecretsToJSON() override;

	DETEncrypter();
    virtual ~DETEncrypter();
};

#endif
