#include <string>

#include "Message.hpp"

using nlohmann::json;

class MocksSerializer_json : public Serializer {
 public:
  MOCK_METHOD(json, set_body, (), (override));
};

TEST(Serializer, set_body) {
  MockIdleManager mock;
  EXPECT_CALL(mock, takeSleepTime()).Times(1);
  mock.takeSleepTime();
}

TEST(IdleManager, process_idling) {
  MockIdleManager mock;
  EXPECT_CALL(mock, process_idling()).Times(1);
  mock.process_idling();
}

TEST(Config, get_value) {
  MockConfig mock;
  EXPECT_CALL(mock, get_value<std::string>("service", "name")).Times(1);
  mock.get_value<std::string>("service", "name");
}