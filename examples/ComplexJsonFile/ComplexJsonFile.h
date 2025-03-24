#include "sample.json.h"
#include "JsonStreamingParser.h"
#include "ExampleListener.h"
#include <string.h>

void setup() {
    ExampleListener listener = ExampleListener();
    JsonStreamingParser parser = JsonStreamingParser();

    parser.setListener(&listener);

    for (int i = 0; i < strlen(json_sample); i++)
    {
        parser.parse(json_sample[i]);
    }
}

void loop() {

}

#ifndef ARDUINO
int main() {
    setup();
    loop();
    return 0;
}
#endif