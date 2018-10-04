#ifndef HE2DECIPHER_H
#define HE2DECIPHER_H

#include <string>
#include <NTL/ZZ.h>
#include <NTL/vec_ZZ_p.h>
#include "HOMDecipher.hpp"

class HE2Decipher : public HOMDecipher<NTL::vec_ZZ_p,NTL::ZZ>
{
protected:
	/**
	 * The public modulus for modular arithmetic.
	 */
	NTL::ZZ modulus;
	/**
	 * The decryption vector. This is a pointer to avoid gamma being initialised mod zero
	 */
	NTL::vec_ZZ_p* gamma;

public:
	/**
	 * Auxiliary method to decrypt a string respresentation of the 2-vector ciphertext
	 * @param str A string respresentation of the ciphertext
	 * @return A multiprecision integer
	 */
	NTL::ZZ decryptFromString(std::string& str);

	HE2Decipher();
	virtual ~HE2Decipher();
};

#endif
