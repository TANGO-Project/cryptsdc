#include <sstream>
#include <NTL/RR.h>
#include <json/json.h>
#include "HE1NEncrypter.h"
#include "Random.h"

/**
 * Default destructor
 */
HE1NEncrypter::~HE1NEncrypter()
{
	delete kappamod;
}

HE1NEncrypter::HE1NEncrypter(int lambda, int eta, int nu){
	kappa = NTL::RandomPrime_ZZ(nu, 20);
	generateParameters(lambda,eta);
	NTL::ZZ_p::init(modulus);
	NTL::ZZ_p tmp = to_ZZ_p(kappa);
	kappamod = new NTL::ZZ_p(tmp);
}

HE1NEncrypter::HE1NEncrypter(int n, int d, int rho, int rhoprime)
{
	NTL::RR two(2);
	NTL::RR exp1(rho*d);
	NTL::RR nplusone(n+1);
	NTL::RR exp2(d);
	NTL::RR exp3(rho);
	NTL::RR kloBound = pow(two,exp1)*pow(nplusone,exp2);
	NTL::ZZ kappaLowerBound;
	conv(kappaLowerBound,kloBound);
	long nu = NumBits(kappaLowerBound)+1;
	kappa = NTL::RandomPrime_ZZ(nu, 20);
	NTL::RR kappareal = to_RR(kappa);
	NTL::RR ploBound = pow(pow(two,exp3)+pow(kappareal,two),exp2)*pow(nplusone,exp2);
	NTL::ZZ pLowerBound;
	conv(pLowerBound,ploBound);
	long lambda = NumBits(pLowerBound) + 1;
	long eta = ((lambda * lambda / rhoprime) - lambda);
	generateParameters(lambda,eta);
	NTL::ZZ_p::init(modulus);
	NTL::ZZ_p tmp = to_ZZ_p(kappa);
	kappamod = new NTL::ZZ_p(tmp);
};

HE1NEncrypter::HE1NEncrypter(std::string& secrets, std::string& parameters){
	Json::Value rootP;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(parameters,rootP);
	if (parsingSuccessful){
		modulus = NTL::conv<NTL::ZZ>(rootP["modulus"].asCString());
		NTL::ZZ_p::init(modulus);
		Json::Value rootS;
		bool parsingSuccessful = reader.parse(secrets,rootS);
		if (parsingSuccessful){
			p = NTL::conv<NTL::ZZ>(rootS["p"].asCString());
			NTL::ZZ_p ptmp = to_ZZ_p(p);
			pmod = new NTL::ZZ_p(ptmp);
			q = modulus/p;
			kappa = NTL::conv<NTL::ZZ>(rootS["kappa"].asCString());
			NTL::ZZ_p ktmp = to_ZZ_p(kappa);
			kappamod = new NTL::ZZ_p(ktmp);
		}
	}
}

NTL::vec_ZZ HE1NEncrypter::getKey()
{
	NTL::vec_ZZ ret;
	ret.append(p);
	ret.append(kappa);
    return ret;
};

NTL::ZZ_p HE1NEncrypter::encrypt(NTL::ZZ& plaintext)
{
    NTL::ZZ_p r = to_ZZ_p(rng->nextBigInteger(ONE, q));
    NTL::ZZ_p s = to_ZZ_p(rng->nextBigInteger(kappa));
    NTL::ZZ_p ptext = to_ZZ_p(plaintext);
    return ptext+r*(*pmod)+s*(*kappamod);
};

std::string HE1NEncrypter::writeSecretsToJSON()
{
	Json::Value root;
	std::stringstream pStr, kappaStr;
	pStr << p;
	kappaStr << kappa;
	root["p"] = pStr.str();
	root["kappa"] = kappaStr.str();
	Json::FastWriter writer;
	return writer.write(root);
};
