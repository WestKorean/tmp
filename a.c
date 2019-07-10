#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>


int main()
{

    char key[30], c_key[30] = {'a','b'};
    char *r;
    r = crypt(key, c_key);
    printf("Key: %d", sizeof(key));
} 
