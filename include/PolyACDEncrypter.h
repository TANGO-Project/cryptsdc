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

#ifndef POLYACDENCRYPTER_H
#define POLYACDENCRYPTER_H

#include <NTL/ZZ.h>
#include <NTL/ZZX.h>
#include "Encipher.hpp"

class PolyACDEncrypter : public Encipher<NTL::ZZX,NTL::ZZX>{
private:
	/**
	 * Secret large integer parameter
	 */
	NTL::ZZ k1;
	/**
	 * Secret polynomial
	 */
	NTL::ZZX k2;
	/**
	 * The bit length of the plaintext coefficients
	 */
	int mu;

public:
	PolyACDEncrypter(int lambda, int mu, int d);
	PolyACDEncrypter(int mu, std::string& secrets);
	virtual ~PolyACDEncrypter();
	NTL::ZZX encrypt(NTL::ZZX& plaintext) override;
    NTL::ZZX encrypt(NTL::vec_ZZ& plaintext);
    std::string writeSecretsToJSON() override;
};

#endif
