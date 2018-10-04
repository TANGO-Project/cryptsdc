/*
 * Decipher.hpp
 *
 *  Created on: 25 Jun 2018
 *      Author: James Dyer
 *
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
