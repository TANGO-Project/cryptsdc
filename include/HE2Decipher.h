#ifndef HE2DECIPHER_H
#define HE2DECIPHER_H

#include <string>
#include <NTL/ZZ.h>
#include <NTL/vec_ZZ_p.h>
#include "HOMDecipher.hpp"

class HE2Decipher : public HOMDecipher<NTL::vec_ZZ_p,NTL::ZZ>
{
protected:
	NTL::ZZ modulus;
	NTL::vec_ZZ_p* gamma; //This is a pointer to avoid gamma being initialised mod zero

public:
	NTL::ZZ decryptFromString(std::string& str);

	HE2Decipher();
	virtual ~HE2Decipher();
};

#endif
