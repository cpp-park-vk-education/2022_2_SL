#include "logacceptor.h"
#include "logcollector.h"
#include "logwriter.h"
#include "serializer.h"
#include "logsender.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockLogAcceptor : public LogAcceptor {
 public:
  MOCK_METHOD(void, set_serializer, (Serializer serializer), (override));
  MOCK_METHOD(void, set_socket, (socket socket), (override));
};

class MockLogCollector : public LogCollector {
 public:
  MOCK_METHOD(void, set_serializer, (Serializer serializer), (override));
  MOCK_METHOD(void, set_sensors, (vector<Sensor> sensors), (override));
};

class MockLogWriter : public LogWriter {
 public:
  MOCK_METHOD(void, set_serializer, (Serializer serializer), (override));
};

class MockLogSender : public LogSender {
 public:
  MOCK_METHOD(void, set_serializer, (Serializer serializer), (override));
  MOCK_METHOD(void, set_socket, (socket socket), (override));
};

TEST(LogAcceptor, set_serializer) {
  MockLogAcceptor mock;
  Serializer serializer;
  EXPECT_CALL(mock, set_serializer(serializer));
  mock.set_serializer(serializer);
}

TEST(LogAcceptor, set_socket) {
  MockLogAcceptor mock;
  socket socket;
  EXPECT_CALL(mock, set_socket(socket));
  mock.set_socket(socket);
}

TEST(LogCollector, set_serializer) {
  MockLogCollector mock;
  Serializer serializer;
  EXPECT_CALL(mock, set_serializer(serializer));
  mock.set_serializer(serializer);
}

TEST(LogCollector, set_sensors) {
  MockLogCollector mock;
  vector<Sensor> sensors;
  EXPECT_CALL(mock, set_sensors(sensors));
  mock.set_sensors(sensors);
}

TEST(LogWriter, set_serializer) {
  MockLogWriter mock;
  Serializer serializer;
  EXPECT_CALL(mock, set_serializer(serializer));
  mock.set_serializer(serializer);
}

TEST(LogSender, set_serializer) {
  MockLogSender mock;
  Serializer serializer;
  EXPECT_CALL(mock, set_serializer(serializer));
  mock.set_serializer(serializer);
}

