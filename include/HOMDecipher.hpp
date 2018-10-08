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

#ifndef HOMDECIPHER_HPP
#define HOMDECIPHER_HPP

#include <NTL/ZZ.h>
#include "Decipher.hpp"

/**
 * This interface details the class members common to all HE\em x algorithms. All HE\em x decryption classes derive from this class.
 * @tparam C Ciphertext type
 * @tparam P Plaintext type
 */
template <typename C, typename P> class HOMDecipher : public Decipher<C,P>
{
protected:
	/**
	 * Secret cipher parameter
	 */
	NTL::ZZ p;

public:
	HOMDecipher(){};
	virtual ~HOMDecipher(){};
};

#endif
