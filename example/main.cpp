#include <smt_logger.h>
#include <thread>
#include <iostream>

const char *MODULE_A = "moduleA";
const char *MODULE_B = "moduleB";
const char *MODULE_C = "moduleC";


int main(int argc, char **argv) {
    LogConfig config;
    config.logLevel = LogLevel::DEBUG;
    setupLogger(config);

    // main thread
    logInfo(MODULE_A, "info in main thread");
    logDebug(MODULE_B, "logDebug in main thread");
    logTrace(MODULE_C, "trace in main thread");

    // children thread
    std::thread t1([]() -> void {
        logInfo(MODULE_A, "info in children thread1");
        logDebug(MODULE_B, "logDebug in children thread1");
        logTrace(MODULE_C, "trace in children thread1");

    });
    t1.detach();

    std::thread t2([]() -> void {
        logInfo(MODULE_A, "info in children thread2");
        logDebug(MODULE_B, "logDebug in children thread2");
        logTrace(MODULE_C, "trace in children thread2");

    });
    t2.join();

}