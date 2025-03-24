#include "ExampleListener.h"
#include "JsonListener.h"


void json_print(String value) {
  #ifdef ARDUINO
  Serial.println(value.c_str());
  #else
  printf("%s\n", value.c_str());
  #endif
}
void ExampleListener::whitespace(char c) {
  json_print("whitespace");
}

void ExampleListener::startDocument() {
  json_print("start document");
}

void ExampleListener::key(String key) {
  json_print("key: " + key);
}

void ExampleListener::value(String value) {
  json_print("value: " + value);
}

void ExampleListener::endArray() {
  json_print("end array. ");
}

void ExampleListener::endObject() {
  json_print("end object. ");
}

void ExampleListener::endDocument() {
  json_print("end document. ");
}

void ExampleListener::startArray() {
  json_print("start array. ");
}

void ExampleListener::startObject() {
  json_print("start object. ");
}

