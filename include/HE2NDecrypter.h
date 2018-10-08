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
