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

class ArduinoString : public std::string {
    public:
        ArduinoString(const char* c_str) : std::string(c_str) {}
        ArduinoString(std::string str) : std::string(str) {}
        
        boolean equals(ArduinoString other){
            return compare(other) == 0;
        }

        ArduinoString operator +(ArduinoString other){
            return ArduinoString(this->append(other));
        }
};

class ArduinoStream {
    public:
        virtual int available() {return 0;}
        virtual int read() {return 0;}
        virtual int peek() {return 0;}
};

void delay(int ms){}

typedef ArduinoString String;
typedef ArduinoStream Stream;

#endif // ARDUINO
#endif // __MULTIPLATFORM_H__