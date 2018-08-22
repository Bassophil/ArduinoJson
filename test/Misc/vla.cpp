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

  SECTION("JsonObject") {
#ifndef SUBSCRIPT_CONFLICTS_WITH_BUILTIN_OPERATOR
    SECTION("operator[]") {
      int i = 16;
      char vla[i];
      strcpy(vla, "hello");

      DynamicJsonDocument doc;
      JsonObject obj = doc.to<JsonObject>();
      obj[vla] = "world";

      REQUIRE(std::string("world") == obj["hello"]);
    }
#endif

#ifndef SUBSCRIPT_CONFLICTS_WITH_BUILTIN_OPERATOR
    SECTION("operator[] const") {
      int i = 16;
      char vla[i];
      strcpy(vla, "hello");

      DynamicJsonDocument doc;
      deserializeJson(doc, "{\"hello\":\"world\"}");

      JsonObject obj = doc.as<JsonObject>();
      REQUIRE(std::string("world") == obj[vla]);
    }
#endif

    SECTION("get()") {
      int i = 16;
      char vla[i];
      strcpy(vla, "hello");

      DynamicJsonDocument doc;
      deserializeJson(doc, "{\"hello\":\"world\"}");

      JsonObject obj = doc.as<JsonObject>();
      REQUIRE(std::string("world") == obj.get<char*>(vla));
    }

    SECTION("containsKey()") {
      int i = 16;
      char vla[i];
      strcpy(vla, "hello");

      DynamicJsonDocument doc;
      deserializeJson(doc, "{\"hello\":\"world\"}");

      JsonObject obj = doc.as<JsonObject>();
      REQUIRE(true == obj.containsKey(vla));
    }

    SECTION("remove()") {
      int i = 16;
      char vla[i];
      strcpy(vla, "hello");

      DynamicJsonDocument doc;
      deserializeJson(doc, "{\"hello\":\"world\"}");
      JsonObject obj = doc.as<JsonObject>();
      obj.remove(vla);

      REQUIRE(0 == obj.size());
    }

    SECTION("is<T>()") {
      int i = 16;
      char vla[i];
      strcpy(vla, "hello");

      DynamicJsonDocument doc;
      deserializeJson(doc, "{\"hello\":42}");
      JsonObject obj = doc.as<JsonObject>();

      REQUIRE(true == obj.is<int>(vla));
    }

    SECTION("createNestedArray()") {
      int i = 16;
      char vla[i];
      strcpy(vla, "hello");

      DynamicJsonDocument doc;
      JsonObject obj = doc.to<JsonObject>();
      obj.createNestedArray(vla);
    }

    SECTION("createNestedObject()") {
      int i = 16;
      char vla[i];
      strcpy(vla, "hello");

      DynamicJsonDocument doc;
      JsonObject obj = doc.to<JsonObject>();
      obj.createNestedObject(vla);
    }
  }

  SECTION("JsonObjectSubscript") {
    SECTION("operator=") {  // issue #416
      int i = 32;
      char vla[i];
      strcpy(vla, "world");

      DynamicJsonDocument doc;
      JsonObject obj = doc.to<JsonObject>();
      obj["hello"] = vla;

      REQUIRE(std::string("world") == obj["hello"].as<char*>());
    }

    SECTION("set()") {
      int i = 32;
      char vla[i];
      strcpy(vla, "world");

      DynamicJsonDocument doc;
      JsonObject obj = doc.to<JsonObject>();
      obj["hello"].set(vla);

      REQUIRE(std::string("world") == obj["hello"].as<char*>());
    }
  }
}
#endif
