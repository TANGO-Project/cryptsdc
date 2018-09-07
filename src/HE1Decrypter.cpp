#include "HE1Decrypter.h"
#include <json/json.h>

HE1Decrypter::HE1Decrypter()
{
};

HE1Decrypter::~HE1Decrypter()
{
};

void HE1Decrypter::readSecretsFromJSON(std::string& json)
{
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(json,root);
	if (parsingSuccessful){
		p = NTL::conv<NTL::ZZ>(root["p"].asCString());
	}
};

void HE1Decrypter::init()
{
	NTL::ZZ_p::init(p);
};

NTL::ZZ HE1Decrypter::decrypt(NTL::ZZ_p& ciphertext)
{
	NTL::ZZ ctext = NTL::rep(ciphertext);
	return ctext % p;
};

void HE1Decrypter::setKey(NTL::ZZ& key)
{
	p = key;
};

