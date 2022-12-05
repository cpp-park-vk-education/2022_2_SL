#include <string>
#include <nlohmann/json.hpp>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>

#include "serialize.h"

class MocksMessage : public AbstractMessage {
  
 public:
  MOCK_METHOD(bool, set_body, (json element), (override));
  MOCK_METHOD(json, get_body, (), (override));
};

TEST(Serializer, get_body) {
  MocksMessage mock_message;
  Serializer_json myapp_mock;
  EXPECT_CALL(mock_message, get_body()).Times(1);
  myapp_mock.serialize(mock_message);
};

TEST(Deserializer, set_body) {
  MocksMessage mock_message;
  Serializer_json myapp_mock;
  json element;
  EXPECT_CALL(mock_message, set_body(element)).Times(1);
  myapp_mock.deserialize(element,mock_message);
};

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}