#ifndef HE2DECRYPTER_H
#define HE2DECRYPTER_H

#include <string>
#include <NTL/ZZ.h>
#include <NTL/vec_ZZ_p.h>
#include "HE2Decipher.h"

class HE2Decrypter : public HE2Decipher
{
public:
    void readSecretsFromJSON(std::string& json) override;
    NTL::ZZ decrypt(NTL::vec_ZZ_p& ciphertext) override;

    virtual ~HE2Decrypter();
    HE2Decrypter();
};

#endif
