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

#ifndef HOMENCIPHER_HPP
#define HOMENCIPHER_HPP

#include <NTL/ZZ.h>
#include "Encipher.hpp"
#include "Random.h"

/**
 * This abstract class details all the members and methods that are common to the HE\em x algorithms.
 * All of the HE\em x encryption classes derive from and implement this class.
 * @tparam C Ciphertext type
 * @tparam P Plaintext type
 */
template <typename C, typename P> class HOMEncipher : public Encipher<C,P>
{
protected:
	/**
	 * Modulus (=pq) for arithmetic operations on ciphertexts. A public parameter of the cipher.
	 */
	NTL::ZZ modulus;
	/**
	 * A secret parameter of the cipher.
	 */
	NTL::ZZ p;
	/**
	 * A secret parameter of the cipher.
	 */
	NTL::ZZ q;
	/**
	 * Secure random number generator.
	 */
	Random* rng;

	void generateModulus(int lambda, int eta){
		p = NTL::RandomPrime_ZZ(lambda,20);
		q = NTL::RandomPrime_ZZ(eta,20);
		modulus = p*q;
	}

public:
	/**
	 * Initialize the cipher by setting the modulus for arithmetic operations
	 */
	void init(){
		this->rng = new Random();
		NTL::ZZ_p::init(modulus);
	};

	/**
	 * Accessor to retrieve public modulus for arithmetic operations on ciphertexts
	 * @return Modulus
	 */
	NTL::ZZ getModulus(){
		return modulus;
	};

	/**
	 * Write the public cipher parameters to a JSON string
	 * @return JSON string
	 */
	virtual std::string writeParametersToJSON()=0;

	/**
	 * Default constructor
	 */
	HOMEncipher(){
		rng=nullptr;
	};

	/**
	 * Default destructor
	 */
	virtual ~HOMEncipher(){
		delete rng;
	};
};

#endif
