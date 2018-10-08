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
	/**
	 * AES key (byte array)
	 */
	CryptoPP::SecByteBlock key;
	/**
	 * AES initialisation vector (byte array)
	 */
	CryptoPP::SecByteBlock iv;
	/**
	 * CBC mode AES decryption.
	 */
	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption d;
public:
    void readSecretsFromJSON(std::string& reader) override;
    std::string decrypt(std::string& ciphertext) override;
    /**
     * Convenience method to decrypt a byte array
     * @param ciphertext byte array
     * @return plaintext byte string
     */
    std::string decrypt(CryptoPP::SecByteBlock& ciphertext);
    /**
     * Convenience method to decrypt a hexadecimal encoded string
     * @param hexString Hexadecimal encoded string
     * @return plaintext byte string
     */
    std::string decryptFromHex(std::string& hexString);
    /**
     * Accessor to set the AES cipher key and initialisation vector
     * @param key AES key (byte array)
     * @param iv AES initiialisation vector (byte array)
     */
    void setKeyWithIV(CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv);
    /**
     * Accessor to set the AES cipher key and initialisation vector
     * @param hexkey Hexadecimal encoded AES key
     * @param hexiv Hexadecimal encoded initialisation vector
     */
    void setKeyWithIV(std::string& hexkey, std::string& hexiv);

    DETDecrypter(){};
    virtual ~DETDecrypter(){};
};

#endif
