#include <sstream>
#include <jsoncpp/json/json.h>
#include "HE2Decipher.h"

HE2Decipher::HE2Decipher()
{
	modulus = NTL::ZZ::zero();
	gamma = nullptr;
};

HE2Decipher::~HE2Decipher()
{
	delete gamma;
};

NTL::ZZ HE2Decipher::decryptFromString(std::string& str)
{
	NTL::vec_ZZ_p vec;
	NTL::ZZ_p::init(modulus);
	std::istringstream iss(str);
	iss >> vec;
	return decrypt(vec);
};
