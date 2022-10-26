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
    mpz_t temp;
    mpz_init_set_str(base, "18096385125311361929", 10);
    mpz_init_set_str(modulus, "11956167491683668500912809771423810466891014777098993343204306140270942013318246342933114528955373506746550317457564085175949195464468770419500405042218191", 10);
    mpz_init(temp);
    for(uint32_t i = 0; i < len; i++)
    {
        mpz_add_ui(temp, key, i);
        mpz_powm(temp, base, temp, modulus);
        mpz_mod_ui(temp, temp, 256);
        input[i] ^= mpz_get_ui(temp);
        //printf("%d\n", mpz_get_ui(temp));
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
