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
