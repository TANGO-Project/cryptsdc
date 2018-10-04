/*
 * SSEDecrypter.h
 *
 *  Created on: 15 Aug 2018
 *      Author: scsjd
 */

#ifndef SSEDECRYPTER_H_
#define SSEDECRYPTER_H_

#include <string>
#include <vector>
#include <cryptopp/cryptlib.h>
#include <cryptopp/aes.h>
#include <cryptopp/ccm.h>
#include <cryptopp/cmac.h>
#include <cryptopp/secblock.h>
#include "Decipher.hpp"

class SSEDecrypter: public Decipher<std::string,std::string> {
private:
	/**
	 * The cipher key
	 */
	CryptoPP::SecByteBlock key;
	/**
	 * The decryption cipher (AES in CBC mode)
	 */
	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption d;

	/**
	 * Decode a hexadecimal string and place the result in \c bytes
	 * @param hexString A hexadecimal string
	 * @param bytes A byte array
	 */
	void decodeHexString(std::string& hexString, CryptoPP::SecByteBlock& bytes);
public:
	SSEDecrypter();
	virtual ~SSEDecrypter();

	void readSecretsFromJSON(std::string& json);
	std::string decrypt(std::string& ciphertext);
	/**
	 * Set they cipher key
	 * @param key Byte array
	 */
	void setKey(CryptoPP::SecByteBlock& key);
	/**
	 * Set the cipher key
	 * @param hexEncodedKey Hexadecimal encoded string
	 */
	void setKey(std::string& hexEncodedKey);
};

#endif /* INCLUDE_SSEDECRYPTER_H_ */
