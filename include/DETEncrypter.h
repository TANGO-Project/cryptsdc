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
	/**
	 * The AES cipher key (byte array)
	 */
	CryptoPP::SecByteBlock key;
	/**
	 * AES CBC (Cipher Block Chaining) mode initialization vector (byte array)
	 */
	CryptoPP::SecByteBlock iv;
	/**
	 * CBC mode AES encryption
	 */
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption e;
public:
	std::string encrypt(std::string& plaintext) override;
	/**
	 * A convenience method to encrypt a byte array
	 * @param plaintext A byte array
	 * @return A ciphertext as a byte string
	 */
	std::string encrypt(CryptoPP::SecByteBlock& plaintext);
    /**
     * A convenience method to encrypt to a hexadecimal encoded string
     * @param plaintext A (byte) string
     * @return A hexadecimal encoded string
     */
    std::string encryptToHex(std::string& plaintext);
	/**
	 * A convenience method to encrypt a byte array to a hexadecimal encoded string
	 * @param plaintext A byte array
	 * @return A hexadecimal encoded string
	 */
    std::string encryptToHex(CryptoPP::SecByteBlock& plaintext);

    /**
     * Return the key material as a byte aray
     * @return Byte array
     */
    CryptoPP::SecByteBlock getKey();

    /**
     * Returns the CBC mode initialisation vector as a byte array
     * @return Byte array
     */
    CryptoPP::SecByteBlock getIV();
    /**
     * Convenience method to get the key as a hexadecimal encoded string
     * @return A hexadecimal encoded string
     */
    std::string getHexEncodedKey();
    /**
     * Convenience method to get the initialisation vector as a hexadecimal encoded string
     * @return A hexadecimal encoded string
     */
    std::string getHexEncodedIV();
    std::string writeSecretsToJSON() override;

    /**
     * The constructor generates a random 256-bit key and initialisation vector.
     */
    DETEncrypter();
    virtual ~DETEncrypter(){};
};

#endif
