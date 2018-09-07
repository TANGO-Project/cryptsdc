#ifndef HE1ENCRYPTER_H
#define HE1ENCRYPTER_H

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include "HE1Encipher.h"

class HE1Encrypter : public HE1Encipher
{
public:
	NTL::ZZ_p encrypt(NTL::ZZ& plaintext) override;
	NTL::ZZ& getKey();
	std::string writeSecretsToJSON() override;

	HE1Encrypter(int lambda, int eta);
	HE1Encrypter(int n, int d, int rho);
	virtual ~HE1Encrypter();
};

#endif
