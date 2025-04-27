#pragma once

#include <array>

namespace RUtil{
class String_magic
{
    String_magic() = delete;
    String_magic(const String_magic &) = delete;
    String_magic(String_magic &&) = delete;
    ~String_magic() = delete;
    String_magic &operator=(const String_magic &) = delete;
    String_magic &operator=(String_magic&&)=delete;

    template <std::size_t N1, std::size_t N2>
    static constexpr std::array<char, N1+N2-1> string_concat(const char (&a)[N1], const char (&b)[N2]){
        std::array<char, N1+N2-1> re{};
        for(std::size_t i=0;i<N1-1;i++) re[i]=a[i];
        for(std::size_t i=0;i<N2;i++) re[N1-1+i]=b[i];
        re.back()='\0';
        return re;
    }

    template <std::size_t N1, std::size_t N2>
    static constexpr auto string_concat(std::array<char, N1> a, const char (&b)[N2]){
        std::array<char, N1+N2-1> re{};
        for(std::size_t i=0;i<N1-1;i++) re[i]=a[i];
        for(std::size_t i=0;i<N2;i++) re[N1-1+i]=b[i];
        re.back()='\0';
        return re;    
    }

    template <std::size_t N>
    static constexpr auto string_concat(std::array<char, N> a){return a;}

    template <std::size_t N>
    static constexpr auto string_concat(const char (&a)[N]){
       std::array<char, N> re{};
       for(size_t i=0;i<N;i++) re[i]=a[i];
       re.back()='\0';
       return re;
    }
    
    template <std::size_t N1, std::size_t N2, std::size_t N3, std::size_t...Args>
    static constexpr auto string_concat(std::array<char, N1> a, const char (&b)[N2], const char (&c)[N3], const char (&...args)[Args]){
        return string_concat(string_concat(a,b), c, args...);
    }

    template <std::size_t N1, std::size_t N2, std::size_t N3, std::size_t...Args>
    static constexpr auto string_concat(const char (&a)[N1], const char (&b)[N2], const char (&c)[N3], const char (&...args)[Args]){
        return string_concat(string_concat(a,b), c, args...);
    }
};
}