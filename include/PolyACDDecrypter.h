/*
 * PACDDecrypter.h
 *
 *  Created on: 26 Jun 2018
 *      Author: scsjd
 */

#ifndef POLYACDDECRYPTER_H
#define POLYACDDECRYPTER_H

#include <NTL/ZZ.h>
#include <NTL/ZZX.h>
#include <NTL/vec_ZZ.h>
#include "Decipher.hpp"

class PolyACDDecrypter : public Decipher<NTL::ZZX,NTL::ZZX> {
private:
	/**
	 * Secret large integer parameter
	 */
	NTL::ZZ k1;
	/**
	 * Secret polynomial
	 */
	NTL::ZZX k2;

public:
	PolyACDDecrypter();
	virtual ~PolyACDDecrypter();
	void readSecretsFromJSON(std::string& string) override;
	NTL::ZZX decrypt(NTL::ZZX& ciphertext) override;
};

#endif
