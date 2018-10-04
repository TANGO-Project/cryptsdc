#ifndef HE1ENCIPHER_H
#define HE1ENCIPHER_H

#include <string>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>

#include "HOMEncipher.hpp"

class HE1Encipher : public HOMEncipher<NTL::ZZ_p,NTL::ZZ>
{
protected:
	/**
	 * The secret key, \c p, as a modulo integer. This is a pointer to avoid pmod being initialised mod zero.
	 */
	NTL::ZZ_p* pmod;
	/**
	 * Generate the cipher parameters common to HE1 and HE1N cipher
	 * @param lambda The bit length of the secret key, p
	 * @param eta The bit length of the prime q where the public modulus is pq
	 */
	void generateParameters(long lambda, long eta);
public:
	/**
	 * The number one as a multiprecision integer
	 */
	static NTL::ZZ ONE;

	std::string writeParametersToJSON() override;
	HE1Encipher();
	virtual ~HE1Encipher();
};

#endif
