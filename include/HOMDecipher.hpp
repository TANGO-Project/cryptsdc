#ifndef HOMDECIPHER_HPP
#define HOMDECIPHER_HPP

#include <NTL/ZZ.h>
#include "Decipher.hpp"

template <typename C, typename P>
class HOMDecipher : public Decipher<C,P>
{
protected:
	NTL::ZZ p;

public:
	HOMDecipher(){};
	virtual ~HOMDecipher(){};
};

#endif
