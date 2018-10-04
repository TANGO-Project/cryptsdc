#include "HE1NDecrypter.h"
#include <json/json.h>
#include <NTL/ZZ_p.h>

void HE1NDecrypter::setKey(NTL::vec_ZZ& key)
{
    p = key[0];
    kappa = key[1];
};

void HE1NDecrypter::readSecretsFromJSON(std::string& json)
{
	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(json,root);
	if (parsingSuccessful){
		p = NTL::conv<NTL::ZZ>(root["p"].asCString());
		kappa = NTL::conv<NTL::ZZ>(root["kappa"].asCString());
	}
};

NTL::ZZ HE1NDecrypter::decrypt(NTL::ZZ_p& ciphertext)
{
	NTL::ZZ ctext = rep(ciphertext);
    return (ctext % p) % kappa;
};

