#include <string>
#include <nlohmann/json.hpp>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>

#include "message.h"
#include "serialize.h"

class MocksSerializer_json : public ISerializer<json>{
  
 public:
  MOCK_METHOD1(serialize, json(int));
};

TEST(Serializer, get_body) {
  MocksSerializer_json mock_serialize;
  EXPECT_CALL(mock_serialize, serialize(1)).Times(1);
  mock_serialize.serialize(1);
};

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}