/*
 * GACDDecrypter.cpp
 *
 *  Created on: 7 Aug 2018
 *      Author: scsjd
 */

#include <jsoncpp/json/json.h>
#include <NTL/ZZ.h>
#include "GACDDecrypter.h"

GACDDecrypter::GACDDecrypter() {
}

GACDDecrypter::~GACDDecrypter() {
}

NTL::ZZ GACDDecrypter::decrypt(NTL::ZZ& ciphertext){
	return ciphertext/k;
}

void GACDDecrypter::readSecretsFromJSON(std::string& secrets){
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(secrets,root);
	if (parsingSuccessful){
		k = NTL::conv<NTL::ZZ>(root["key"].asCString());
	}
}
