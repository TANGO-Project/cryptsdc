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
#include "HE2Decipher.h"

HE2Decipher::HE2Decipher()
{
	modulus = NTL::ZZ::zero();
	gamma = nullptr;
};

HE2Decipher::~HE2Decipher()
{
	delete gamma;
};

NTL::ZZ HE2Decipher::decryptFromString(std::string& str)
{
	NTL::vec_ZZ_p vec;
	NTL::ZZ_p::init(modulus);
	std::istringstream iss(str);
	iss >> vec;
	return decrypt(vec);
};
