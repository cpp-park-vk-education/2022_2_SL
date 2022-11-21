#include <string>

#include "Message.hpp"

using json = nlohmann::json;

class MocksSerializer_json : public Serializer {
 public:
  MOCK_METHOD(json, set_body, (), (override));
};

TEST(Serializer, set_body) {
  MockIdleManager mock;
  EXPECT_CALL(mock, takeSleepTime()).Times(1);
  mock.takeSleepTime();
}
