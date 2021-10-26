#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include <smt-logger/smt_logger.h>

class LoggerTest : public testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}

  const char *MODULE_A = "moduleA";
  const char *MODULE_B = "moduleB";
  const char *MODULE_C = "moduleC";
};

TEST_F(LoggerTest, LogOff) {
  LogConfig config{.logLevel = LogLevel::OFF, .logFileInDebugMode = false};
  setupLogger(config);

  // no log will be printed or written
  logInfo(MODULE_A, "Camera LogInfo");

  std::cout << "-----------------------------" << std::endl;
}

TEST_F(LoggerTest, LogTrace) {
  LogConfig config{.logLevel = LogLevel::OFF, .logFileInDebugMode = true};
  setupLogger(config);

  // only logs under debug level can be printed at console
  logTrace(MODULE_A, "trace msg...");
  logDebug(MODULE_B, "debug msg...");
  logInfo(MODULE_C, "info msg...");
  logWarn(MODULE_A, "info msg...");
  logError(MODULE_B, "error msg...");
  logCritical(MODULE_C, "critical msg...");
}