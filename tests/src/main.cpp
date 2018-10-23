/*
 * main.cpp
 *
 *  Created on: 3 Aug 2018
 *      Author: scsjd
 */

#include <chrono>
#include <iostream>
#include <random>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/vec_ZZ.h>
#include <NTL/vec_ZZ_p.h>
#include "DETEncrypter.h"
#include "DETDecrypter.h"
#include "SSEEncrypter.h"
#include "SSEDecrypter.h"
#include "GACDEncrypter.h"
#include "GACDDecrypter.h"
#include "PolyACDEncrypter.h"
#include "PolyACDDecrypter.h"
#include "HE1Encrypter.h"
#include "HE1Decrypter.h"
#include "HE1NEncrypter.h"
#include "HE1NDecrypter.h"
#include "HE2Encrypter.h"
#include "HE2Decrypter.h"
#include "HE2NEncrypter.h"
#include "HE2NDecrypter.h"
#include "HE2Ciphertext.h"
#include "PolyCiphertext.h"
#include "SSECiphertext.h"

NTL::ZZX createRandomPoly(std::mt19937& rng, int mu, int n) {
	NTL::ZZX p;
	//Generate random int for degree of poly
	unsigned int rnd = (rng() % n) + 1;
	//Generate random coefficients for poly
	p.SetLength(rnd+1);
	for (unsigned int i = 0; i < rnd + 1; i++) {
		NTL::ZZ tmp;
		RandomBits(tmp, mu);
		p[i] = tmp;
	}
	return p;
}

