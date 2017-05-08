#include "sboxgrig.h"

SBoxGrig::SBoxGrig()
{

}

void SBoxGrig::generate(byte *&sbox)
{
    if(sbox){
        delete[] (sbox);
    }

    sbox = new byte[256];
    for(int i = 0; i < 256; i++){
        (sbox)[i] = sboxGrig[i];
    }
}
