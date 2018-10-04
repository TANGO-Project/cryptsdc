#ifndef HOMDECIPHER_HPP
#define HOMDECIPHER_HPP

#include <NTL/ZZ.h>
#include "Decipher.hpp"

/**
 * This interface details the class members common to all HE\em x algorithms. All HE\em x decryption classes derive from this class.
 * @tparam C Ciphertext type
 * @tparam P Plaintext type
 */
template <typename C, typename P> class HOMDecipher : public Decipher<C,P>
{
protected:
	/**
	 * Secret cipher parameter
	 */
	NTL::ZZ p;

public:
	HOMDecipher(){};
	virtual ~HOMDecipher(){};
};

#endif
