#include "trace_log.h"

int main() {
    enable_timestamp();
    enable_file_location();
    enable_save_tracelog();  // Redirects log output to a predefined file (traceback.txt)

    // Log an information message
    TRACE_LOG(LOG_INFO, "This is an info message.\n");

    // Log a debug message
    TRACE_LOG(LOG_DEBUG, "This is a debug message.\n");

    // Log a warning message
    TRACE_LOG(LOG_WARN, "This is a warning message.\n");

    // Log an error message
    TRACE_LOG(LOG_ERROR, "This is an error message.\n");

    // Open a custom log file
    FILE* custom_log = fopen("custom_log.txt", "a");
    if (custom_log != NULL) {
        // Redirect log output to custom_log.txt file
        set_file_redirect(custom_log);

        // Log messages into the custom file
        TRACE_LOG(LOG_INFO, "This info message is written to custom_log.txt.\n");
        TRACE_LOG(LOG_DEBUG, "This debug message is written to custom_log.txt.\n");
        TRACE_LOG(LOG_WARN, "This warning message is written to custom_log.txt.\n");

        // Close the custom log file
        fclose(custom_log);
    } else {
        TRACE_LOG(LOG_ERROR, "Failed to open custom log file.\n");
    }

    // Log a fatal error message (this will exit the program)
    TRACE_LOG(LOG_FATAL, "This is a fatal error message.\n");

    return 0;
}