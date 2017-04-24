#include<iostream>
#include<cmath>
using namespace std;

int hob (uint16_t num)
{
    if (!num)
        return 0;

    int ret = 1;

    while (num>>(ret+1)){
		 ret++;
	}

    return ret;
}

int main(){
	uint16_t res,poly;
	poly=283;
	for(auto i=0;i<1000;i++){
		res=rand()%65536;
		cout<<res<<"\t";
		while(hob(res)>=8){
		res^=poly<<(hob(res)-8);
	}
		cout<<res<<endl;
		
	}
	
}
