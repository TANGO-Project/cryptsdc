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

    HE2Encrypter(int lambda, int eta);
    HE2Encrypter(int n, int d, int rho);
    virtual ~HE2Encrypter();
};

#endif
