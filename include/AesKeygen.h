#ifndef AESKEYGEN_H
#define AESKEYGEN_H
#include<iostream>
#include<fstream>
#include "sbox.h"
using namespace std;
class AesKeygen
{
 
public:
	int rounds;
	fstream* keyfile= new fstream;
	streampos size;
	char* key;
	uint8_t** roundkeys;
    AesKeygen(char* filename);
	~AesKeygen();
 
    void check_key();
	uint8_t** getRoundKeys();
    void load_key();
    void check_key_size();
    void generate_roundkeys();
	void print_key();
	private:
	uint32_t g(uint32_t word,int i);
};
 
#endif