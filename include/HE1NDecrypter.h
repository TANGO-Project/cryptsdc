#ifndef HE1NDECRYPTER_H
#define HE1NDECRYPTER_H

#include <string>
#include <NTL/ZZ.h>
#include <NTL/vec_ZZ.h>
#include "HOMDecipher.hpp"

class HE1NDecrypter : public HOMDecipher<NTL::ZZ_p,NTL::ZZ>
{
private:
	/**
	 * A secret cipher parameter
	 */
    NTL::ZZ kappa;

public:
    /**
     * Set the secret parameters \c p and \c kappa from the given vector.
     * @param key A vector
     */
    void setKey(NTL::vec_ZZ& key);
    void readSecretsFromJSON(std::string& json) override;
    NTL::ZZ decrypt(NTL::ZZ_p& ciphertext) override;

    HE1NDecrypter(){};
    virtual ~HE1NDecrypter(){};
};

#endif
