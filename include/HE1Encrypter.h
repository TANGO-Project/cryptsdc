#ifndef HE1ENCRYPTER_H
#define HE1ENCRYPTER_H

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include "HE1Encipher.h"

class HE1Encrypter : public HE1Encipher
{
public:
	NTL::ZZ_p encrypt(NTL::ZZ& plaintext) override;
	/**
	 * Accessor to retrieve the secret modulus, \c p
	 * @return Secret modulus \c p
	 */
	NTL::ZZ& getKey();
	std::string writeSecretsToJSON() override;

	/**
	 * Initialise cipher by generating cipher parameters such that \c p is a \c lambda bit prime
	 * and \c q is an \c eta bit prime. The public modulus for arithmetic operations on ciphertexts is \c pq
	 * @param lambda Bit length of secret modulus \c p (security parameter)
	 * @param eta Bit length of secret prime \c q.
	 */
	HE1Encrypter(int lambda, int eta);
	/**
	 * Initialise cipher by generating cipher parameters so that \c p is large enough to
	 * accommodate a degree \c d multivariate polynomial computed over \c n \c rho%-bit integer inputs
	 * and \c q is large enough so that \c pq cannot be factored in polynomial time.
	 * @param n total number of inputs
	 * @param d degree of polynomial to compute
	 * @param rho bit length of inputs, e.g for 32-bit integers \c rho = 32
	 */
	HE1Encrypter(int n, int d, int rho);
	virtual ~HE1Encrypter();
};

#endif
