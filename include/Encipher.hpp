/*
 * Encipher.hpp
 *
 *  Created on: 25 Jun 2018
 *      Author: James Dyer
 *
 */

#ifndef ENCIPHER_HPP
#define ENCIPHER_HPP

#include <string>

/**
 *	Interface implemented by all enciphering classes in this library
 *	@tparam C Ciphertext type
 *	@tparam P Plaintext type
 */
template <typename C, typename P> class Encipher
{
public:
	Encipher(){};
	virtual ~Encipher(){};
	/**
	 * Writes cipher secrets out to a JSON string
	 * @return JSON string
	 */
	virtual std::string writeSecretsToJSON()=0;
	/**
	 * Encrypt a plaintext
	 * @param plaintext A plaintext value
	 * @return A ciphertext value
	 */
	virtual C encrypt(P& plaintext)=0;
};

#endif
