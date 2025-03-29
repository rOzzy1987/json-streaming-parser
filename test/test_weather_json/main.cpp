#include <Unity.h>
#include "misc.h"
#include "sample.json.h"
#include "sample.err.json.h"


void test_weather_json() {
    Stream *stream = new MemoryStream(json_sample, sizeof(json_sample));
    parser.parse(stream);

    TEST_ASSERT_EQUAL(listener.objectsCreated, listener.objectsClosed);
    TEST_ASSERT_EQUAL(listener.arraysCreated, listener.arraysClosed);    
    TEST_ASSERT_EQUAL(0, parser.errorCount());    
}

void test_erroneous_json() {
    Stream *stream = new MemoryStream(json_err_sample, sizeof(json_err_sample));
    parser.parse(stream);

    TEST_ASSERT_GREATER_THAN(0, parser.errorCount());
}

void setUp(){
    parser = JsonStreamingParser();
    listener = TestListener();
    parser.setListener(&listener);
    parser.setErrorCallback(test_error_vprintf);    
}
void tearDown(){
    parser.reset();
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_weather_json);
    RUN_TEST(test_erroneous_json);
    UNITY_END();
}

