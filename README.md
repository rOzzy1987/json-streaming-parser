# json-streaming-parser
Arduino library for parsing potentially huge json streams on devices with scarce memory.

This library is a fork of squix78's port (https://github.com/squix78/json-streaming-parser/archive/master.zip) 
of Salsify's PHP based json streaming parser (https://github.com/salsify/jsonstreamingparser).

## Why yet another JSON parser?

When working with small (connected) devices you might quickly get to the point where you need to process potentially huge JSON object received from a REST interface.
All libraries for processing JSON objects on the Arduino platform had some deficiencies which led me to create one on my own.
Not really being an expert in writing parsers I miserably failed the first time. 

This is the second attempt and I took Salsify's PHP based parser and ported it to C++. 
This library has been tested on the Arduino/ESP8266 target platform but should work in theory on all platforms available for the Arduino environment

## Why a streaming parser?

Generally speaking when parsing data you have two options to make sense of this data: 
you either create a document object model (DOM) which contains the whole information of that document and lets you retrieve the
nodes with random access. A DOM parser needs the whole document to start parsing and only lets you access the data
after it has finished the process.
The other option you have when parsing a document is to process it char by char (or byte by byte) while it becomes
available to your client code. Compared to the DOM parser this has two advantages: a) you can react
the data as soon as meaningful parts are available and b) you can drop information as soon as the parser has processed
it. This reduces the memory consumption a lot, especially if you retrieve huge documents when only being interested
by a small subset of it. But this efficiency comes at a price: your code will have to do more "magic" than with a
DOM parser, the business logic becomes part of the parser.

## How to install

### Arduino IDE
Until the library becomes available in the Arduino IDE library manager you'll have to do a bit more work by hand.
1) Download this library: https://github.com/squix78/json-streaming-parser/archive/master.zip
2) Rename master.zip to json-streaming-parser.zip
3) Open the zip file in the Arduino IDE from menu Sketch > Include Library > Add ZIP Library...

### Platformio IDE
There are 2 main methods to install:
1) Using the library manager of platformio add the library to the project
2) Add `rozzy1987/JsonStreamingParser@^1.0.0` to `lib_deps` key in your project's `platformio.ini` file 

## How to use

This is a streaming parser, which means that you feed a stream of chars into the parser and you take out from that
stream whatever you are interested in. In order to do that you will create a subclass of JsonListener class and
implement methods which will be notified in case of certain events in the feed occure. Available events are:

 * startDocument()
 * key(String key)
 * value(String value)
 * endArray()
 * endObject()
 * endDocument()
 * startArray()
 * startObject()

In your implementation of these methods you will have to write problem specific code to find the parts of the document that you are interested in. Please see the example to understand what that means. In the example the ExampleListener implements the event methods declared in the JsonListener interface and prints to the serial console when they are called.

## License

This code is available under the MIT license, which basically means that you can use, modify the distribute the code as long as you give credits to me (and Salsify) and add a reference back to this repository. Please read https://github.com/squix78/json-streaming-parser/blob/master/LICENSE for more detail...

## Credits

- @Salsify (original PHP implementation, https://github.com/salsify)
- @squix78 (original c++ port, https://github.com/squix78)
- Maciej Dobrzanski (bufixes, https://github.com/dbnski)
- @bigbug (bugfixes, "https://github.com/bigbug")