int main(){
	std::cout << "======= SSE Tests =======" << std::endl;

	std::string test = "this is a test";

	std::cout << "DET consistency test: ";
	DETEncrypter DETenc;
	std::string DETsecrets = DETenc.writeSecretsToJSON();
	std::string DETencrypted = DETenc.encryptToHex(test);

	DETDecrypter DETdec;
	DETdec.readSecretsFromJSON(DETsecrets);
	std::string DETdecrypted = DETdec.decryptFromHex(DETencrypted);
	if(test==DETdecrypted) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "DET equality test: ";
	std::string encrypted1 = DETenc.encryptToHex(test);
	std::string encrypted2 = DETenc.encryptToHex(test);
	if(encrypted1==encrypted2) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "SSE consistency test: ";
	SSEEncrypter SSEenc;
	std::string SSEsecrets = SSEenc.writeSecretsToJSON();
	std::string SSEencrypted = SSEenc.encrypt(test);

	SSEDecrypter SSEdec;
	SSEdec.readSecretsFromJSON(SSEsecrets);
	std::string SSEdecrypted = SSEdec.decrypt(SSEencrypted);
	if(test==SSEdecrypted) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "SSE match test 1: ";
	std::string searchKey = SSEenc.createHexEncodedSearchKey(test);
	SSECiphertext ssec(SSEencrypted);
	if(ssec.match(searchKey)) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "SSE match test 2: ";
	std::string test2 = "The quick brown fox jumped over the lazy dog";
	std::string SSEencrypted2 = SSEenc.encrypt(test2);
	std::string searchKey2 = SSEenc.createHexEncodedSearchKey(test2);
	SSECiphertext ssec2(SSEencrypted2);
	if(ssec2.match(searchKey2)) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "======= OPE Tests =======" << std::endl;
	//Data for GACD test
	int bits = 32;
	NTL::ZZ ope_m1 = NTL::RandomBits_ZZ(bits);
	NTL::ZZ ope_m2 = NTL::RandomBits_ZZ(bits);

	std::cout << "GACD consistency test: ";
	GACDEncrypter GACDenc(GACDEncrypter::getMinimumKeyLength(bits));
	std::string GACDsecrets = GACDenc.writeSecretsToJSON();
	NTL::ZZ GACDencrypted1 = GACDenc.encrypt(ope_m1);

	GACDDecrypter GACDdec;
	GACDdec.readSecretsFromJSON(GACDsecrets);
	NTL::ZZ GACDdecrypted = GACDdec.decrypt(GACDencrypted1);
	if(ope_m1==GACDdecrypted) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "GACD order-preserving test: ";
	NTL::ZZ GACDencrypted2 = GACDenc.encrypt(ope_m2);
	if(ope_m1 < ope_m2){
		if(GACDencrypted1<GACDencrypted2) std::cout << "PASSED" << std::endl;
		else std::cout << "FAILED" << std::endl;
	}
	else{
		if (ope_m1>ope_m2){
			if(GACDencrypted1>GACDencrypted2) std::cout << "PASSED" << std::endl;
			else std::cout << "FAILED" << std::endl;
		}
		else{
			//random order
			std::cout << "PASSED" << std::endl;
		}
	}

	//Data for PolyACD tests
	int lambda = 80;
	int mu = 32;
	int cdegree = 10;
	int pdegree = 5;
	std::mt19937 rng;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	rng.seed(seed);
	NTL::ZZX ope_p1 = createRandomPoly(rng,mu,pdegree);
	PolyCiphertext polyp1(ope_p1);
	NTL::ZZX ope_p2 = createRandomPoly(rng,mu,pdegree);
	PolyCiphertext polyp2(ope_p2);

	std::cout << "PolyACD consistency test: ";
	PolyACDEncrypter PolyACDenc(lambda,mu,cdegree);
	std::string PolyACDsecrets = PolyACDenc.writeSecretsToJSON();
	NTL::ZZX PolyACDencrypted1 = PolyACDenc.encrypt(ope_p1);

	PolyACDDecrypter PolyACDdec;
	PolyACDdec.readSecretsFromJSON(PolyACDsecrets);
	NTL::ZZX PolyACDdecrypted = PolyACDdec.decrypt(PolyACDencrypted1);
	if(ope_p1==PolyACDdecrypted) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "PolyACD order-preserving test: ";
	NTL::ZZX PolyACDencrypted2 = PolyACDenc.encrypt(ope_p2);
	PolyCiphertext polyc1(PolyACDencrypted1);
	PolyCiphertext polyc2(PolyACDencrypted2);
	if(polyp1 < polyp2){
		if(polyc1<polyc2) std::cout << "PASSED" << std::endl;
		else std::cout << "FAILED" << std::endl;
	}
	else{
		if (polyp1>polyp2){
			if(polyc1>polyc2) std::cout << "PASSED" << std::endl;
			else std::cout << "FAILED" << std::endl;
		}
		else{
			//random order
			std::cout << "PASSED" << std::endl;
		}
	}

	std::cout << "======= Integer HE Tests =======" << std::endl;
	//Data for HEx tests
	int n = 1000;
	int d = 2;
	int rho1=8;
	int rho2=32;
	int rhoprime=32;

	NTL::ZZ he_rho1_m1 = NTL::RandomBits_ZZ(rho1);
	NTL::ZZ he_rho1_m2 = NTL::RandomBits_ZZ(rho1);
	NTL::ZZ he_rho2_m1 = NTL::RandomBits_ZZ(rho2);
	NTL::ZZ he_rho2_m2 = NTL::RandomBits_ZZ(rho2);
	NTL::ZZ rho1_sum = he_rho1_m1+he_rho1_m2;
	NTL::ZZ rho1_product = he_rho1_m1*he_rho1_m2;
	NTL::ZZ rho2_sum = he_rho2_m1+he_rho2_m2;
	NTL::ZZ rho2_product = he_rho2_m1*he_rho2_m2;

	std::cout << "HE1 consistency test: ";
	HE1Encrypter he1enc(n,d,rho2);
	he1enc.init();
	//NTL::ZZ he1key = he1enc.getKey();
	std::string he1secrets = he1enc.writeSecretsToJSON();
	NTL::ZZ_p he1_c1 = he1enc.encrypt(he_rho2_m1);

	HE1Decrypter he1dec;
	//he1dec.setKey(he1key);
	he1dec.readSecretsFromJSON(he1secrets);
	he1dec.init();
	NTL::ZZ he1_m1 = he1dec.decrypt(he1_c1);
	if(he1_m1==he_rho2_m1) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "HE1 homomorphic tests:" << std::endl;
	NTL::ZZ_p he1_c2 = he1enc.encrypt(he_rho2_m2);
	NTL::ZZ_p he1_sum = he1_c1+he1_c2;
	NTL::ZZ_p he1_product = he1_c1*he1_c2;
	NTL::ZZ he1_sum_dec = he1dec.decrypt(he1_sum);
	NTL::ZZ he1_product_dec = he1dec.decrypt(he1_product);
	std::cout << "\t Sum: ";
	if(he1_sum_dec==rho2_sum) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;
	std::cout << "\t Product: ";
	if(he1_product_dec==rho2_product) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "HE1N consistency test: ";
	HE1NEncrypter he1nenc(n,d,rho1,rhoprime);
	he1nenc.init();
	//NTL::vec_ZZ he1nkey = he1nenc.getKey();
	std::string he1nsecrets = he1nenc.writeSecretsToJSON();
	NTL::ZZ_p he1n_c1 = he1nenc.encrypt(he_rho1_m1);

	HE1NDecrypter he1ndec;
	//he1ndec.setKey(he1nkey);
	he1ndec.readSecretsFromJSON(he1nsecrets);
	NTL::ZZ he1n_m1 = he1ndec.decrypt(he1n_c1);
	if(he1n_m1==he_rho1_m1) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "HE1N homomorphic tests:" << std::endl;
	NTL::ZZ_p he1n_c2 = he1nenc.encrypt(he_rho1_m2);
	NTL::ZZ_p he1n_sum = he1n_c1+he1n_c2;
	NTL::ZZ_p he1n_product = he1n_c1*he1n_c2;
	NTL::ZZ he1n_sum_dec = he1ndec.decrypt(he1n_sum);
	NTL::ZZ he1n_product_dec = he1ndec.decrypt(he1n_product);
	std::cout << "\t Sum: ";
	if(he1n_sum_dec==rho1_sum) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;
	std::cout << "\t Product: ";
	if(he1n_product_dec==rho1_product) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "HE2 consistency test: ";
	HE2Encrypter he2enc(n,d,rho2);
	he2enc.init();
	std::string he2secrets = he2enc.writeSecretsToJSON();
	std::string he2params = he2enc.writeParametersToJSON();
	NTL::vec_ZZ_p he2_c1 = he2enc.encrypt(he_rho2_m1);

	HE2Decrypter he2dec;
	he2dec.readSecretsFromJSON(he2secrets);
	NTL::ZZ he2_m1 = he2dec.decrypt(he2_c1);
	if(he2_m1==he_rho2_m1) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "HE2 homomorphic tests:" << std::endl;
	NTL::vec_ZZ_p he2_c2 = he2enc.encrypt(he_rho2_m2);
	HE2Ciphertext::setParameters(he2params);
	HE2Ciphertext he2c1(he2_c1);
	HE2Ciphertext he2c2(he2_c2);
	NTL::vec_ZZ_p he2_sum = (he2c1+he2c2).get_ciphertext();
	NTL::vec_ZZ_p he2_product = (he2c1*he2c2).get_ciphertext();
	NTL::ZZ he2_sum_dec = he2dec.decrypt(he2_sum);
	NTL::ZZ he2_product_dec = he2dec.decrypt(he2_product);
	std::cout << "\t Sum: ";
	if(he2_sum_dec==rho2_sum) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;
	std::cout << "\t Product: ";
	if(he2_product_dec==rho2_product) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "HE2N consistency test: ";
	HE2NEncrypter he2nenc(n,d,rho1,rhoprime);
	he2nenc.init();
	std::string he2nsecrets = he2nenc.writeSecretsToJSON();
	std::string he2nparams = he2nenc.writeParametersToJSON();
	NTL::vec_ZZ_p he2n_c1 = he2nenc.encrypt(he_rho1_m1);

	HE2NDecrypter he2ndec;
	he2ndec.readSecretsFromJSON(he2nsecrets);
	NTL::ZZ he2n_m1 = he2ndec.decrypt(he2n_c1);
	if(he2n_m1==he_rho1_m1) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;

	std::cout << "HE2N homomorphic tests:" << std::endl;
	NTL::vec_ZZ_p he2n_c2 = he2nenc.encrypt(he_rho1_m2);
	//Fails in setParameters when initialising R
	HE2Ciphertext::setParameters(he2nparams);
	HE2Ciphertext he2nc1(he2n_c1);
	HE2Ciphertext he2nc2(he2n_c2);
	HE2Ciphertext he2ncsum = he2nc1+he2nc2;
	HE2Ciphertext he2ncproduct = he2nc1*he2nc2;
	NTL::vec_ZZ_p he2n_sum = he2ncsum.get_ciphertext();
	NTL::vec_ZZ_p he2n_product = (he2nc1*he2nc2).get_ciphertext();
	NTL::ZZ he2n_sum_dec = he2ndec.decrypt(he2n_sum);
	NTL::ZZ he2n_product_dec = he2ndec.decrypt(he2n_product);
	std::cout << "\t Sum: ";
	if(he2n_sum_dec==rho1_sum) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;
	std::cout << "\t Product: ";
	if(he2n_product_dec==rho1_product) std::cout << "PASSED" << std::endl;
	else std::cout << "FAILED" << std::endl;
}

