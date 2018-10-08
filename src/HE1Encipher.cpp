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
