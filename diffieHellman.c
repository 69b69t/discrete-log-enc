#include <stdio.h>
#include <gmp.h>

int main()
{
    mpz_t base;
    mpz_t modulo;
    mpz_init_set_ui(base, 2);
    mpz_init_set_str(modulo, "e13b01bbe6e08cdf", 16);
    mpz_t pkey;
    mpz_init(pkey);
    FILE* random = fopen("/dev/random", "r");
    mpz_import(pkey, 1024, 1, 1, 0, 0, random);
    fclose(random);
    mpz_t ckey;
    mpz_init(ckey);
    mpz_t sharedSecret;
    mpz_init(sharedSecret);
    char cKeyBuffer[4096] = {0};
    printf("Your public key(send this):\n");
    mpz_powm(ckey, base, pkey, modulo);
    mpz_out_str(stdout, 62, ckey);
    printf("\n\nOther person's public key:");
    fgets(cKeyBuffer, 4096, stdin);
    mpz_set_str(ckey, cKeyBuffer, 62);
    mpz_powm(sharedSecret, ckey, pkey, modulo);
    printf("\nShared secret\n");
    mpz_out_str(stdout, 62, sharedSecret);
    printf("\n\n");
    mpz_clear(base);
    mpz_clear(modulo);
    mpz_clear(pkey);
    mpz_clear(ckey);
    mpz_clear(sharedSecret);
    return 0;
}
