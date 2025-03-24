#ifndef __MULTIPLATFORM_H__
#define __MULTIPLATFORM_H__

#ifdef ARDUINO 
#include <Arduino.h>
#else

#include <string>
// #include <string.h>

template<typename T> inline T min(T a, T b){
    return a > b ? b : a;
} 
template<typename T> inline T max(T a, T b){
    return a > b ? a : b;
} 

typedef bool boolean;

class String : public std::string {
    public:
        String(const char* c_str) : std::string(c_str) {}
        String(std::string str) : std::string(str) {}
        
        boolean equals(String other){
            return compare(other) == 0;
        }

        String operator +(String other){
            return String(this->append(other));
        }
};

#endif // ARDUINO
#endif // __MULTIPLATFORM_H__