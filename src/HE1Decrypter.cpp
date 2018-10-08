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

#include "HE1Decrypter.h"
#include <json/json.h>

void HE1Decrypter::readSecretsFromJSON(std::string& json)
{
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(json,root);
	if (parsingSuccessful){
		p = NTL::conv<NTL::ZZ>(root["p"].asCString());
	}
};

void HE1Decrypter::init()
{
	NTL::ZZ_p::init(p);
};

NTL::ZZ HE1Decrypter::decrypt(NTL::ZZ_p& ciphertext)
{
	NTL::ZZ ctext = NTL::rep(ciphertext);
	return ctext % p;
};

void HE1Decrypter::setKey(NTL::ZZ& key)
{
	p = key;
};

