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

#ifndef HE1DECRYPTER_H
#define HE1DECRYPTER_H

#include <string>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include "HOMDecipher.hpp"

class HE1Decrypter : public HOMDecipher<NTL::ZZ_p,NTL::ZZ>
{
public:
	void readSecretsFromJSON(std::string& json) override;
	/**
	 * Intialise the cipher by setting the local modulus for arithmetic operations to \c p
	 */
	void init();
	NTL::ZZ decrypt(NTL::ZZ_p& ciphertext) override;
	/**
	 * Set the secret key to the given value
	 * @param key Multiprecision integer
	 */
	void setKey(NTL::ZZ& key);

	HE1Decrypter(){};
	virtual ~HE1Decrypter(){};
};

#endif
