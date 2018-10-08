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
