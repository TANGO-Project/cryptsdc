#include <sstream>
#include <NTL/ZZ_p.h>
#include <json/json.h>
#include "HE1Encipher.h"

NTL::ZZ HE1Encipher::ONE = NTL::ZZ(1);

HE1Encipher::HE1Encipher()
{
	pmod = nullptr;
};

HE1Encipher::~HE1Encipher()
{
	delete pmod;
};

void HE1Encipher::generateParameters(long lambda, long eta){
	generateModulus(lambda,eta);
	/* Set local modulus to pq */
	NTL::ZZ_p::init(modulus);
	NTL::ZZ_p tmp = NTL::to_ZZ_p(p);
	pmod = new NTL::ZZ_p(tmp);
}


std::string HE1Encipher::writeParametersToJSON()
{
	Json::Value root;
	std::stringstream modStr;
	modStr << modulus;
	root["modulus"] = modStr.str();
	Json::FastWriter writer;
	std::string json = writer.write(root);
	return json;
};
