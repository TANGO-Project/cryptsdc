#ifndef HE2ENCIPHER_H
#define HE2ENCIPHER_H

#include <NTL/ZZ.h>
#include <NTL/vec_ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include "HOMEncipher.hpp"

class HE2Encipher : public HOMEncipher<NTL::vec_ZZ_p,NTL::ZZ>
{
protected:
	NTL::vec_ZZ_p* a; //This is a pointer to avoid a being initialised mod zero
	NTL::mat_ZZ_p* R; //This is a pointer to avoid R being initialised mod zero
	NTL::vec_ZZ_p* gamma; //This is a pointer to avoid gamma being initialised mod zero
	NTL::ZZ_p* pmod; //This is a pointer to avoid pmod being initialised mod zero

	void generateParameters(int lambda, int eta);
public:
	static NTL::ZZ ONE;
	static NTL::vec_ZZ_p ONE_VECTOR;

	std::string writeParametersToJSON() override;
	virtual std::string encryptToString(int16_t plaintext);
	virtual std::string encryptToString(int32_t plaintext);
	virtual std::string encryptToString(int64_t plaintext);
	virtual std::string encryptToString(NTL::ZZ& plaintext);

	HE2Encipher();
	virtual ~HE2Encipher();
};

#endif
