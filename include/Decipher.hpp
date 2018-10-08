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

#ifndef DECIPHER_HPP
#define DECIPHER_HPP

#include <string>

/**
 *	Interface implemented by all deciphering classes in this library
 *	@tparam C Ciphertext type
 *	@tparam P Plaintext type
 */
template <typename C, typename P> class Decipher
{
public:
	Decipher(){};
	virtual ~Decipher(){};
	/**
	 * Reads the cipher secrets in from a JSON string
	 * @param string JSON string
	 */
	virtual void readSecretsFromJSON(std::string& string)=0;
	/**
	 * Decrypts a ciphertext
	 * @param ciphertext Ciphertext value
	 * @return Plaintext value
	 */
	virtual P decrypt(C& ciphertext)=0;
};

#endif
