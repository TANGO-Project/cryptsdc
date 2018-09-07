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
	NTL::ZZ k;
	NTL::ZZ minr;
	NTL::ZZ maxr;
	Random rng;
public:
	GACDEncrypter(int bits);
	virtual ~GACDEncrypter();
	NTL::ZZ encrypt(NTL::ZZ& plaintext) override;
    std::string writeSecretsToJSON() override;
};

#endif
