#include <stdio.h>
#include <gmp.h>

int main()
{
    mpz_t base;
    mpz_t modulo;
    mpz_init_set_ui(base, 2);
    mpz_init_set_str(modulo, "ea921a8a0baf3436bb5dbca9f1c525e8776affe0cc120ae5cf3c29cca1ee2bb0e69296c071c7ac0fda83260e2c49769b495d5a50bcda5e7d1f105820378003b97825395371d1f2c50fa4361ee5b7528b874a5c167c075ebd3ed44c45895ecfaa41cab022aaf87feaccf94dcb0c79da4492d1d79142cc310e0b0f27c106c22058ee72f757581e8a44da511883566a63f3fe40019a7dec565f9ba7dbec3f4ef3716a54a8e1cca52587011e6edf9faa9eefdba865ea4f9e915b179fa478bfb8edfd126b58da8c4a053f42d167a86aeb728e8afae3e298443d3ef98dbe2b9f34b0b8520de806432e28eb14bf9397a199468f1d7428f736655ff807cc24e988ea3432c5dfd8a9c6ccb732fa531ce78575749b16e26ff360b2732ddd1267d94f3a7b3f9087a8509c5aa48130da5402da4e7b7480a72305a2a8e168a07d5237bd7d0f38c3b49cc74c0437900753a553fe9b9ecf1e8a56bc88d953b61e7bc0419035b1ca9ed83026015a69c6a29deea67990ec30861fc5e3ae3353b2fb0e2d3403935a4ba633cab4f857a796c19f1f6978df70cf93f4e113500a6929dd18f34d6c12e450999d58c41750bad207b897fcecb0f1a94537f690f3d4f096db522c07caa244953cdc169c3b757036e0ef09119985c78eb4a6e3db3982a89373ffa0bb46f213dff69e2bf5e6387a5c239657ab5fb4d9add378d6a18a1636b68ee4f7620849b36845a2deee73851e5af64f023381a84ec64a5490c9bc079bea3023af535938d15173527aee29323f6edc7585d54395341a7e54cd540e57339d37606d782eb8171b576abfd52706001c699d956361e72b2f14e3c98071d3a8e26a774ff6f7260891626e2aa2244d04d94b97c88df28de99ff68146fd7fff62d696d144f3fdd7f79a4e3ac7289cd0677d3986d0065542565663d9d110ffb63174c77e854ef50dcacc472c7fd6b8de0c68542513acdc5432200b3fbbff3f67657c77cacf3f60db7072d4893d0ff5d8cf17e547bc19d3d4ef0cda3219e3174def2b085b23a3523c9297937c8f3ca53a5323885d4910e7291931d5baeecde27428e481bfca949f42a2f567d92eedf3fc7121a9052ac8fd918f0544e505c0495a9f19d328e12e302b2d336abda513421e0a4e58205a8b6c79ca413419dd7985bb954ef97e89a9b451a95858ea4066b48186b7450478b322515a7cf490cc0f498949bf9a9bf4d2d856058a42ae571f9656ebd750f5b5d5c74449acdad36277fe449e337b90c3c87b39192dc3250476c9cf6764cccbbbf2770d362aeeea7731f6b51f94c7ccf6e5b515bd3dea6f7db77e335f192e8ba1ed2be316bf2d198c7e091b9d5d989559733bbc2d2b86e5ca1c1b3551ad0057d16b25b9606200f6c9b2042c84ac31e46c99ea6cfa1940810686192e9a5f6fb0e9fd0f1c1c7d83e0f8de481ccb701034155b32c1c0c3", 16);
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