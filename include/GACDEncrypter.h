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

#ifndef GACDENCRYPTER_H
#define GACDENCRYPTER_H

#include <NTL/ZZ.h>
#include "Encipher.hpp"
#include "Random.h"

class GACDEncrypter : public Encipher<NTL::ZZ,NTL::ZZ>{
private:
	/**
	 * The secret key, \c k, a large integer
	 */
	NTL::ZZ k;
	/**
	 * The minimum value of the random offsets in each ciphertext
	 */
	NTL::ZZ minr;
	/**
	 * The maximum value of the random offsets in each ciphertext
	 */
	NTL::ZZ maxr;
	/**
	 * The pseudorandom number generator
	 */
	Random rng;
public:
	/**
	 * The constructor generates a prime of bit length \c lambda
	 * @param bits Required bit length of key
	 */
	GACDEncrypter(int lambda);
	virtual ~GACDEncrypter(){};
	NTL::ZZ encrypt(NTL::ZZ& plaintext) override;
    std::string writeSecretsToJSON() override;
    /**
     * Static method to return the minimum safe key length given the size of the inputs (\c bits)
     * @param bits Bit length of plaintext
     * @return Minimum key length in bits
     */
    static int getMinimumKeyLength(int bits);
};

#endif
