#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>


int main()
{

    char key[32], c_key[32] = {'a','b'};
    char *r;
    r = crypt(key, c_key);
    strcpy(key, "abc");   

    printf("Key: %d", sizeof(key));

} 
