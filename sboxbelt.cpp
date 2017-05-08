#include "sboxbelt.h"

SBoxBelT::SBoxBelT()
{

}

void SBoxBelT::generate(byte ** sbox)
{
    if(sbox && (* sbox)){
        delete[] (* sbox);
    }

    * sbox = new byte[256];
    for(int i = 0; i < 256; i++){
        (* sbox)[i] = sboxBelT[i];
    }
}
