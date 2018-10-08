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

#ifndef HE2NENCRYPTER_H
#define HE2NENCRYPTER_H

#include <NTL/ZZ.h>
#include <NTL/vec_ZZ_p.h>
#include <string>
#include "HE2Encipher.h"

class HE2NEncrypter : public HE2Encipher
{
private:
	/**
	 * Secret cipher parameter
	 */
    NTL::ZZ kappa;
    /**
     * Kappa as a modulo integer. This is a pointer to avoid kappamod being initialised mod zero.
     */
    NTL::ZZ_p* kappamod;
public:
    NTL::vec_ZZ_p encrypt(NTL::ZZ& plaintext) override;
    std::string writeSecretsToJSON() override;

    /**
     * Initialise cipher by generating cipher parameters such that \c p is a \c lambda bit prime,
     * \c q is an \c eta bit prime, and \c kappa is a \c nu bit prime. The public modulus for arithmetic
     * operations on ciphertexts is \c pq
     * @param lambda Bit length of secret modulus \c p (security parameter)
     * @param eta Bit length of secret prime \c q
     * @param nu Bit length of secret prime \c kappa.
     */
    HE2NEncrypter(int lambda, int eta, int nu);
    /**
     * Initialise cipher by generating cipher parameters so that \c p and \c kappa are large enough to
     * accommodate a degree \c d multivariate polynomial computed over \c n \c rhoprime%-bit integers
     * and \c q is large enough so that \c pq cannot be factored in polynomial time.
     * @param n total number of inputs
     * @param d degree of polynomial to compute
     * @param rho bit length of inputs, e.g for 32-bit integers \c rho = 32
     * @param rhoprime The effective entropy (bit lengths) of the inputs after encryption.
     */
    HE2NEncrypter(int n, int d, int rho, int rhoprime);
    virtual ~HE2NEncrypter();
};

#endif
