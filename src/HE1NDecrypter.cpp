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

#include "HE1NDecrypter.h"
#include <json/json.h>
#include <NTL/ZZ_p.h>

void HE1NDecrypter::setKey(NTL::vec_ZZ& key)
{
    p = key[0];
    kappa = key[1];
};

void HE1NDecrypter::readSecretsFromJSON(std::string& json)
{
	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(json,root);
	if (parsingSuccessful){
		p = NTL::conv<NTL::ZZ>(root["p"].asCString());
		kappa = NTL::conv<NTL::ZZ>(root["kappa"].asCString());
	}
};

NTL::ZZ HE1NDecrypter::decrypt(NTL::ZZ_p& ciphertext)
{
	NTL::ZZ ctext = rep(ciphertext);
    return (ctext % p) % kappa;
};

