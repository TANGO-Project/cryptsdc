#include <sstream>
#include <jsoncpp/json/json.h>
#include "HE2NDecrypter.h"

HE2NDecrypter::HE2NDecrypter()
{
    kappa = 0;
};

HE2NDecrypter::~HE2NDecrypter()
{
};

void HE2NDecrypter::readSecretsFromJSON(std::string& json)
{
	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(json,root);
	if (parsingSuccessful){
		p = NTL::conv<NTL::ZZ>(root["p"].asCString());
		modulus = NTL::conv<NTL::ZZ>(root["modulus"].asCString());
		kappa = NTL::conv<NTL::ZZ>(root["kappa"].asCString());
		NTL::ZZ_p::init(modulus);
		gamma = new NTL::vec_ZZ_p;
		std::istringstream iss(root["gamma"].asString());
		iss >> (*gamma);
	}
};

NTL::ZZ HE2NDecrypter::decrypt(NTL::vec_ZZ_p& ciphertext)
{
    NTL::ZZ_p::init(modulus);
    NTL::ZZ_p partial = (*gamma)*ciphertext;
    NTL::ZZ ret;
    conv(ret,partial);
    return (ret % p) % kappa;
};

