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

#include "PolyACDEncrypter.h"

#include <NTL/ZZ.h>
#include <NTL/ZZX.h>
#include <json/json.h>
#include <cryptopp/osrng.h>
#include <cryptopp/rng.h>
#include <chrono>
#include <string>
#include <sstream>

PolyACDEncrypter::PolyACDEncrypter(int lambda, int mu, int d) {
	this->mu = mu;
	RandomLen(k1,lambda);
	k2.SetLength(d+1);
	for(int i =0; i < d; i++){
		NTL::ZZ tmp;
		RandomBits(tmp,mu);
		SetCoeff(k2,i,tmp);
	}
	SetCoeff(k2,d,1);
}

PolyACDEncrypter::PolyACDEncrypter(int mu, std::string& secrets) {
	this->mu = mu;
	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(secrets,root);
	if (parsingSuccessful){
		std::istringstream k1buf(root["k1"].asString());
		k1buf >> k1;
		std::istringstream k2buf(root["k2"].asString());
		k2buf >> k2;
	}
}

PolyACDEncrypter::~PolyACDEncrypter() {
}

std::string PolyACDEncrypter::writeSecretsToJSON(){
	Json::Value root;
	std::ostringstream k1buf;
	k1buf << k1;
	root["k1"]= k1buf.str();
	std::ostringstream k2buf;
	k2buf << k2;
	root["k2"]= k2buf.str();
	Json::FastWriter writer;
	return writer.write(root);
}

NTL::ZZX PolyACDEncrypter::encrypt(NTL::ZZX& plaintext){
	NTL::ZZX p = k2*plaintext;
	long degree = deg(p);
	NTL::ZZ m_n = LeadCoeff(plaintext);
	NTL::ZZX p2;
	p2.SetLength(degree-1);
	for (long i = 0; i < degree-1; i++){
		SetCoeff(p2,i,coeff(p,i));
	}
	SetCoeff(p2,degree-1,p[degree-1]+k1*m_n);
	NTL::ZZX r;
	long d = deg(k2);
	r.SetLength(d-1);
	for(long i =0; i < d; i++){
		NTL::ZZ tmp;
		RandomBits(tmp,mu);
		SetCoeff(r,i,tmp);
	}
	return p2+r;
}

NTL::ZZX PolyACDEncrypter::encrypt(NTL::vec_ZZ& plaintext){
	NTL::ZZX ptext = to_ZZX(plaintext);
	return encrypt(ptext);
}
