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

int GACDEncrypter::getMinimumKeyLength(int bits){
	return ceil(8.0*bits/3);
}
