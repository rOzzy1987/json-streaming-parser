const char* json_sample = R"JSON(
{
    "simpleValue": 1234,
    "simpleFloatValue": 12.345,
    "normalizedFloat": 1.345e-6,
    "boolean": true,
    "string": "str1234",
    "arrayOfSimpleValues": [
        "text",
        6234,
        false
    ],
    "arraOfObjects": [
        {
            "utf8String": "éáőúüóóű",
            "escapedString": "\"\u3fd4"
        },
        {
            "whatever": "lol",
            "nullValue": null
        }
    ]
})JSON";