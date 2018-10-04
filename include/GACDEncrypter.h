/*
 * GACDEncrypter.h
 *
 *  Created on: 25 Jun 2018
 *      Author: scsjd
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
	 * The constructor generates a prime with 8/3 as many bits as \c bits
	 * @param bits Bit length of inputs
	 */
	GACDEncrypter(int bits);
	virtual ~GACDEncrypter(){};
	NTL::ZZ encrypt(NTL::ZZ& plaintext) override;
    std::string writeSecretsToJSON() override;
};

#endif
