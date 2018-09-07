#include <sstream>
#include <jsoncpp/json/json.h>
#include "HE2Decrypter.h"

HE2Decrypter::~HE2Decrypter()
{
}

HE2Decrypter::HE2Decrypter()
{
}

void HE2Decrypter::readSecretsFromJSON(std::string& json)
{
	Json::Value root;   // will contain the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(json,root);
	if (parsingSuccessful){
		p = NTL::conv<NTL::ZZ>(root["p"].asCString());
		modulus = NTL::conv<NTL::ZZ>(root["modulus"].asCString());
		NTL::ZZ_p::init(modulus);
		gamma = new NTL::vec_ZZ_p;
		std::istringstream iss(root["gamma"].asString());
		iss >> (*gamma);
	}
}

NTL::ZZ HE2Decrypter::decrypt(NTL::vec_ZZ_p& ciphertext)
{
    NTL::ZZ_p::init(modulus);
    NTL::ZZ_p decrypt = (*gamma)*ciphertext;
    NTL::ZZ ret;
    conv(ret,decrypt);
    return ret % p;
}



