#include"../librairie/init.h"
#include"hash_algo.h"

int my_pow(int a,int b)
{
    if(b==0)return 1;
    return a * my_pow(a,b-1);
}

int get_hash_index_airport(char iata_code[SIZE_acronym])
{
    return 
    iata_code[2]-A_ascii + 
    (iata_code[1]-A_ascii)*(MAX_LETTER) + 
    (iata_code[0]-A_ascii)*my_pow(MAX_LETTER,2);
}
