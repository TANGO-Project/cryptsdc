#ifndef HE2ENCRYPTER_H
#define HE2ENCRYPTER_H

#include <string>
#include <NTL/ZZ.h>
#include <NTL/vec_ZZ_p.h>
#include "HE2Encipher.h"

class HE2Encrypter : public HE2Encipher
{
public:
    std::string writeSecretsToJSON() override;
    NTL::vec_ZZ_p encrypt(NTL::ZZ& plaintext) override;

	/**
	 * Initialise cipher by generating cipher parameters such that \c p is a \c lambda bit prime
	 * and \c q is an \c eta bit prime. The public modulus for arithmetic operations on ciphertexts is \c pq
	 * @param lambda Bit length of secret modulus \c p (security parameter)
	 * @param eta Bit length of secret prime \c q.
	 */
    HE2Encrypter(int lambda, int eta);
	/**
	 * Initialise cipher by generating cipher parameters so that \c p is large enough to
	 * accommodate a degree \c d multivariate polynomial computed over \c n \c rho%-bit integer inputs
	 * and \c q is large enough so that pq cannot be factored in polynomial time.
	 * @param n total number of inputs
	 * @param d degree of polynomial to compute
	 * @param rho bit length of inputs, e.g for 32-bit integers \c rho = 32
	 */
    HE2Encrypter(int n, int d, int rho);

    virtual ~HE2Encrypter(){};
};

#endif
