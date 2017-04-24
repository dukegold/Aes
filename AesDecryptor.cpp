#include "AesDecryptor.h"

AesDecryptor::AesDecryptor(char* in,char* out,uint8_t** keyx){
	infile->open(in,ios::in|ios::binary|ios::ate);
	size=infile->tellg();
	key=keyx;
	infile->seekg(0,ios::beg);
	outfile->open(out,ios::out|ios::binary);
}
AesDecryptor::~AesDecryptor(){
	infile->close();
	outfile->close();
}
void AesDecryptor::decrypt(){
	if(size%16!=0){
		cout<<"Warning: padding zeros at the end"<<endl;
	}
	
	for(int i=0;i<size/16;i++){
		uint8_t* array;
		array = new uint8_t [16];
		infile->read(array,16);
		for(int j=1;j<11;j++){
			roundProcess(array,j);
		}
		for(int k=0;k<16;k++){
		array[k]^=key[0][k];
		}

		outfile->write(array,16);
	}
	
}
int AesDecryptor::hob(uint16_t num)
{
    if (!num)
        return 0;
    int ret = 1;
    while(num>>(ret+1)){
		ret++;
	}
    return ret;
}

uint8_t  AesDecryptor::polyreduce(uint16_t res){
	uint16_t poly;
	poly=283;
	while(hob(res)>=8)
		res^=poly<<(hob(res)-8);
	return res;
}
void AesDecryptor::roundProcess(uint8_t* array,int i){
	for(int k=0;k<16;k++){
		array[k]^=key[11-i][k];
	}
	uint8_t* interim;
	interim = new uint8_t [16];

	if(i!=1){
		for(int l=0;l<4;l++){
			interim[(0+(l*4))]= polyreduce((array[(0+(4*l))]<<3) ^(array[(0+(4*l))]<<2)^(array[(0+(4*l))]<<1))^
								polyreduce((array[(1+(4*l))]<<3) ^(array[(1+(4*l))]<<1)^(array[(1+(4*l))]))^
								polyreduce((array[(2+(4*l))]<<3) ^(array[(2+(4*l))]<<2)^(array[(2+(4*l))]))^
								polyreduce((array[(3+(4*l))]<<3) ^(array[(3+(4*l))]));
			interim[(1+(l*4))]= polyreduce((array[(1+(4*l))]<<3) ^(array[(1+(4*l))]<<2)^(array[(1+(4*l))]<<1))^
								polyreduce((array[(2+(4*l))]<<3) ^(array[(2+(4*l))]<<1)^(array[(2+(4*l))]))^
								polyreduce((array[(3+(4*l))]<<3) ^(array[(3+(4*l))]<<2)^(array[(3+(4*l))]))^
								polyreduce((array[(0+(4*l))]<<3) ^(array[(0+(4*l))]));					
			interim[(2+(l*4))]= polyreduce((array[(2+(4*l))]<<3) ^(array[(2+(4*l))]<<2)^(array[(2+(4*l))]<<1))^
								polyreduce((array[(3+(4*l))]<<3) ^(array[(3+(4*l))]<<1)^(array[(3+(4*l))]))^
								polyreduce((array[(0+(4*l))]<<3) ^(array[(0+(4*l))]<<2)^(array[(0+(4*l))]))^
								polyreduce((array[(1+(4*l))]<<3) ^(array[(1+(4*l))]));
			interim[(3+(l*4))]= polyreduce((array[(3+(4*l))]<<3) ^(array[(3+(4*l))]<<2)^(array[(3+(4*l))]<<1))^
								polyreduce((array[(0+(4*l))]<<3) ^(array[(0+(4*l))]<<1)^(array[(0+(4*l))]))^
								polyreduce((array[(1+(4*l))]<<3) ^(array[(1+(4*l))]<<2)^(array[(1+(4*l))]))^
								polyreduce((array[(2+(4*l))]<<3) ^(array[(2+(4*l))]));

		}
	}
	else{
		for(int p=0;p<16;p++){
			interim[p]=array[p];
		}
	}
	array[0] = sbox_inv[interim[0]];
	array[1] = sbox_inv[interim[13]];
	array[2] = sbox_inv[interim[10]];
	array[3] = sbox_inv[interim[7]];
	array[4] = sbox_inv[interim[4]];
	array[5] = sbox_inv[interim[1]];
	array[6] = sbox_inv[interim[14]];
	array[7] = sbox_inv[interim[11]];
	array[8] = sbox_inv[interim[8]];
	array[9] = sbox_inv[interim[5]];
	array[10] = sbox_inv[interim[2]];
	array[11] = sbox_inv[interim[15]];
	array[12] = sbox_inv[interim[12]];
	array[13] = sbox_inv[interim[9]];
	array[14] = sbox_inv[interim[6]];
	array[15] = sbox_inv[interim[3]];
	delete interim;

}