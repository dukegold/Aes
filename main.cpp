#include<iostream>
#include<fstream>
#include<vector>
#include "AesKeygen.h"
#include "AesDecryptor.h"
using namespace std;

int main(int argc,char* argv[]){
	AesKeygen my = AesKeygen(argv[1]);
	my.check_key();
	my.load_key();
	my.generate_roundkeys();
	//my.print_key();
	
	// AesEncryptor x = AesEncryptor(argv[2],argv[3],my.getRoundKeys());
	// x.encrypt();
	AesDecryptor x =AesDecryptor(argv[2],argv[3],my.getRoundKeys());
	x.decrypt();
	cout<<"Encryption Successful"<<endl;
	return 0;
}