/*
 * Copyright 2018 James Dyer
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 *
 * This is being developed for the TANGO Project: http://tango-project.eu
 */

#include <sstream>
#include <NTL/RR.h>
#include <json/json.h>
#include "HE2Encrypter.h"
#include "Random.h"

HE2Encrypter::HE2Encrypter(int lambda, int eta){
	generateParameters(lambda,eta);
}

HE2Encrypter::HE2Encrypter(int n, int d, int rho)
{
    /* Compute lower bound for p */
	NTL::RR rtwo(2);
	NTL::RR exp1(rho*d);
	NTL::RR nplusone(n+1);
	NTL::RR exp2(d);
	NTL::RR ploBound = pow(rtwo,exp1)*pow(nplusone,exp2);
	NTL::ZZ pLowerBound = to_ZZ(ploBound);

	/* Derive lambda and eta */
	long lambda = NumBits(pLowerBound) + 1;
	long eta = ((lambda * lambda / rho) - lambda);
	generateParameters(lambda,eta);
}

NTL::vec_ZZ_p HE2Encrypter::encrypt(NTL::ZZ& plaintext)
{
    NTL::ZZ_p r = to_ZZ_p(rng->nextBigInteger(q));
    NTL::ZZ_p s = to_ZZ_p(rng->nextBigInteger(modulus));
    NTL::ZZ_p ptext = to_ZZ_p(plaintext);
    NTL::ZZ_p c = ptext + r*(*pmod);
    return ONE_VECTOR*c + (*a)*s;
}

std::string HE2Encrypter::writeSecretsToJSON()
{
	Json::Value root;
	std::ostringstream pStr,modStr,gammaStr;
	pStr << p;
	root["p"] = pStr.str();
	modStr << modulus;
	root["modulus"] = modStr.str();
	gammaStr << (*gamma);
    root["gamma"]=gammaStr.str();
	Json::FastWriter writer;
	return writer.write(root);
}
