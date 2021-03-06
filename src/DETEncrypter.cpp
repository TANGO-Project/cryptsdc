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

#include <iostream>
#include <iterator>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <jsoncpp/json/json.h>
#include "DETEncrypter.h"


DETEncrypter::DETEncrypter() {
	CryptoPP::AutoSeededRandomPool rng;
	key.CleanNew(CryptoPP::AES::MAX_KEYLENGTH);
	rng.GenerateBlock(key, key.size());
	iv.CleanNew(CryptoPP::AES::BLOCKSIZE);
	rng.GenerateBlock(iv, iv.size());
}

std::string DETEncrypter::encrypt(std::string& plaintext) {
	std::string cipher;
	e.SetKeyWithIV(key, key.size(), iv, iv.size());
	CryptoPP::StringSource(plaintext, true,
			new CryptoPP::StreamTransformationFilter(e,
					new CryptoPP::StringSink(cipher)));
	return cipher;
}

std::string DETEncrypter::encrypt(CryptoPP::SecByteBlock& plaintext) {
	std::string cipher;
	e.SetKeyWithIV(key, key.size(), iv, iv.size());
	CryptoPP::ArraySource(plaintext.data(), plaintext.size(), true,
			new CryptoPP::StreamTransformationFilter(e,
					new CryptoPP::StringSink(cipher)));
	return cipher;
}

std::string DETEncrypter::encryptToHex(CryptoPP::SecByteBlock& plaintext) {
	std::string cipher;
	e.SetKeyWithIV(key, key.size(), iv, iv.size());
	CryptoPP::ArraySource(plaintext.data(), plaintext.size(), true,
			new CryptoPP::StreamTransformationFilter(e,
					new CryptoPP::HexEncoder(
							new CryptoPP::StringSink(cipher))));
	return cipher;
}

std::string DETEncrypter::encryptToHex(std::string& plaintext) {
	std::string cipher;
	e.SetKeyWithIV(key, key.size(), iv, iv.size());
	CryptoPP::StringSource(plaintext, true,
			new CryptoPP::StreamTransformationFilter(e,
					new CryptoPP::HexEncoder(
							new CryptoPP::StringSink(cipher))));
	return cipher;
}

CryptoPP::SecByteBlock DETEncrypter::getKey() {
	return key;
}

CryptoPP::SecByteBlock DETEncrypter::getIV() {
	return iv;
}

std::string DETEncrypter::getHexEncodedKey() {
	std::string hexString;
	CryptoPP::ArraySource(key.data(), key.size(), true,
					new CryptoPP::HexEncoder(
							new CryptoPP::StringSink(hexString)));
	return hexString;
}

std::string DETEncrypter::getHexEncodedIV() {
	std::string hexString;
	CryptoPP::ArraySource(iv.data(), iv.size(), true,
					new CryptoPP::HexEncoder(
							new CryptoPP::StringSink(hexString)));
	return hexString;
}

std::string DETEncrypter::writeSecretsToJSON() {
	Json::Value root;
	std::string keyStr = getHexEncodedKey();
	root["key"] = keyStr;
	std::string ivStr = getHexEncodedIV();
	root["iv"] = ivStr;
	Json::FastWriter writer;
	return writer.write(root);
}
