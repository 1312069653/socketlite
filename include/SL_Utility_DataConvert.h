#ifndef SOCKETLITE_UTILITY_DATA_CONVERT_H
#define SOCKETLITE_UTILITY_DATA_CONVERT_H
#include "SL_DataType.h"
#include "SL_Config.h"

class SL_Utility_DataConvert
{
public:
    SL_Utility_DataConvert()
    {
    }

    ~SL_Utility_DataConvert()
    {
    }

    //�ַ���ת4�ֽ�����
    static int32   atoi(const char *str);
    static int32   atoi(const char *str, uint len, char **endptr);
    //�ַ���ת4�ֽ��޷�������
    static uint32  atoui(const char *str);
    static uint32  atoui(const char *str, uint len, char **endptr);
    //�ַ���ת8�ֽ�����
    static int64   atoll(const char *str);
    static int64   atoll(const char *str, uint len, char **endptr);
    //�ַ���ת8�ֽ��޷�������
    static uint64  atoull(const char *str);
    static uint64  atoull(const char *str, uint len, char **endptr);

    //4�ֽ��޷�������ת10�����ִ�
    static int uitoa(uint32 value, char str[12]);

    //4�ֽ�����ת10�����ִ�
    static inline int itoa(int32 value, char str[12])
    {
        if (value >= 0)
        {
            return uitoa(value, str);
        }
        else
        {
            *str++ = '-';
            return uitoa(-value, str) + 1;
        }
    }

    //8�ֽ��޷�������ת10�����ִ�
    static int ulltoa(uint64 value, char str[21]);

    //8�ֽ�����ת10�����ִ�
    static inline int lltoa(int64 value, char str[21])
    {
        if (value >= 0)
        {
            return ulltoa(value, str);
        }
        else
        {
            *str++ = '-';
            return ulltoa(-value, str) + 1;
        }
    }

    //��������תΪ10�����ַ����ĳ���
    static inline int digits10(uint32 value)
    {
        if (value < 10)
            return 1;
        if (value < 100)
            return 2;
        if (value < 1000)
            return 3;
        if (value < 10000)
            return 4;
        if (value < 100000)
            return 5;
        if (value < 1000000)
            return 6;
        if (value < 10000000)
            return 7;
        if (value < 100000000)
            return 8;
        if (value < 1000000000)
            return 9;
        return 10;
    }

    //��������תΪ10�����ַ����ĳ���
    static inline int digits10(uint64 value)
    {
        if (value < 10ull)
            return 1;
        if (value < 100ull)
            return 2;
        if (value < 1000ull)
            return 3;
        if (value < 10000ull)
            return 4;
        if (value < 100000ull)
            return 5;
        if (value < 1000000ull)
            return 6;
        if (value < 10000000ull)
            return 7;
        if (value < 100000000ull)
            return 8;
        if (value < 1000000000ull)
            return 9;
        if (value < 10000000000ull)
            return 10;
        if (value < 100000000000ull)
            return 11;
        if (value < 1000000000000ull)
            return 12;
        if (value < 10000000000000ull)
            return 13;
        if (value < 100000000000000ull)
            return 14;
        if (value < 1000000000000000ull)
            return 15;
        if (value < 10000000000000000ull)
            return 16;
        if (value < 100000000000000000ull)
            return 17;
        if (value < 1000000000000000000ull)
            return 18;
        if (value < 10000000000000000000ull)
            return 19;
        return 20;
    }

    static char digits_[201];
};

#endif

