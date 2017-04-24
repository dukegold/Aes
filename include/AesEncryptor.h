#ifndef AESENCRYPTOR_H
#define AESENCRYPTOR_H
#include<fstream>
#include<iostream>
#include"sbox.h"
using namespace std;
class AesEncryptor{
	public:
		AesEncryptor(char* in,char* out,uint8_t** keyx);
		~AesEncryptor();
		void encrypt();
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