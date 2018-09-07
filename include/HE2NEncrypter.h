#ifndef HE2NENCRYPTER_H
#define HE2NENCRYPTER_H

#include <NTL/ZZ.h>
#include <NTL/vec_ZZ_p.h>
#include <string>
#include "HE2Encipher.h"

class HE2NEncrypter : public HE2Encipher
{
private:
    NTL::ZZ kappa;
    NTL::ZZ_p* kappamod; //This is a pointer to avoid kappamod being initialised mod zero
public:
    NTL::vec_ZZ_p encrypt(NTL::ZZ& plaintext) override;
    std::string writeSecretsToJSON() override;

    HE2NEncrypter(int lambda, int eta, int nu);
    HE2NEncrypter(int n, int d, int rho, int rhoprime);
    virtual ~HE2NEncrypter();
};

#endif
