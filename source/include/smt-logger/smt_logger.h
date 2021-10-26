#pragma once

#include <string>

#define LOGINFO(fmt, ...) logInfo(__FILE__, fmt, ##__VA_ARGS__)
#define LOGDEBUG(fmt, ...) logDebug(__FILE__, fmt, ##__VA_ARGS__)
#define LOGWARN(fmt, ...) logWarn(__FILE__, fmt, ##__VA_ARGS__)
#define LOGTRACE(fmt, ...) logTrace(__FILE__, fmt, ##__VA_ARGS__)
#define LOGERROR(fmt, ...)                                                     \
  logError(__FILE__,                                                           \
           (std::string("[function:%s,line:%d]-") + std::string(fmt)).c_str(), \
           __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGCRITICAL(fmt, ...)                                                  \
  logCritical(                                                                 \
      __FILE__,                                                                \
      (std::string("[function:%s,line:%d]-") + std::string(fmt)).c_str(),      \
      __FUNCTION__, __LINE__, ##__VA_ARGS__)

/**
 * @description: Log level enum definition
 */
enum class LogLevel { TRACE, DEBUG, INFO, WARN, ERR, CRITICAL, OFF };

typedef struct LoggerConfig {

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
} LogConfig;

/**
 * setup logger with LoggerConfig before print any logs.
 */
extern void setupLogger(const LoggerConfig &config);

/**
 * @description: log as debug
 * @param {tag name}
 * @param {format with variable parameter}
 */
extern void logDebug(const std::string &tag, const char *format, ...);

/**
 * @description: log as info
 * @param {tag name}
 * @param {format with variable parameter}
 */
extern void logInfo(const std::string &tag, const char *format, ...);

/**
 * @description: log as warning
 * @param {tag name}
 * @param {format with variable parameter}
 */
extern void logWarn(const std::string &tag, const char *format, ...);

/**
 * @description: log as error
 * @param {tag name}
 * @param {format with variable parameter}
 */
extern void logError(const std::string &tag, const char *format, ...);

/**
 * @description: log as trace
 * @param {tag name}
 * @param {format with variable parameter}
 */
extern void logTrace(const std::string &tag, const char *format, ...);

/**
 * @description: log as critical
 * @param {tag name}
 * @param {format with variable parameter}
 */
extern void logCritical(const std::string &tag, const char *format, ...);

/**
 * @description: redirect the output dir
 * @param {dir target}
 */
extern void setOutputDir(std::string dir);
