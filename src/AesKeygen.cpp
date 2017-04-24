#include "AesKeygen.h"

using namespace std;

class InvalidKey : public runtime_error
{
public:
   InvalidKey(): runtime_error( "Invalid key size" ) {}
};


AesKeygen::AesKeygen(char* filename){
	keyfile->open(filename,ios::in|ios::binary|ios::ate);
	size=keyfile->tellg();
}
AesKeygen::~AesKeygen(){
	keyfile->close();
}
void AesKeygen::check_key(){
	try{
		check_key_size();
		cout<<"Key file ok\n";
	}

	 catch ( InvalidKey &invalidKey )
	{
		cout << "Exception occurred: " << invalidKey.what() << endl;
	}
}

void AesKeygen::load_key(){
key = new unsigned char [keyfile->tellg()];
keyfile->seekg (0, ios::beg);
keyfile->read (key, size);
keyfile->close();
// for(auto i=0;i<size;i++){
	// cout<<std::hex<<unsigned(key[i]);
// }
}

void AesKeygen::check_key_size(){
if(keyfile->tellg()!= 16 && keyfile->tellg()!= 24 && keyfile->tellg()!=32)
	throw InvalidKey();

}

void AesKeygen::generate_roundkeys(){
	rounds= (size==16) ?10:((size==24)?12:14);
	roundkeys = new uint8_t*[rounds+1];
	for(int i = 0; i < rounds+1; ++i)
		roundkeys[i] = new uint8_t[16];
	for(int i=0;i<rounds+1;i++){
		if(i==0){
			for(int k=0;k<16;k++){
				roundkeys[i][k]=key[k];
			}
		}
	
		else{
			uint32_t gval,wl;
			wl=(roundkeys[i-1][12]<<24)|(roundkeys[i-1][13]<<16)|(roundkeys[i-1][14]<<8)|(roundkeys[i-1][15]);
			gval=g(wl,i);
			wl=(roundkeys[i-1][0]<<24)|(roundkeys[i-1][1]<<16)|(roundkeys[i-1][2]<<8)|(roundkeys[i-1][3]);
			gval^=wl;
			for(int k=0;k<4;k++){
				roundkeys[i][k]= gval>>((3-k)*8)&0xff;
			}
			for(int k=4;k<16;k++){
				
				roundkeys[i][k]=roundkeys[i][k-4]^roundkeys[i-1][k];
			}
				
		}
	}
	
	
}


void AesKeygen::print_key(){
	for(int i=0;i<rounds+1;i++){
		for(int j=0;j<16;j++){
			cout<<std::hex<<unsigned(roundkeys[i][j])<<" ";
		}
		cout<<endl;
	}
}

uint32_t AesKeygen::g(uint32_t word,int i){

	word =  (sbox[(word>>16)&0xff] ^ rcon[i])<<24 | (sbox[(word>>8)&0xff])<<16 | (sbox[(word)&0xff])<<8 |(sbox[(word>>24)&0xff]);
	return word;
}
uint8_t** AesKeygen::getRoundKeys(){
	return this->roundkeys;
}