/**The MIT License (MIT)

Copyright (c) 2015 by Daniel Eichhorn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

See more at http://blog.squix.ch and https://github.com/squix78/json-streaming-parser
*/

#pragma once

#include <stdint.h>
#include <stdarg.h>
#include "crossplatform.h"
#include "JsonListener.h"

#define STATE_START_DOCUMENT     0
#define STATE_DONE               255
#define STATE_IN_ARRAY           1
#define STATE_IN_OBJECT          2
#define STATE_END_KEY            3
#define STATE_AFTER_KEY          4
#define STATE_IN_STRING          5
#define STATE_START_ESCAPE       6
#define STATE_UNICODE            7
#define STATE_IN_NUMBER          8
#define STATE_IN_TRUE            9
#define STATE_IN_FALSE           10
#define STATE_IN_NULL            11
#define STATE_AFTER_VALUE        12
#define STATE_UNICODE_SURROGATE  13
#define STATE_UNESCAPED_UTF8     14

#define STACK_OBJECT             1
#define STACK_ARRAY              2
#define STACK_KEY                3
#define STACK_STRING             4

#define BUFFER_INITIAL_LENGTH  64

typedef void (*printf_callback)(const char* format, va_list args);

class JsonStreamingParser {
  private:
    uint8_t state;
    uint8_t *stack = new uint8_t[20];
    uint8_t stackPos = 0;
    JsonListener* myListener;

    boolean doEmitWhitespace = false;
    // fixed length buffer array to prepare for c code
    char *buffer = new char[BUFFER_INITIAL_LENGTH];
    int16_t bufferPos = 0;
    int16_t bufferLength = BUFFER_INITIAL_LENGTH;

    char unicodeEscapeBuffer[10];
    uint8_t unicodeEscapeBufferPos = 0;
    
    char utf8Length = 0;
    char utf8Pos = 0;

    char unicodeBuffer[10];
    uint8_t unicodeBufferPos = 0;

    int characterCounter = 0;
    int unicodeHighSurrogate = 0;

    void increaseBufferPointer();
    boolean isDigit(unsigned char c);
    boolean isHexCharacter(unsigned char c);

    void processEscapeCharacters(unsigned char c);
    unsigned char convertCodepointToCharacter(int num);
    void endUnicodeCharacter(int codepoint);
    void endUnicodeSurrogateInterstitial();

    int getHexArrayAsDecimal(unsigned char hexArray[], int length);
    int getHexArrayAsDecimal(char hexArray[], int length);

    int convertDecimalBufferToInt(unsigned char myArray[], int length);

    void pushStack(uint8_t s) { stack[stackPos++] = s; };
    uint8_t popStack() { return stack[--stackPos]; };
    uint8_t peekStack() {  return stack[stackPos - 1]; };

    void startNumber(unsigned char c);
    void startString();
    void startObject();
    void startArray();
    void startValue(unsigned char c);
    void startKey();
    void endString();
    void endArray();
    void endNull();
    void endFalse();
    void endTrue();
    void endDocument();
    void endNumber();
    void endObject();

    void error(const char* format, ...);

    boolean doesCharArrayContain(unsigned char myArray[], int length, unsigned char c);
    boolean doesCharArrayContain(char myArray[], int length, unsigned char c);

    void processUnicodeCharacter(unsigned char c);

    printf_callback error_callback = nullptr;

    unsigned int lineNumber = 1;
    unsigned int columnNumber = 0;
    unsigned int _errorCount = 0;

  public:
    JsonStreamingParser();
    void parse(char c);
    void parse(unsigned char c);
    void parse(Stream* stream);
    void setListener(JsonListener* listener);

    int16_t getBufferLength() { return bufferLength; };
    void setBufferLength(int16_t length) { 
      char* nb = new char[length];
      if(buffer != nullptr) {
        memcpy(nb, buffer, min(bufferLength, length));
        delete[] buffer;
      }
      buffer = nb;
      bufferLength = length;
    };

    void setErrorCallback(printf_callback callback) { error_callback = callback; };
    unsigned int errorCount() { return _errorCount; };
    void reset();
};
