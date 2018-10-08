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

#include <iterator>
#include <iostream>
#include <json/json.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include "DETDecrypter.h"

void DETDecrypter::readSecretsFromJSON(std::string& json) {
	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(json, root);
	if (parsingSuccessful) {
		std::string keyStr = root["key"].asString();
		std::string ivStr = root["iv"].asString();
		setKeyWithIV(keyStr,ivStr);
	}
}

std::string DETDecrypter::decrypt(std::string& ciphertext) {
	std::string plain;
	CryptoPP::StringSource(ciphertext, true,
			new CryptoPP::StreamTransformationFilter(d,
					new CryptoPP::StringSink(plain)));
	return plain;
}

std::string DETDecrypter::decrypt(CryptoPP::SecByteBlock& ciphertext) {
	std::string plain;
	CryptoPP::ArraySource(ciphertext.data(), ciphertext.size(), true,
			new CryptoPP::StreamTransformationFilter(d,
					new CryptoPP::StringSink(plain)));
	return plain;
}

std::string DETDecrypter::decryptFromHex(std::string& hexString) {
	std::string plain;
	CryptoPP::StringSource(hexString, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StreamTransformationFilter(d,
				new CryptoPP::StringSink(plain))));
	return plain;
}

void DETDecrypter::setKeyWithIV(CryptoPP::SecByteBlock& key,
		CryptoPP::SecByteBlock& iv) {
	this->key = key;
	this->iv = iv;
	d.SetKeyWithIV(key, key.size(), iv, iv.size());
}

void DETDecrypter::setKeyWithIV(std::string& hexkey, std::string& hexiv) {
	key.CleanNew(CryptoPP::AES::MAX_KEYLENGTH);
	CryptoPP::StringSource(hexkey, true,
					new CryptoPP::HexDecoder(
							new CryptoPP::ArraySink(key.data(),key.size())));
	iv.CleanNew(CryptoPP::AES::BLOCKSIZE);
	CryptoPP::StringSource(hexiv, true,
					new CryptoPP::HexDecoder(
							new CryptoPP::ArraySink(iv.data(),iv.size())));
	d.SetKeyWithIV(key, key.size(), iv, iv.size());
}

