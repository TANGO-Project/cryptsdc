/*
 * GACDEncrypter.cpp
 *
 *  Created on: 25 Jun 2018
 *      Author: scsjd
 */

#include <sstream>
#include <NTL/RR.h>
#include <jsoncpp/json/json.h>
#include "GACDEncrypter.h"

GACDEncrypter::GACDEncrypter(int lambda) {
	k = NTL::RandomPrime_ZZ(lambda, 20);
	NTL::RR kreal = to_RR(k);
	minr = RoundToZZ(sqrt(sqrt(power(kreal,3)))); // minr = k^{3/4}
	maxr = k-minr;
}

NTL::ZZ GACDEncrypter::encrypt(NTL::ZZ& plaintext){
	NTL::ZZ r = rng.nextBigInteger(minr, maxr);
	return plaintext*k+r;
}

std::string GACDEncrypter::writeSecretsToJSON(){
	Json::Value root;
	std::stringstream keyStr;
	keyStr << k;
	root["key"] = keyStr.str();
	Json::FastWriter writer;
	return writer.write(root);
}
