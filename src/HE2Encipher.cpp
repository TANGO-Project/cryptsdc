#include <sstream>
#include <json/json.h>
#include <NTL/RR.h>
#include <NTL/ZZ_p.h>
#include "HE2Encipher.h"
#include "Random.h"

NTL::ZZ HE2Encipher::ONE = NTL::ZZ(1);
NTL::vec_ZZ_p HE2Encipher::ONE_VECTOR;


HE2Encipher::HE2Encipher()
{
	pmod=nullptr;
	a=nullptr;
	gamma=nullptr;
	R=nullptr;
};

HE2Encipher::~HE2Encipher()
{
	delete pmod;
	delete a;
	delete gamma;
	delete R;
};

std::string HE2Encipher::writeParametersToJSON()
{
	Json::Value root;
	std::ostringstream modStr;
	modStr << modulus;
	root["modulus"] = modStr.str();
	Json::Value RArray(Json::arrayValue);
	for (int i=0; i < R->NumRows(); i++){
		Json::Value RRow(Json::arrayValue);
		for (int j=0; j < R->NumCols(); j++){
			std::ostringstream eltStr;
			eltStr << R->get(i,j);
			RRow[j]= eltStr.str();
		}
		RArray[i] = RRow;
	}
	root["R"] = RArray;
	Json::FastWriter writer;
	std::string json = writer.write(root);
	return json;
};

std::string HE2Encipher::encryptToString(NTL::ZZ& plaintext)
{
	Json::Value root(Json::arrayValue);
	NTL::vec_ZZ_p encrypted = encrypt(plaintext);
	std::ostringstream ss;
	ss << encrypted;
	return ss.str();
};

std::string HE2Encipher::encryptToString(int16_t plaintext)
{
	NTL::ZZ p = NTL::ZZ(plaintext);
	return encryptToString(p);
};

std::string HE2Encipher::encryptToString(int32_t plaintext)
{
	NTL::ZZ p = NTL::ZZ(plaintext);
	return encryptToString(p);
};

std::string HE2Encipher::encryptToString(int64_t plaintext)
{
	NTL::ZZ p = NTL::ZZ(plaintext);
	return encryptToString(p);
};

void HE2Encipher::generateParameters(int lambda, int eta){
	generateModulus(lambda,eta);

	/* Set local modulus to pq */
	NTL::ZZ_p::init(modulus);
	NTL::ZZ_p ptmp = NTL::to_ZZ_p(p);
	pmod = new NTL::ZZ_p(ptmp);

	/* Configure common HE2x vectors and matrices */
    /* Initialise ONE_VECTOR */
	HE2Encipher::ONE_VECTOR.SetLength(2);
	HE2Encipher::ONE_VECTOR[0] = NTL::to_ZZ_p(HE2Encipher::ONE);
	HE2Encipher::ONE_VECTOR[1] = NTL::to_ZZ_p(HE2Encipher::ONE);

	/* Set constants for calculations below */
    NTL::ZZ_p one(1);
    NTL::ZZ_p two(2);

    /* Generate a */
    Random rnd = Random();

	NTL::ZZ a1temp;
	do{
		a1temp = rnd.nextBigInteger(ONE, modulus);
	} while (a1temp % p == 0 || a1temp % q == 0);
	NTL::ZZ a2temp;
	do {
		a2temp = rnd.nextBigInteger(ONE, modulus);
	} while (a1temp == a2temp || a2temp % p == 0 || a2temp % q == 0 || SubMod(a1temp,a2temp,p)==0 || SubMod(a1temp,a2temp,q)==0);
	NTL::ZZ_p a1 = NTL::to_ZZ_p(a1temp);
	NTL::ZZ_p a2 = NTL::to_ZZ_p(a2temp);
	a = new NTL::vec_ZZ_p;
	a->SetLength(2);
	a->put(0,a1);
	a->put(1,a2);

	/* Generate gamma */
	NTL::ZZ_p adiff = a2-a1;
	NTL::ZZ_p adiffinv = NTL::inv(adiff);
    NTL::ZZ_p gamma1 = adiffinv*a2;
    NTL::ZZ_p gamma2 = adiffinv*(-a1);
    gamma = new NTL::vec_ZZ_p;
    gamma->SetLength(2);
    gamma->put(0,gamma1);
    gamma->put(1,gamma2);

    /* Generate R */
    NTL::ZZ_p r = NTL::to_ZZ_p(rnd.nextBigInteger(q));
    NTL::ZZ_p s = NTL::to_ZZ_p(rnd.nextBigInteger(modulus));
    NTL::ZZ_p beta = adiff*adiff*two;
    NTL::ZZ_p betainv = NTL::inv(beta);
    NTL::ZZ_p rp = r*NTL::to_ZZ_p(p);
    NTL::ZZ_p alpha1 = betainv*(s*a1+rp - a1*a1);
    NTL::ZZ_p alpha2 = betainv*(s*a2+rp - a2*a2);
    R = new NTL::mat_ZZ_p;
    R->SetDims(2, 3);
    NTL::ZZ_p R11 = one - two*alpha1;
    R->put(0,0,R11);
    NTL::ZZ_p R12 = alpha1;
    R->put(0,1,R12);
    NTL::ZZ_p R13 = alpha1;
    R->put(0,2,R13);
    NTL::ZZ_p R21 = -two*alpha2;
    R->put(1,0,R21);
    NTL::ZZ_p R22 = alpha2+one;
    R->put(1,1,R22);
    NTL::ZZ_p R23 = alpha2;
    R->put(1,2,R23);
}
