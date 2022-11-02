#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <gmp.h>
#define BUFFERLEN 4096

uint32_t strLen(uint8_t* str)
{
    uint32_t i = 0;
    while(str[i] != 0)
    {
        i++;
    }
    return i;
}

void printStrHex(uint8_t* str, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        printf("%.2x", str[i]);
    }
    printf("\n");
}

uint8_t hexChar(uint8_t value)
{
    switch(value)
    {
        case '0': return 0x00;
        case '1': return 0x01;
        case '2': return 0x02;
        case '3': return 0x03;
        case '4': return 0x04;
        case '5': return 0x05;
        case '6': return 0x06;
        case '7': return 0x07;
        case '8': return 0x08;
        case '9': return 0x09;
        case 'a': return 0x0a;
        case 'b': return 0x0b;
        case 'c': return 0x0c;
        case 'd': return 0x0d;
        case 'e': return 0x0e;
        case 'f': return 0x0f;
    }
    return 0xff;
}

uint8_t* textToBin(uint8_t* raw, uint8_t* outBuffer)
{
    uint32_t outLen = strLen(raw)/2;
    //uint8_t* outBuffer = calloc(outLen, 1);
    for(uint32_t i = 0; i < outLen; i++)
    {
        outBuffer[i] = (hexChar(raw[2*i]) << 4) + hexChar(raw[2*i + 1]);
    }
    return outBuffer;
}

uint8_t* crypt(mpz_t key, uint8_t* input, uint32_t len)
{   
    mpz_t base;
    mpz_t modulus;

    //temp is for small operations, bigtemp is for the running massive sum
    mpz_t temp;
    mpz_t bigtemp;
    mpz_init_set_str(base, "2", 10);
    mpz_init_set_str(modulus, "e519335ded99dcdc65434a265d999baf", 16);
    mpz_init(temp);
    mpz_init(bigtemp);

    //sets original offset based on key
    mpz_powm(bigtemp, base, key, modulus);

    for(uint32_t i = 0; i < len; i++)
    {
        mpz_mod_ui(temp, bigtemp, 256);
        input[i] ^= mpz_get_ui(temp);

        //update sum
        mpz_mul(bigtemp, bigtemp, base);
        mpz_mod(bigtemp, bigtemp, modulus);
    }
    return input;
}

uint32_t main()
{
    printf("Key:");
    mpz_t key;
    uint8_t keyBuffer[BUFFERLEN] = {0};
    fgets(keyBuffer, BUFFERLEN, stdin);
    mpz_init_set_str(key, keyBuffer, 62);

    printf("Text:");
    uint8_t rawTextBuffer[BUFFERLEN] = {0};
    fgets(rawTextBuffer, BUFFERLEN, stdin);

    printf("Encrypt or decrypt?(e/d):");
    uint8_t choiceBuffer[2] = {0};
    fgets(choiceBuffer, 2, stdin);

    uint32_t inputLen = strLen(rawTextBuffer);

    if(choiceBuffer[0] == 'e')
    {
        //had to add this evilness so some devices actually print "00" in the output
        uint8_t* ciphertext = crypt(key, rawTextBuffer, inputLen);
        printStrHex(ciphertext, inputLen);
    }
    
    if(choiceBuffer[0] == 'd')
    {
        uint32_t originalLen = inputLen/2;
        uint8_t outBuffer[BUFFERLEN/2] = {0};
        uint8_t* rawBinary = textToBin(rawTextBuffer, outBuffer);
        uint8_t* originalText = crypt(key, rawBinary, originalLen);
        printf("%s", originalText);
    }
    return 0;
}
