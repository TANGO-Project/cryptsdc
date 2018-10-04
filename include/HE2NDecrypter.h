#ifndef HE2NDECRYPTER_H
#define HE2NDECRYPTER_H

#include <NTL/ZZ.h>
#include <NTL/vec_ZZ_p.h>
#include <string>
#include "HE2Decipher.h"

class HE2NDecrypter : public HE2Decipher
{
private:
	/**
	 * Secret cipher parameter
	 */
    NTL::ZZ kappa;
public:
    void readSecretsFromJSON(std::string& json) override;
    NTL::ZZ decrypt(NTL::vec_ZZ_p& ciphertext) override;

    HE2NDecrypter();
    virtual ~HE2NDecrypter(){};
};

#endif
