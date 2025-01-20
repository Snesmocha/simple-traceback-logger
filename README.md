# File Logger

This is a simple single header file logger written in C99 that provides functionality to log messages with various severity levels such as INFO, DEBUG, WARNING, ERROR, and FATAL. It supports writing logs to both the console and a log file, with options to include timestamps and file location information in the log messages.

It'll probably work in most compilers? I haven't tested but as long as the terminal supports posix escape codes, it'll probably be fine. I ain't supporting windows built in terminal escape codes... I would be screaming if I did 

## Features

- Logs messages with different severity levels: 
  - `INFO`, `TRACE`, `DEBUG`, `WARNING`, `ERROR`, `FATAL`.
- Supports output to the console with color-coded messages.
- Option to log messages to a file (`traceback.txt`).
- Option to redirect messages however needed.
- Includes file location (file, line number, function name) for easy debugging.
- Timestamp for each log message.

## Installation

1. Clone this repository to your local machine:

    ```bash
    git clone https://github.com/snesmocha/file-logger.git
    cd file-logger
    ```

2. Drag the header into your folder and include it with your build system.

## Usage

### Basic Logging Into Console Example

```c
#include "trace_log.h"

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
```

### Basic Logging Into Predefined File Example

```c
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

	// Disable File Logging
	disable_save_tracelog();

    // Log a fatal error message (this will exit the program)
    TRACE_LOG(LOG_FATAL, "This is a fatal error message.\n");

    return 0;
}
```

### Logging Into A Custom File Redirect

```c
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
```
