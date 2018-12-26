#ifndef SOCKETLITE_CRYPTO_RAND_H
#define SOCKETLITE_CRYPTO_RAND_H
#include "SL_Config.h"

class SL_Crypto_Rand
{
public:
    enum TYPE
    {
        RANDOM_CHAR = 0,        // ��unsinged char ��������ڴ��
        VISIBLE_CHAR,           // ��char ������� �����ַ���(���̿�������)
        STANDARD_CHAR,          // ��char ������� ��׼�ַ���(�����������ַ���)
        ENLARGE_CHAR,           // ��char ������� ��ǿ�ͱ�׼�ַ���(�����Զ���������ַ�)
        NUMBER_CHAR,            // ��char ������� ������(0-9)
        LOWERCASE_CHAR,         // ��char ������� Сд��ĸ(a-z)
        UPPERCASE_CHAR,         // ��char ������� ��д��ĸ(A-Z)

        TYPE_NUMS,
    };

    SL_Crypto_Rand();
    virtual ~SL_Crypto_Rand();

    virtual void    seed(int nseed) = 0;
    virtual int     random_int() = 0;
    virtual int     random_int(int low, int high);
    virtual double  random_double();
    virtual double  random_double(double low, double high);
    virtual int     random_byte(char *out, unsigned int out_len, SL_Crypto_Rand::TYPE type, const char *special_char);
    virtual int     random_byte(char *out, unsigned int out_len, int low, int high);

protected:
    virtual char    random_mt_char();                          // ���ɱ�׼�ַ�
    virtual char    random_mt_char(const char* special_char);  // �������ַ�(specialchar)���� ��ǿ���ַ�

    // Randomizes a buffer
    virtual void    fill_buffer_mt(char *buffer, unsigned int bytes);

    // Randomizes a buffer by type
    virtual void    fill_buffer_mt(char *buffer, unsigned int bytes, int type);
    virtual void    fill_buffer_mt(char *buffer, unsigned int bytes, const char *special_char);
};

#endif

