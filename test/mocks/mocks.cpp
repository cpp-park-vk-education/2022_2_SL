#include <string>
#include <nlohmann/json.hpp>

#include "Message.hpp"

using json = nlohmann::json;

class MocksSerializer_json : public Serializer {
 public:
  MOCK_METHOD(json, set_body, (), (override));
};

TEST(Serializer, set_body) {
  MockIdleManager mock;
  EXPECT_CALL(mock, set_body()).Times(1);
  mock.set_body();
};
