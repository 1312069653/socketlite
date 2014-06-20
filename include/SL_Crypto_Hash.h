#ifndef SOCKETLITE_CRYPTO_HASH_H
#define SOCKETLITE_CRYPTO_HASH_H

class SL_Crypto_Hash
{
public:
    enum TYPE 
    {
        MD5         = 1,    //���ƽ�
        SHA1        = 2,    //���ƽ�
        SHA256      = 3,    //sha2-256 �Ƽ�ʹ��
        SHA512      = 4,    //sha2-512 �Ƽ�ʹ��
        SHA3_256    = 5,    //sha3-256
        SHA3_512    = 6,    //sha3-512
    };

    SL_Crypto_Hash()
    {
    }

    virtual ~SL_Crypto_Hash()
    {
    }

    virtual int get_digest_len() = 0;
    virtual int init() = 0;
    virtual int update(const unsigned char *in, unsigned int in_len) = 0;
    virtual int final(unsigned char *digest) = 0;
    virtual int final(const unsigned char *in, unsigned int in_len, unsigned char *digest) = 0;
};

#endif

