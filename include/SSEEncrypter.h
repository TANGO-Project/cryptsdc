/*
 * Copyright 2018 James Dyer
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 *
 * This is being developed for the TANGO Project: http://tango-project.eu
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
	/**
	 * The 256-bit key for the key generation cipher
	 */
	CryptoPP::SecByteBlock keyGenKey;
	/**
	 * The initialization vector for the key generation cipher
	 */
	CryptoPP::SecByteBlock keyGenIV;
	/**
	 * The 256-bit key for the encryption cipher
	 */
	CryptoPP::SecByteBlock key;
	/**
	 * The encryption cipher. AES is CBC mode.
	 */
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption e;
	/**
	 * The key generation cipher. AES is CBC mode.
	 */
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption keygen;
	/**
	 * The MAC algorithm.
	 */
	CryptoPP::CMAC<CryptoPP::AES> mac;

	/**
	 * Decode a hexadecimal string to a byte array
	 * @param hexString Hexadecimal string
	 * @param bytes Byte array
	 */
	void decodeHexString(std::string& hexString, CryptoPP::SecByteBlock& bytes);
public:
	/**
	 * Encrypts the plaintext word as a triple of a 16-byte intialisation vector, an AES ciphertext, and a MAC tag.
	 * Currently, this triple is implmented as a hex encoded JSON object for convenience. However, it could easily be
	 * altered to return a C++ tuple or a concatenated byte sequence.
	 * @param plaintext A string
	 * @return A JSON object
	 */
	std::string encrypt(std::string& plaintext) override;

	/**
	 * Accessor to return the AES cipher key
	 * @return Key byte sequence
	 */
	CryptoPP::SecByteBlock getKey();
	/**
	 * Accessor to return the key for the deterministic AES instance used for key generation
	 * @return Key byte sequence
	 */
	CryptoPP::SecByteBlock getKeyGenKey();
    /**
     * Convenience method to get the key as a hexadecimal encoded string.
     * @return hexadecimal encoded string
     */
    std::string getHexEncodedKey();
    /**
     * Convenience method to get the key as a hexadecimal encoded string.
     * @return hexadecimal encoded string
     */
    std::string getHexEncodedKeyGenKey();
	/**
	 * This function generates a MAC key using a deterministic cipher (AES with a constant initialisation vector).
	 * This is applied to the input word
	 * @param word Input word
	 * @return A 16 or 32 byte array
	 */
	CryptoPP::SecByteBlock createSearchKey(std::string& word);
	/**
	 * Convenience method to generate and hexadecimal encode the search key
	 * @param word Input word
	 * @return A hexadecimal encoded string
	 */
	std::string createHexEncodedSearchKey(std::string& word);
    std::string writeSecretsToJSON() override;

    /**
     * The constructor generates three random values: a 256-bit cipher key; a 256-bit key for the key
     * generation cipher; and an initialisation vector for the key generation cipher.
     */
	SSEEncrypter();
	/**
	 * Initialises the cipher using pre-existing secrets in the supplied JSON string
	 * @param secrets A JSON string containing the hex encoded cipher keys
	 */
	SSEEncrypter(std::string& secrets);
    virtual ~SSEEncrypter();
};

#endif /* SSEENCRYPTER_H_ */
