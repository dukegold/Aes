#include "AesEncryptor.h"

AesEncryptor::AesEncryptor(char* in,char* out,uint8_t** keyx){
	infile->open(in,ios::in|ios::binary|ios::ate);
	size=infile->tellg();
	key=keyx;
	infile->seekg(0,ios::beg);
	outfile->open(out,ios::out|ios::binary);
}
AesEncryptor::~AesEncryptor(){
	infile->close();
	outfile->close();
}
void AesEncryptor::encrypt(){
	if(size%16!=0){
		cout<<"Warning: padding zeros at the end"<<endl;
	}
	
	for(int i=0;i<size/16;i++){
		uint8_t* array;
		array = new uint8_t [16];
		infile->read(array,16);
		for(int k=0;k<16;k++){
		array[k]^=key[0][k];
		}
		for(int j=1;j<11;j++){
			roundProcess(array,j);
		}
		// for(auto x=0;x<16;x++){
			// cout<<std::hex<<unsigned(array[x]);
		// }
		// cout<<endl;
		outfile->write(array,16);
	}
	
}
int AesEncryptor::hob(uint16_t num)
{
    if (!num)
        return 0;
    int ret = 1;
    while(num>>(ret+1)){
		ret++;
	}
    return ret;
}

uint8_t  AesEncryptor::polyreduce(uint16_t res){
	uint16_t poly;
	poly=283;
	while(hob(res)>=8)
		res^=poly<<(hob(res)-8);
	return res;
}
void AesEncryptor::roundProcess(uint8_t* array,int i){
	uint8_t* interim;
	interim = new uint8_t [16];
	interim[0] = sbox[array[0]];
	interim[1] = sbox[array[5]];
	interim[2] = sbox[array[10]];
	interim[3] = sbox[array[15]];
	interim[4] = sbox[array[4]];
	interim[5] = sbox[array[9]];
	interim[6] = sbox[array[14]];
	interim[7] = sbox[array[3]];
	interim[8] = sbox[array[8]];
	interim[9] = sbox[array[13]];
	interim[10] = sbox[array[2]];
	interim[11] = sbox[array[7]];
	interim[12] = sbox[array[12]];
	interim[13] = sbox[array[1]];
	interim[14] = sbox[array[6]];
	interim[15] = sbox[array[11]];
	if(i!=10){
		for(int l=0;l<4;l++){
			array[(0+(l*4))]= polyreduce((interim[(0+(4*l))]<<1))^polyreduce(((interim[(1+(4*l))]<<1)^interim[(1+(4*l))]))^(interim[(2+(4*l))])^(interim[(3+(4*l))]);
			array[(1+l*4)]= polyreduce((interim[(1+4*l)]<<1))^polyreduce(((interim[(2+4*l)]<<1)^interim[(2+4*l)]))^(interim[(0+4*l)])^(interim[(3+4*l)]);
			array[(2+l*4)]= polyreduce((interim[(2+4*l)]<<1))^polyreduce((interim[(3+4*l)]<<1)^interim[(3+4*l)])^(interim[(0+4*l)])^(interim[(1+4*l)]);
			array[(3+l*4)]= polyreduce((interim[(3+4*l)]<<1))^polyreduce(((interim[(0+4*l)]<<1)^interim[(0+4*l)]))^(interim[(1+4*l)])^(interim[(2+4*l)]);
		}
	}
	else{
		for(int p=0;p<16;p++){
			array[p]=interim[p];
		}
	}
	delete interim;
	for(int k=0;k<16;k++){
		array[k]^=key[i][k];
	}
}