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

#include <iostream>
#include <sstream>
#include <NTL/RR.h>
#include <NTL/ZZ_p.h>
#include <json/json.h>
#include "HE1Encrypter.h"

#include "Random.h"

HE1Encrypter::HE1Encrypter(int lambda, int eta)
{
	generateParameters(lambda,eta);
}

HE1Encrypter::HE1Encrypter(int n, int d, int rho)
{
	NTL::RR two(2);
	NTL::RR exp1(rho*d);
	NTL::RR nplusone(n+1);
	NTL::RR exp2(d);
	NTL::RR ploBound;
	ploBound = pow(two,exp1)*pow(nplusone,exp2);
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
