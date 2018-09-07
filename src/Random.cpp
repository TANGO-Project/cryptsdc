#include "Random.h"

#include <cryptopp/osrng.h>
#include <cryptopp/rng.h>

NTL::ZZ Random::nextBigInteger(NTL::ZZ& range)
{
	int numBytes = NTL::NumBytes(range);
	int intSize = sizeof(ISAAC_INT);
	int numInts;
	if(numBytes % intSize == 0) numInts = numBytes/intSize;
	else numInts = numBytes/intSize + 1;
	NTL::ZZ result;
	do
	{
		ISAAC_INT bb[numInts];
		for (int i =0; i < numInts; i++){
			bb[i] = rng->rand();
		}
		result = NTL::ZZFromBytes(reinterpret_cast<uint8_t*>(bb), numBytes);
	}
	while(result >= range);
	return result;
}

NTL::ZZ Random::nextBigInteger(NTL::ZZ& min, NTL::ZZ& max)
{
    NTL::ZZ range = max - min;
    NTL::ZZ random = this->nextBigInteger(range);
    return random + min;
}

Random::Random(){
	CryptoPP::SecByteBlock seed(512);
    CryptoPP::OS_GenerateRandomBlock(false, seed.data(), seed.size());
    rng = new QTIsaac<>();
    rng->srand(0,0,0,(ISAAC_INT*)seed.data());
}

Random::Random(CryptoPP::SecByteBlock& seed){
    rng = new QTIsaac<>();
    rng->srand(0,0,0,(ISAAC_INT*)seed.data());
}

Random::~Random(){
	delete rng;
}
