/*
 * PACDEncrypter.h
 *
 *  Created on: 25 Jun 2018
 *      Author: James Dyer
 *
 *
 *  Implementation of Poly ACD based OPE scheme.
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
