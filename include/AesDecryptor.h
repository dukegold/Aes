#ifndef AESEDECRYPTOR_H
#define AESDECRYPTOR_H
#include<fstream>
#include<iostream>
#include"sbox.h"
using namespace std;
class AesDecryptor{
	public:
		AesDecryptor(char* in,char* out,uint8_t** keyx);
		~AesDecryptor();
		void decrypt();
		uint8_t** key;
	
	
	private:
		fstream* infile= new fstream;
		fstream* outfile= new fstream;
		streampos size;
		int hob(uint16_t num);
		uint8_t polyreduce(uint16_t res);
		void roundProcess(uint8_t* array,int i);
};
#endif