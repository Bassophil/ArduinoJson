// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

#ifdef HAS_VARIABLE_LENGTH_ARRAY

TEST_CASE("Variable Length Array") {
  SECTION("deserializeJson()") {
    int i = 9;
    char vla[i];
    strcpy(vla, "{\"a\":42}");

    StaticJsonDocument<JSON_OBJECT_SIZE(1)> doc;
    DeserializationError err = deserializeJson(doc, vla);

    REQUIRE(err == DeserializationError::Ok);
  }

  SECTION("deserializeMsgPack()") {
    int i = 16;
    char vla[i];
    memcpy(vla, "\xDE\x00\x01\xA5Hello\xA5world", 15);

    StaticJsonDocument<JSON_OBJECT_SIZE(1)> doc;
    DeserializationError err = deserializeMsgPack(doc, vla);

    REQUIRE(err == DeserializationError::Ok);
  }
}
#endif
