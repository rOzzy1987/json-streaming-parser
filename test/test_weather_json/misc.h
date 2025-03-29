
#include "../../include/JsonStreamingParser.h"

void test_printf(const char* fmt, ...) { 
    // va_list args; 
    // va_start(args, fmt); 
    // vprintf(fmt, args); 
    // va_end(args);
}

void test_error_vprintf(const char* fmt, va_list args) { 
    vprintf(fmt, args);
    printf("\n");
}

class TestListener: public JsonListener {
    public:
        virtual void whitespace(char c) { test_printf("%s\n",__FUNCTION__); };
        virtual void startDocument() { test_printf("%s\n",__FUNCTION__); };
        virtual void key(String key) { test_printf("%s %s\n",__FUNCTION__, key.c_str()); };
        virtual void value(String value) { test_printf("%s %s\n",__FUNCTION__, value.c_str()); };
        virtual void endArray() { test_printf("%s\n",__FUNCTION__); arraysClosed++; };
        virtual void endObject() { test_printf("%s\n",__FUNCTION__); objectsClosed++; };
        virtual void endDocument() { test_printf("%s\n",__FUNCTION__); };
        virtual void startArray() { test_printf("%s\n",__FUNCTION__); arraysCreated++; };
        virtual void startObject() { test_printf("%s\n",__FUNCTION__); objectsCreated++; };

        uint8_t objectsCreated = 0;
        uint8_t objectsClosed = 0;
        uint8_t arraysCreated = 0;
        uint8_t arraysClosed = 0;
};

class MemoryStream : public ArduinoStream {
    public:
        MemoryStream(const char* buffer, int32_t size) :_buffer(buffer), _size(size), _pos(0) {}
        virtual int available() override { return _size - _pos;}
        virtual int read() override {return _buffer[_pos++];}
        virtual int peek() override {return _buffer[_pos];}
    private:
        const char* _buffer;
        int32_t _size;
        int32_t _pos = 0;
};


TestListener listener;
JsonStreamingParser parser;