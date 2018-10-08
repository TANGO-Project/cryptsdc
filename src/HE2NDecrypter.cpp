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
#include <jsoncpp/json/json.h>
#include "HE2NDecrypter.h"

HE2NDecrypter::HE2NDecrypter()
{
    kappa = 0;
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

