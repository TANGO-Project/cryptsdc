#include <iostream>
#include <sstream>
#include <NTL/RR.h>
#include <json/json.h>
#include "HE1Encrypter.h"

#include "Random.h"

HE1Encrypter::~HE1Encrypter()
{
};

//Generate cipher parameters with p lambda bit prime, q eta bit prime
HE1Encrypter::HE1Encrypter(int lambda, int eta)
{
	generateParameters(lambda,eta);
}

//Generate cipher parameters so that p & q large enough to accommodate degree d multivariate polynomial
//computed over n rho-bit integer inputs
HE1Encrypter::HE1Encrypter(int n, int d, int rho)
{
	NTL::RR two = NTL::RR(2);
	NTL::RR exp1 = NTL::RR(rho*d);
	NTL::RR nplusone = NTL::RR(n+1);
	NTL::RR exp2 = NTL::RR(d);
	NTL::RR ploBound = pow(two,exp1)*pow(nplusone,exp2);
	NTL::ZZ pLowerBound;
	conv(pLowerBound,ploBound);
	long lambda = NumBits(pLowerBound) + 1;
	long eta = ((lambda * lambda / rho) - lambda);
	generateParameters(lambda,eta);
};

NTL::ZZ_p HE1Encrypter::encrypt(NTL::ZZ& plaintext)
{
	NTL::ZZ_p r = to_ZZ_p(rng->nextBigInteger(ONE, q));
	NTL::ZZ_p ptext = to_ZZ_p(plaintext);
	return ptext+r*(*pmod);
};

NTL::ZZ& HE1Encrypter::getKey()
{
	return p;
};

std::string HE1Encrypter::writeSecretsToJSON()
{
	Json::Value root;
	std::stringstream pStr;
	pStr << p;
	root["p"] = pStr.str();
	Json::FastWriter writer;
	return writer.write(root);
};
