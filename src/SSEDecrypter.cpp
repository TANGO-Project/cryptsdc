/*
 * SSEDecrypter.cpp
 *
 *  Created on: 15 Aug 2018
 *      Author: scsjd
 */

#include <iostream>
#include <jsoncpp/json/json.h>
#include <cryptopp/hex.h>
#include "SSEDecrypter.h"

SSEDecrypter::SSEDecrypter() {
	key.CleanNew(CryptoPP::AES::MAX_KEYLENGTH);
}

SSEDecrypter::~SSEDecrypter() {
}

void SSEDecrypter::decodeHexString(std::string& hexString, CryptoPP::SecByteBlock& bytes){
	CryptoPP::StringSource ss(hexString, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::ArraySink(bytes,bytes.size())
		) // HexDecoder
	); // StringSource
}

void SSEDecrypter::readSecretsFromJSON(std::string& json){
	Json::Value root;
	Json::Reader reader;
	if(reader.parse(json, root)){
		std::string hexEncodedKey = root["key"].asString();
		decodeHexString(hexEncodedKey,key);
	}
}

std::string SSEDecrypter::decrypt(std::string& ciphertext){
	Json::Value root;
	Json::Reader reader;
	CryptoPP::SecByteBlock iv(nullptr,CryptoPP::AES::BLOCKSIZE);
	if(reader.parse(ciphertext, root)){
		std::string hexEncodedIV = root["iv"].asString();
		std::string hexEncodedPayload = root["payload"].asString();
		decodeHexString(hexEncodedIV,iv);
		d.SetKeyWithIV(key, key.size(), iv, iv.size());
		std::string plaintext;
		CryptoPP::StringSource ss(hexEncodedPayload, true,
			new CryptoPP::HexDecoder(
				new CryptoPP::StreamTransformationFilter(d,
					new CryptoPP::StringSink(plaintext)
				)
			) // HexDecoder
		); // StringSource
		return plaintext;
	}
	else throw CryptoPP::InvalidDataFormat("Could not parse ciphertext.");
}

void SSEDecrypter::setKey(CryptoPP::SecByteBlock& key){
	this->key = key;
}

void SSEDecrypter::setKey(std::string& hexEncodedKey){
	decodeHexString(hexEncodedKey,key);
}
