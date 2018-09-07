/*
 * GACDDecrypter.h
 *
 *  Created on: 7 Aug 2018
 *      Author: scsjd
 */

#ifndef GACDDECRYPTER_H
#define GACDDECRYPTER_H

#include <NTL/ZZ.h>
#include "Decipher.hpp"

class GACDDecrypter: public Decipher<NTL::ZZ,NTL::ZZ>{
private:
	NTL::ZZ k;
public:
	GACDDecrypter();
	virtual ~GACDDecrypter();
	NTL::ZZ decrypt(NTL::ZZ& ciphertext) override;
    void readSecretsFromJSON(std::string& secrets) override;
};

#endif /* GACDDECRYPTER_H */
