#ifndef SOCKETLITE_UTILITY_MEMORY_H
#define SOCKETLITE_UTILITY_MEMORY_H
#include <cstring>
#include "SL_Config.h"

class SL_Utility_Memory
{
public:
    SL_Utility_Memory()
    {
    }

    ~SL_Utility_Memory()
    {
    }

    //�ڴ濽��
    //������:  window7-32 vc2010 cpu: 4*i5-2310 memory: 4G:
    //              1)С���ڴ�ʱ, ��8�ֽ�������ֵ,������������;
    //              2)����ڴ�ʱ, ��8�ֽ�������ֵ,���ܷ����½�;�����ڴ�����256ʱ,ֱ�ӵ���׼��memcpy.
    //         linux:
    //              1)���ܿ��ܺ�Щ,Ҳ���ܲ�Щ(ʹ��ǰ,�������л�������ϸ����)
    //              2)centos6.3      x86-64 kernel:2.6.32 gcc:4.4.6 cpu:4*i5-2310  memory:4G 8�ֽ�������ֵ ������������
    //              3)centos7.0.1406 x86-64 kernel:3.10.0 gcc:4.8.2 cpu:4*i5-3330S memory:8G 8�ֽ�������ֵ �� ��׼memcpy �����Բ�.
    static void* memcpy(void *dest, const void *src, size_t n);

    //�ڴ�����
    static void memclear(void *dest, size_t n);

    //�ڴ�Ƚ�
    static inline int memcmp(const void *s1, const void *s2, size_t n)
    {
        return std::memcmp(s1, s2, n);
    }

    //�ڴ���ֵ
    //��һ��ʵ�ַ�ʽ: Ԥ�ȼ���  8�ֽ�������ֵ(ÿ�ֽڶ���������c����ֵ)
    //                        4�ֽ�������ֵ(ÿ�ֽڶ���������c����ֵ)
    //                        2�ֽ�������ֵ(ÿ�ֽڶ���������c����ֵ)
    static inline void* memset(void *dest, int c, size_t n)
    {
        return std::memset(dest, c, n);
    }

    static inline void* memmove(void *dest, const void *src, size_t n)
    {
        return std::memmove(dest, src, n);
    }
};

#ifdef SOCKETLITE_OS_WINDOWS
    #define SL_MEMCPY(dest, src, n)     std::memcpy(dest, src, n)
    #define SL_MEMCLEAR(dest, n)        std::memset(dest, 0, n)
    #define SL_MEMCMP(s1, s2, n)        std::memcmp(s1, s2, n)
    #define SL_MEMSET(dest, c, n)       std::memset(dest, c, n)
    #define SL_MEMMOVE(dest, src, n)    std::memmove(dest, src, n)

    #define sl_memcpy(dest, src, n)     SL_Utility_Memory::memcpy(dest, src, n)
    #define sl_memclear(dest, n)        SL_Utility_Memory::memclear(dest, n)
    #define sl_memcmp(s1, s2, n)        std::memcmp(s1, s2, n)
    #define sl_memset(dest, c, n)       std::memset(dest, c, n)
    #define sl_memmove(dest, src, n)    std::memmove(dest, src, n)
#else
    #define SL_MEMCPY(dest, src, n)     std::memcpy(dest, src, n)
    #define SL_MEMCLEAR(dest, n)        std::memset(dest, 0, n)
    #define SL_MEMCMP(s1, s2, n)        std::memcmp(s1, s2, n)
    #define SL_MEMSET(dest, c, n)       std::memset(dest, c, n)
    #define SL_MEMMOVE(dest, src, n)    std::memmove(dest, src, n)

    //��SL_Utility_Memory::memcpy��ios�¿��ܻ����,
    //�����ڷ�windows����Ҫ�����SOCKETLITE_USE_CUSTOM_MEMCPY������sl_memcpyʵ��ΪSL_Utility_Memory::memcpy
    #ifdef SOCKETLITE_USE_CUSTOM_MEMCPY
        #define sl_memcpy(dest, src, n) SL_Utility_Memory::memcpy(dest, src, n)
        #define sl_memclear(dest, n)    SL_Utility_Memory::memclear(dest, n)
    #else
        #define sl_memcpy(dest, src, n) std::memcpy(dest, src, n)
        #define sl_memclear(dest, n)    std::memset(dest, 0, n)
    #endif

    #define sl_memcmp(s1, s2, n)        std::memcmp(s1, s2, n)
    #define sl_memset(dest, c, n)       std::memset(dest, c, n)
    #define sl_memmove(dest, src, n)    std::memmove(dest, src, n)
#endif

#endif

