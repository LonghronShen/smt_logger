#pragma once

#ifndef D4871A22_6A60_496E_8818_ECCDB6B539A5
#define D4871A22_6A60_496E_8818_ECCDB6B539A5

#include <string>

// The smt_logger library version in the form major * 10000 + minor * 100 + patch.
#define SMT_LOGGER_VERSION 10900

/**
 * @description: Log level enum definition
 */
enum class LogLevel { TRACE, DEBUG, INFO, WARN, ERR, CRITICAL, OFF };

struct LoggerConfig {

  /**
   * when print log into files,
   * logs will print into every module log files.
   */
  std::string module;

  /**
   * default log level is ERR, which means logs will
   * not print if its level is below ERR .
   */
  LogLevel logLevel;

  /**
   * as defualt, log print to console not file,
   * but you can change it to log into file with this
   */
  bool logFileInDebugMode;

  /**
   * default file sync frequency is 5s, you can change it before
   * printing any logs
   */
  int flushFrequency;
};

/**
 * setup logger with LoggerConfig before print any logs.
 */
extern void setupLogger(LoggerConfig config);

/**
 * @description: log as debug
 * @param {tag name}
 * @param {format with variable parameter}
 */
extern void logDebug(std::string tag, const char *format, ...);

/**
 * @description: log as info
 * @param {tag name}
 * @param {format with variable parameter}
 */
extern void logInfo(std::string tag, const char *format, ...);

/**
 * @description: log as warning
 * @param {tag name}
 * @param {format with variable parameter}
 */
extern void logWarn(std::string tag, const char *format, ...);

/**
 * @description: log as error
 * @param {tag name}
 * @param {format with variable parameter}
 */
extern void logError(std::string tag, const char *format, ...);

/**
 * @description: log as trace
 * @param {tag name}
 * @param {format with variable parameter}
 */
extern void logTrace(std::string tag, const char *format, ...);

/**
 * @description: log as critical
 * @param {tag name}
 * @param {format with variable parameter}
 */
extern void logCritical(std::string tag, const char *format, ...);
#endif /* D4871A22_6A60_496E_8818_ECCDB6B539A5 */
