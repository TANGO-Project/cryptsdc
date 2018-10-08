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

#ifndef HE2DECIPHER_H
#define HE2DECIPHER_H

#include <string>
#include <NTL/ZZ.h>
#include <NTL/vec_ZZ_p.h>
#include "HOMDecipher.hpp"

class HE2Decipher : public HOMDecipher<NTL::vec_ZZ_p,NTL::ZZ>
{
protected:
	/**
	 * The public modulus for modular arithmetic.
	 */
	NTL::ZZ modulus;
	/**
	 * The decryption vector. This is a pointer to avoid gamma being initialised mod zero
	 */
	NTL::vec_ZZ_p* gamma;

public:
	/**
	 * Auxiliary method to decrypt a string respresentation of the 2-vector ciphertext
	 * @param str A string respresentation of the ciphertext
	 * @return A multiprecision integer
	 */
	NTL::ZZ decryptFromString(std::string& str);

	HE2Decipher();
	virtual ~HE2Decipher();
};

#endif
