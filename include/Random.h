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

#ifndef RANDOM_H
#define RANDOM_H

#include <NTL/ZZ.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/secblock.h>
#include "isaac.hpp"

/**
 * Implements support for uniformly distributed random arbitrary precision integers.
 * We use the ISAAC cipher as our PRNG function.
 *
 * ISAAC has been designed to be cryptographically secure if seeded properly. */
class Random
{
private:
	/**
	 * The ISAAC cipher is used to generate PRNs.
	 */
	QTIsaac<>* rng;

public:
	/**
	 * Generate a multiprecision integer in the range 0 to \c range-1
	 * @param range The maximum value of a random integer produced is \c range-1
	 * @return A multiprecision integer in the range 0 to \c range-1
	 */
	NTL::ZZ nextBigInteger(NTL::ZZ& range);
    /**
     * Generate a multiprecision integer in the range \c min to \c max-1
     * @param min The minimum value of a random integer produced
     * @param max The maximum value of a random integer produced is \c max-1
     * @return A multiprecision integer in the range \c min to \c max-1
     */
    NTL::ZZ nextBigInteger(NTL::ZZ& min, NTL::ZZ& max);

    /**
     * Default constructor. Uses device random data to seed the ISAAC cipher.
     */
    Random();
    /**
     * Uses the supplied byte array to seed the ISAAC cipher
     * @param seed A byte array
     */
    Random(CryptoPP::SecByteBlock& seed);
    virtual ~Random();
};

#endif
