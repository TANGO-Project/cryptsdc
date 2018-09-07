/*
 * SSEEncrypter.cpp
 *
 *  Created on: 15 Aug 2018
 *      Author: scsjd
 */

#include <iostream>
#include <iterator>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <jsoncpp/json/json.h>
#include "SSEEncrypter.h"

SSEEncrypter::SSEEncrypter() {
	CryptoPP::AutoSeededRandomPool rng;
	key.CleanNew(CryptoPP::AES::MAX_KEYLENGTH);
	rng.GenerateBlock(key, key.size());
	keyGenKey.CleanNew(CryptoPP::AES::MAX_KEYLENGTH);
	rng.GenerateBlock(keyGenKey, keyGenKey.size());
	keyGenIV.CleanNew(CryptoPP::AES::BLOCKSIZE);
}

SSEEncrypter::SSEEncrypter(std::string& secrets){
	Json::Value root;
	Json::Reader reader;
	key.CleanNew(CryptoPP::AES::MAX_KEYLENGTH);
	keyGenKey.CleanNew(CryptoPP::AES::MAX_KEYLENGTH);
	keyGenIV.CleanNew(CryptoPP::AES::BLOCKSIZE);
	if(reader.parse(secrets, root)){
		std::string hexEncodedKey = root["key"].asString();
		decodeHexString(hexEncodedKey, key);
		std::string hexEncodedKeyGenKey = root["keygenkey"].asString();
		decodeHexString(hexEncodedKeyGenKey, keyGenKey);
	}
}

SSEEncrypter::~SSEEncrypter() {
}

CryptoPP::SecByteBlock SSEEncrypter::createSearchKey(std::string& word){
	int outputBlocks = word.size()/CryptoPP::AES::BLOCKSIZE;
	if (word.size() % CryptoPP::AES::BLOCKSIZE) outputBlocks++;
	int outputSize = outputBlocks*CryptoPP::AES::BLOCKSIZE;
	CryptoPP::SecByteBlock cipher(nullptr,outputSize);
	keygen.SetKeyWithIV(keyGenKey, keyGenKey.size(), keyGenIV, keyGenIV.size());
	CryptoPP::StringSource(word, true,
			new CryptoPP::StreamTransformationFilter(keygen,
					new CryptoPP::ArraySink(cipher,cipher.size())));
	if (outputSize>CryptoPP::AES::MAX_KEYLENGTH){
		//get last 32 bytes of ciphertext: ensures that word <= MAX_KEYLENGTH bytes does not generate
		//same key as word > MAX_KEYLENGTH bytes
		CryptoPP::SecByteBlock lastbytes(nullptr,CryptoPP::AES::MAX_KEYLENGTH);
		std::copy(cipher.begin()+(cipher.size()-CryptoPP::AES::MAX_KEYLENGTH),cipher.end(),lastbytes.begin());
		return lastbytes;
	}
	else return cipher;
}

std::string SSEEncrypter::createHexEncodedSearchKey(std::string& word){
	std::string hexString;
	CryptoPP::SecByteBlock searchKey = createSearchKey(word);
	CryptoPP::ArraySource ss(searchKey.data(), searchKey.size(), true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(hexString)
		) // HexEncoder
	); // ArraySource
	return hexString;
}

void SSEEncrypter::decodeHexString(std::string& hexString, CryptoPP::SecByteBlock& bytes){
	CryptoPP::StringSource ss(hexString, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::ArraySink(bytes,bytes.size())
		) // HexDecoder
	); // StringSource
}

std::string SSEEncrypter::encrypt(std::string& plaintext){
	Json::Value root;
	//Generate random IV
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::SecByteBlock iv(nullptr,CryptoPP::AES::BLOCKSIZE);
	rng.GenerateBlock(iv, iv.size());
	//Hex encode IV and add to JSON
	std::string hexEncodedIV;
	CryptoPP::ArraySource as(iv, iv.size(), true,
	    new CryptoPP::HexEncoder(
	        new CryptoPP::StringSink(hexEncodedIV)
	    ) // HexEncoder
	); // StringSource
	root["iv"]=hexEncodedIV;
	//Encrypt plaintext using key and IV, hex encode, and add to JSON
	e.SetKeyWithIV(key, key.size(), iv, iv.size());
	std::string payload;
	CryptoPP::StringSource ss(plaintext, true,
		new CryptoPP::StreamTransformationFilter(e,
			new CryptoPP::StringSink(payload)
		)
	);
	std::string hexEncodedPayload;
	CryptoPP::StringSource ss2(payload, true,
	    new CryptoPP::HexEncoder(
	        new CryptoPP::StringSink(hexEncodedPayload)
	    ) // HexEncoder
	); // StringSource
	root["payload"]=hexEncodedPayload;
	//Create searchKey
	CryptoPP::SecByteBlock searchKey = createSearchKey(plaintext);
	//Create CMAC tag using searchKey and add to JSON
	std::string tag;
	mac.SetKey(searchKey.data(), searchKey.size());
	CryptoPP::StringSource(payload, true,
			new CryptoPP::HashFilter(mac,
				new CryptoPP::HexEncoder(
						new CryptoPP::StringSink(tag))));
	root["tag"]=tag;
	//Write JSON object to string
	Json::FastWriter writer;
	std::string json = writer.write(root);
	return json;
}

CryptoPP::SecByteBlock SSEEncrypter::getKey(){
	return key;
}

CryptoPP::SecByteBlock SSEEncrypter::getKeyGenKey(){
	return keyGenKey;
}

std::string SSEEncrypter::getHexEncodedKey(){
	std::string hexEncodedKey;
	CryptoPP::ArraySource as(key, key.size(), true,
	    new CryptoPP::HexEncoder(
	        new CryptoPP::StringSink(hexEncodedKey)
	    ) // HexEncoder
	); // StringSource
	return hexEncodedKey;
}

std::string SSEEncrypter::getHexEncodedKeyGenKey(){
	std::string hexEncodedKey;
	CryptoPP::ArraySource as(keyGenKey, keyGenKey.size(), true,
	    new CryptoPP::HexEncoder(
	        new CryptoPP::StringSink(hexEncodedKey)
	    ) // HexEncoder
	); // StringSource
	return hexEncodedKey;
}

std::string SSEEncrypter::writeSecretsToJSON(){
	Json::Value root;
	root["key"]=getHexEncodedKey();
	root["keygenkey"]=getHexEncodedKeyGenKey();
	Json::FastWriter writer;
	std::string json = writer.write(root);
	return json;

}

