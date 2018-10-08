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

#include <jsoncpp/json/json.h>
#include <NTL/ZZ.h>
#include "GACDDecrypter.h"

NTL::ZZ GACDDecrypter::decrypt(NTL::ZZ& ciphertext){
	return ciphertext/k;
}

void GACDDecrypter::readSecretsFromJSON(std::string& secrets){
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(secrets,root);
	if (parsingSuccessful){
		k = NTL::conv<NTL::ZZ>(root["key"].asCString());
	}
}
