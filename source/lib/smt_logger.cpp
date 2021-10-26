#include <cstdarg>
#include <string>

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/daily_file_sink.h>

#include <smt-logger/smt_logger.h>

#ifdef __GNUC__
#define vsprintf_s vsnprintf
#endif

#if defined(WIN32)
#include <io.h>
#endif

constexpr auto LOG_PATTEN = "[%Y-%m-%d %H:%M:%S.%e][%^%L%$][thread %t]: %v";

#define BUFFER_MAX_SIZE 4096
static spdlog::level::level_enum spdlogLv = spdlog::level::level_enum::info;
std::string output_dir = "./logs/";

std::shared_ptr<spdlog::logger> getLogger(const std::string &tag);

bool hasPermission(const std::string &dir);

void logDebug(const std::string &tag, const char *format, ...) {
  char buffer[BUFFER_MAX_SIZE];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, BUFFER_MAX_SIZE, format, args);
  va_end(args);

  // print log
  auto logger = getLogger(tag);
  if (logger != nullptr) {
    logger->debug(buffer);
    logger->flush();
  }
}

void logInfo(const std::string &tag, const char *format, ...) {
  char buffer[BUFFER_MAX_SIZE];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, BUFFER_MAX_SIZE, format, args);
  va_end(args);

  // print log
  auto logger = getLogger(tag);
  if (logger != nullptr) {
    logger->info(buffer);
    logger->flush();
  }
}

void logWarn(const std::string &tag, const char *format, ...) {
  char buffer[BUFFER_MAX_SIZE];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, BUFFER_MAX_SIZE, format, args);
  va_end(args);

  // print log
  auto logger = getLogger(tag);
  if (logger != nullptr) {
    logger->warn(buffer);
    logger->flush();
  }
}

void logError(const std::string &tag, const char *format, ...) {
  char buffer[BUFFER_MAX_SIZE];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, BUFFER_MAX_SIZE, format, args);
  va_end(args);

  // print log
  auto logger = getLogger(tag);
  if (logger != nullptr) {
    logger->error(buffer);
    logger->flush();
  }
}

void logTrace(const std::string &tag, const char *format, ...) {
  char buffer[BUFFER_MAX_SIZE];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, BUFFER_MAX_SIZE, format, args);
  va_end(args);

  // print log
  auto logger = getLogger(tag);
  if (logger != nullptr) {
    logger->trace(buffer);
    logger->flush();
  }
}

void logCritical(const std::string &tag, const char *format, ...) {
  char buffer[BUFFER_MAX_SIZE];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, BUFFER_MAX_SIZE, format, args);
  va_end(args);

  // print log
  auto logger = getLogger(tag);
  if (logger != nullptr) {
    logger->critical(buffer);
    logger->flush();
  }
}

std::shared_ptr<spdlog::logger> getLogger(const std::string &tag) {
  std::string temp = tag;
  size_t index = temp.find_last_of('.');
  if (index != -1) {
    temp = "Other";
  }
  auto logger = spdlog::get(temp);
  if (logger == nullptr) {
    if (!hasPermission(output_dir)) {
      return nullptr;
    }

    auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(
        output_dir + temp, 23, 59);
    daily_sink->set_pattern(LOG_PATTEN);
    logger = std::make_shared<spdlog::logger>(temp, daily_sink);
    logger->set_level(spdlogLv);
    spdlog::register_logger(logger);
  }

  return logger;
}

void setupLogger(const LoggerConfig &config) {
  switch (config.logLevel) {
  case LogLevel::TRACE:
    spdlogLv = spdlog::level::level_enum::trace;
    break;
  case LogLevel::DEBUG:
    spdlogLv = spdlog::level::level_enum::debug;
    break;
  case LogLevel::INFO:
    spdlogLv = spdlog::level::level_enum::info;
    break;
  case LogLevel::WARN:
    spdlogLv = spdlog::level::level_enum::warn;
    break;
  case LogLevel::ERR:
    spdlogLv = spdlog::level::level_enum::err;
    break;
  case LogLevel::CRITICAL:
    spdlogLv = spdlog::level::level_enum::critical;
    break;
  case LogLevel::OFF:
    spdlogLv = spdlog::level::level_enum::off;
    break;
  default:
    break;
  }
}

void setOutputDir(std::string dir) { output_dir = dir; }

bool hasPermission(const std::string &dir) {
#ifdef WIN32
  return _access(dir.c_str(), 6) == 0;
#elif defined __linux__
  return access(dir.c_str(), 6) == F_OK;
#endif
}
