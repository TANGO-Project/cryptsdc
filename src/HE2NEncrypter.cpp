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
#include "HE2NEncrypter.h"
#include "Random.h"

HE2NEncrypter::~HE2NEncrypter()
{
	delete kappamod;
};

HE2NEncrypter::HE2NEncrypter(int lambda, int eta, int nu){
	kappa = NTL::RandomPrime_ZZ(nu,20);
	generateParameters(lambda,eta);
	NTL::ZZ_p::init(modulus);
	NTL::ZZ_p ktmp = NTL::to_ZZ_p(kappa);
	kappamod = new NTL::ZZ_p(ktmp);
}

HE2NEncrypter::HE2NEncrypter(int n, int d, int rho, int rhoprime)
{
    /* Compute lower bound for kappa */
	NTL::RR rtwo = NTL::RR(2);
	NTL::RR exp1 = NTL::RR(rho*d);
	NTL::RR nplusone = NTL::RR(n+1);
	NTL::RR exp2 = NTL::RR(d);
	NTL::RR exp3 = NTL::RR(rho);
	NTL::RR kloBound = pow(rtwo,exp1)*pow(nplusone,exp2);
	NTL::ZZ kappaLowerBound = to_ZZ(kloBound);
	/* Generate kappa as prime > lower bound */
	long nu = NumBits(kappaLowerBound)+1;
	kappa = NTL::RandomPrime_ZZ(nu,20);

	/*compute lower bound for p */
	NTL::RR kappareal = to_RR(kappa);
	NTL::RR ploBound = pow(pow(rtwo,exp3)+pow(kappareal,rtwo),exp2)*pow(nplusone,exp2);
	NTL::ZZ pLowerBound = to_ZZ(ploBound);

	/* Generate p and q */
	long lambda = NumBits(pLowerBound) + 1;
	long eta = ((lambda * lambda / rho) - lambda);

	generateParameters(lambda,eta);
	NTL::ZZ_p::init(modulus);
	NTL::ZZ_p ktmp = NTL::to_ZZ_p(kappa);
	kappamod = new NTL::ZZ_p(ktmp);
};

NTL::vec_ZZ_p HE2NEncrypter::encrypt(NTL::ZZ& plaintext)
{
    NTL::ZZ_p r = NTL::to_ZZ_p(rng->nextBigInteger(q));
    NTL::ZZ_p s = NTL::to_ZZ_p(rng->nextBigInteger(kappa));
    NTL::ZZ_p t = NTL::to_ZZ_p(rng->nextBigInteger(modulus));
    NTL::ZZ_p ptext = NTL::to_ZZ_p(plaintext);
    NTL::ZZ_p c = ptext + r*(*pmod) +s*(*kappamod);
    return ONE_VECTOR*c + (*a)*t;
};

std::string HE2NEncrypter::writeSecretsToJSON()
{
	Json::Value root;
	std::ostringstream pStr,modStr,kappaStr,gammaStr;
	pStr << p;
	root["p"] = pStr.str();
	modStr << modulus;
	root["modulus"] = modStr.str();
	kappaStr << kappa;
	root["kappa"] = kappaStr.str();
	gammaStr << (*gamma);
    root["gamma"]=gammaStr.str();
	Json::FastWriter writer;
	return writer.write(root);
};

