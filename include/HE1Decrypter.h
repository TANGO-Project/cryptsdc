#ifndef HE1DECRYPTER_H
#define HE1DECRYPTER_H

#include <string>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include "HOMDecipher.hpp"

class HE1Decrypter : public HOMDecipher<NTL::ZZ_p,NTL::ZZ>
{
public:
	void readSecretsFromJSON(std::string& json) override;
	/**
	 * Intialise the cipher by setting the local modulus for arithmetic operations to \c p
	 */
	void init();
	NTL::ZZ decrypt(NTL::ZZ_p& ciphertext) override;
	/**
	 * Set the secret key to the given value
	 * @param key Multiprecision integer
	 */
	void setKey(NTL::ZZ& key);

	HE1Decrypter(){};
	virtual ~HE1Decrypter(){};
};

#endif
