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
    mpz_init_set_str(modulus, "b59ef56b82f576719a27ac71aa9c90a8d8545934eb025a501ec9d2ac4045631bb2e3282fb4ba32361bc0c9cc8e522ee1e958451cf4f56651ffdc8a1c8afd7ae3f9688666cc9b56cbc429adbcb86faee504380b6121bb230208a947d0c13e1e7825c8b2d0fd9b8048fbdb5afce001020fde6ad53f1f99e87f7a6e2505be33216fa39d13a1f10bcba0a8d7e6683d78e4b04dd63b3a132d83a7ce2084943353d63ce4e14304baf2bb394cedb1dc182f9225d9201fa95c21ae27083c14cb5327edfa900f7d29355966c5cb9dd67adfbe778394c43a49dfbf198d5fb275251340d1b4dab02c6b93743bb78c02e2d9e7f135f717977e382ebff3c23c4ebedae396555643dc25dbc7b43925af1cf1705861fdccad8e7e8cc8b6cec61ddc9469b7b833569c407ed35a1133c9a8b8094faef277d65e5ddc33e4b411469347a16f57b94685d35068d4f5c1def5381352c65f53cc1f5aec45629e0581549c91051a2bf2da68e4d41f74d448ab1057f3a57b8e2f8792442cf9abf38bcfb884a894450027154f74fb8208a7fa3dbe9370af5bbcf866f3dc9e3b73d6bd06e11297cbd0b840c7823e075c63c45bac0309ccff3fab9a75284494d23bf4c18d4effb4cfe7590e9b953ce56128de9f439ac9bddfa4702f8d542aa2d78e286992b15af258e0c2a142b4d5dc7090cc9600a51d0ba26013641f1803b9aaa9cf42f876d7549f2a945f7ad416767b3f5d6a58070eacc3e1fd5a104426450577ff1a1d333837de400a7e01f6aaa170eebd717302ab3a66ec51e8873e3be50c7d84767a74eea2852ec51edee0091544d39319c3f24086c4e5ffd87310e086686ca9140e6eee6288f231fa155140f3b7ef7fe021158b97e45a29af998839ad4c55c54a7ad39430a745b903c70831943a7fc6c40bd81626e37b5f153c03f06563f7f2fdb45fd30277cdbbdcd98aadee3605006665d73cef353ccde9610c7cbf03b8a720a1b270d36ddb97ad49b964ade4644c40f7386f6aece9599bf3a4f19bc3568d418417542421287db1fedb64903b0e47fffb20b1779374bfbd57130a76b3a9c0c7e307294cd9dd10f812cd975847193955c1288fa8f35eb69dfe214758e094b48532a057ff9cab7f231231e4b5df13aaa3f0bfaf17feb314ffa370d9d81d855f96288d7f23b2c469efcbb7adfed3422cabad1ba2cdc1e0e3c082ad4de91e95a71544422184572524be9068a32f4dfb88174e5886ac4cd2e4193fd90edac1b40003b88af50fea67c160905b8cb9ea981cf906ee5cc162c43f5da23581511a6f7df1f56b70e1df28065f9e4ccb6a511eee9e727469497d82c81c87d6f7d4710467896243b881c9c5339ada760fbfb11aa3fd2ef61a13951d3313668dcb9f4015ca488c1c1f4f2efc66c95547f1dcdb1a0a7cb3d422046f9126265ef6153fd42276690e2295a0fca75ef12fac2c9c8aee268c72db84a6b58e00a95aa5d90849381698af76a42bb21e18a2660ae9c48f57a9b091e9722f51ab51f20c554f6304f1634d3c0dbb33cb5dd6ad7feb5c185a6982df1cb27bc51b6c93afb90e13f430a87927d4063975f0030ee6f69830a50066d18b72142048a2b8344ad80534b33436165169a43fdd761b9366ba52ab9bc8dec14232c91b328f9da40df826af6b35e9eb27e5f2eeb0f3046de08762aa0107572babb63191d064e8f809c7c62021b95509659891004a59fca333fc440c6a4032004846aed1238ae0d5a5b7dbc86f886f5be6e54692775ab1f1d835042d33218b59314036e5a73172c6f749c80c466f7859e00497b41c8a57135443d57233a13814cdaa1a390819130ddaab46faff720a5ddd64734a5813185df4be03ceb06f1594f699b47aeec4b306aaaf180a70b8849cda70a540b38f4de881cdbf02ad61c575835d9d7a168381c739d91edd92dd5b1e54678481c0c4e686af8897686b6648bf35f8608ab2501d85864d46d4d1aed2d49d2ebc20091ad72c889777353a69c36cd6c2fc0203d6672806048476da847736af9d539dfdade6ab8fc4b7025b11410c3bc0107da6a480ad5fbef112915476b184f50ae1c4e77a2b09f113c38584c948073f40199c08efa558ece2b6129e8d50d37784fa8fac8cd257ab62b8b28dfaedfcf8a5e8c9fc3b320c4421b7127ce08bc046f53d05c63463fecad30ac8274b3bcfb1e936069dec881f983c8cedca5eae966e61ec978bf35d2faa29d6dfff68d5fcd9a23db6f376d43018cab95ed9da5d2bfc5223051110efcfb9d9fd447882f609142a9c8fedd31bbfdf4e7679a440b71be42b9797341933f56f92c18d33a5ee0a45c2f4d948d4ffa64094f1d1a6698bbba19e62c3b913c806354c118c254cc328ec49f61b3d424a9de1df9122a18e77bf0aa5be487ef0bca29d2df59d263a1daa7d29442b87c3578c8adc610ca8ced9e38590fd99365f78c01d1bf244798bf289c2dd2108d4331e3c0f123992ddcdbb37edd8a5b58a2f57d2e81d50b859381b5a726376b158975960df7d6a9ed4a97410bf2ebd457c87631903d4f5f5c60bed5a1bbf1212b6274f0da7a8e16f61bf853dfbea8f544e3a75b242ae89214676e1b2704d3a621e89ff025af5dc76eab12b8ac609fca7b5dabe2e44a13318fc8244eaf02299564771f03156ce97e7ec3a99014bea7766c0f54d30bcda02afde1589b170a6ae75cd8bb02de8c33d4b32d826c8b6ebacc793f4ba9a9b34bf2194afbc46c10d2991e8225b76f1f2ea8cc5a5d932f6d018a13a8f85756f844a6777e234e6cffab22c2759a05d6dd0afb5a05ff967cc008b004ddc9ad7fed24cf67c45eeb75498bcc1977a512f11ecf6c962c9709d621f0a96ea00cd7c9ddb51a6047147b66cf9f3387d0c4226574b363a50b0f3346d442ab9416e2179bea3", 16);
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
