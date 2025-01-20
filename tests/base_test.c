#include <trace_log.h>

int main() {
    // Enable time stamping and file location where stuff happened
	enable_timestamp();
    enable_file_location();
	
    // Log an information message
    TRACE_LOG(LOG_INFO, "This is an info message.\n");

    // Log a debug message
    TRACE_LOG(LOG_DEBUG, "This is a debug message.\n");

    // Log a warning message
    TRACE_LOG(LOG_WARN, "This is a warning message.\n");

    // Log an error message
    TRACE_LOG(LOG_ERROR, "This is an error message.\n");

    // Log a fatal error message (this will exit the program)
    TRACE_LOG(LOG_FATAL, "This is a fatal error message.\n");

    return 0;
}