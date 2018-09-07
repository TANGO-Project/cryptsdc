/*
 * SSEEncrypter.h
 *
 *  Created on: 15 Aug 2018
 *      Author: scsjd
 */

#ifndef SSEENCRYPTER_H_
#define SSEENCRYPTER_H_

#include <string>
#include <vector>
#include <cryptopp/cryptlib.h>
#include <cryptopp/aes.h>
#include <cryptopp/ccm.h>
#include <cryptopp/cmac.h>
#include <cryptopp/secblock.h>
#include "Encipher.hpp"

class SSEEncrypter: public Encipher<std::string,std::string> {
private:
	CryptoPP::SecByteBlock keyGenKey;
	CryptoPP::SecByteBlock keyGenIV;
	CryptoPP::SecByteBlock key;
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption e;
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption keygen;
	CryptoPP::CMAC<CryptoPP::AES> mac;

	void decodeHexString(std::string& hexString, CryptoPP::SecByteBlock& bytes);
public:
	std::string encrypt(std::string& plaintext) override;
    std::string encryptToHex(std::string& plaintext);

    CryptoPP::SecByteBlock getKey();
    CryptoPP::SecByteBlock getKeyGenKey();
    std::string getHexEncodedKey();
    std::string getHexEncodedKeyGenKey();
	CryptoPP::SecByteBlock createSearchKey(std::string& word);
	std::string createHexEncodedSearchKey(std::string& word);
    std::string writeSecretsToJSON() override;

	SSEEncrypter();
	SSEEncrypter(std::string& secrets);
    virtual ~SSEEncrypter();
};

#endif /* SSEENCRYPTER_H_ */
