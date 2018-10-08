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

#ifndef HE2ENCIPHER_H
#define HE2ENCIPHER_H

#include <NTL/ZZ.h>
#include <NTL/vec_ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include "HOMEncipher.hpp"

class HE2Encipher : public HOMEncipher<NTL::vec_ZZ_p,NTL::ZZ>
{
protected:
	/**
	 * The secret vector of the cipher. This is a pointer to avoid a being initialised mod zero.
	 */
	NTL::vec_ZZ_p* a;
	/**
	 * The public re-encryption matrix. This is a pointer to avoid R being initialised mod zero.
	 */
	NTL::mat_ZZ_p* R;
	/**
	 * The secret decryption vector. This is a pointer to avoid gamma being initialised mod zero.
	 */
	NTL::vec_ZZ_p* gamma;
	/**
	 * The secret key as a modulo integer. This is for convenience to avoid having to convert multiple times. This is a pointer to avoid pmod being initialised mod zero.
	 */
	NTL::ZZ_p* pmod;

	/**
	 * Generate the cipher parameters common to the HE2 and HE2N ciphers. This method generates \c a, \c gamma, and \c R.
	 * @param lambda The bit length of \c p
	 * @param eta The bit length of \c q where the modulus is \c pq
	 */
	void generateParameters(int lambda, int eta);
public:
	/**
	 * One as a multiprecision integer
	 */
	static NTL::ZZ ONE;
	/**
	 * The vector [1 1]^T
	 */
	static NTL::vec_ZZ_p ONE_VECTOR;

	std::string writeParametersToJSON() override;
	/**
	 * Convenience method to encrypt a 16-bit integer to a string representation of the ciphertext
	 * @param plaintext A 16-bit integer
	 * @return A string representation of the ciphertext
	 */
	virtual std::string encryptToString(int16_t plaintext);
	/**
	 * Convenience method to encrypt a 32-bit integer to a string representation of the ciphertext
	 * @param plaintext A 32-bit integer
	 * @return A string representation of the ciphertext
	 */
	virtual std::string encryptToString(int32_t plaintext);
	/**
	 * Convenience method to encrypt a 64-bit integer to a string representation of the ciphertext
	 * @param plaintext A 64-bit integer
	 * @return A string representation of the ciphertext
	 */
	virtual std::string encryptToString(int64_t plaintext);
	/**
	 * Convenience method to encrypt to a string representation of the ciphertext
	 * @param plaintext A multiprecision integer
	 * @return A string representation of the ciphertext
	 */
	virtual std::string encryptToString(NTL::ZZ& plaintext);

	HE2Encipher();
	virtual ~HE2Encipher();
};

#endif
