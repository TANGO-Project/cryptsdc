/*
 * Copyright 2018 James Dyer
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 *
 * This is being developed for the TANGO Project: http://tango-project.eu
 */

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
