#ifndef TRACER_LOG_H
#define TRACE_LOG_H

#if defined(_MSC_VER)
    #define FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    #define FORCE_INLINE inline __attribute__((always_inline))
#else
    #define FORCE_INLINE inline
#endif

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILE_LOCATION_PRINT(file, line, func) printf("File Name: %s\nLine %d\nFunction %s\n", file, line, func)
#define FILE_LOCATION_PRINT_TOFILE(file_name, file, line, func ) fprintf(file_name, "File Name: %s\nLine %d\nFunction %s\n", file, line, func)


#ifdef __cplusplus
extern "C"
{ 
#endif

// enums



// terminal manipulation
typedef enum
{
    T_BG_WHITE = 47,
    T_BG_RED = 41,
    T_BG_GREEN = 42,
    T_BG_YELLOW = 43,
    T_BG_BLUE = 44,
    T_BG_MAGENTA = 45,
    T_BG_CYAN = 46,
    T_BG_RESET = 49, // Reset background to default color
} terminal_bg_color;

typedef enum
{
    T_WHITE = 37,
    T_RED = 31,
    T_GREEN = 32,
    T_YELLOW = 33,
    T_BLUE = 34,
    T_MAGENTA = 35,
    T_CYAN = 36,
    T_RESET = 0,
} terminal_color;


FORCE_INLINE void set_terminal_color(terminal_color color)
{
    printf("\033[%dm", color);
}

FORCE_INLINE void reset_terminal_color()
{
    printf("\033[0m");
}

FORCE_INLINE void set_terminal_bg_color(terminal_bg_color color)
{
    printf("\033[%dm", color);
}

// Function to reset only background color
FORCE_INLINE void reset_terminal_bg_color()
{
    printf("\033[49m");
}

// setting parameters for trace log

static int save_tracelog = 0;
static int file_location = 0;
static int timestamp = 0;

static FILE* file_redirect = NULL;

static const char* file_name = "traceback.txt";

static int text_colors[6] = {
	T_WHITE, 
	T_GREEN,
	T_CYAN,
	T_YELLOW,
	T_RED,
	T_WHITE,
};

static int bg_colors[6] = {
	T_RESET,
	T_RESET,
	T_RESET,
	T_RESET,
	T_RESET,
	T_BG_RED, 
};	

FORCE_INLINE void enable_save_tracelog(void) 
{
    save_tracelog = 1;
}

FORCE_INLINE void disable_save_tracelog(void) 
{
    save_tracelog = 0;
}


FORCE_INLINE void enable_file_location(void) 
{
    file_location = 1;
}

FORCE_INLINE void disable_file_location(void) 
{
    file_location = 0;
}

FORCE_INLINE void enable_timestamp(void) 
{
    timestamp = 1;
}

FORCE_INLINE void disable_timestamp(void) 
{
    timestamp = 0;
}


FORCE_INLINE void set_file_redirect(FILE* file) 
{
    file_redirect = file;

}

FORCE_INLINE void set_log_file_name(const char* name) 
{
    file_name = name;
}

// trace log data

typedef enum
{
	LOG_INFO,
	LOG_TRACE,
	LOG_DEBUG,
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL,
} warning;

#ifndef DISABLE_LOG
	#define TRACE_LOG(level, msg, ...) \
		__trace_log(level, msg, file_redirect, __FILE__, __LINE__, __func__, __VA_ARGS__)
		
#else
	#define TRACE_LOG(level, msg, ...) (void*)
#endif

#ifndef DISABLE_ASSERT
	#define ASSERT(c, msg)\
		disable_save_tracelog()\
		do{\
			if(!c){\
				__trace_log(LOG_FATAL, msg, file_redirect, __FILE__, __LINE__, __func__, __VA_ARGS__); \
			}\
		} while(0)\
#else
	#define ASSERT(c, msg) (void*)
#endif

static void __trace_log(warning level, const char* msg, FILE* redirect, const char* file_name, int line_number, const char* func_name, ...)
{
	va_list args;
	va_start(args, msg);
	
	if(redirect) save_tracelog = 1;
	
	if (save_tracelog)
	{
		FILE* file_ptr = (redirect == NULL) ? redirect : fopen(file_name, "a");
		
		if (file_location)
			FILE_LOCATION_PRINT_TOFILE(file_ptr, file_name, line_number, func_name);
		
		if (timestamp)
		{
			time_t t = time(NULL);
			struct tm local = *localtime(&t);
			
			fprintf(file_ptr, "%d %d %d %d %d %d ", local.tm_year, local.tm_mon, local.tm_mday, local.tm_hour, local.tm_min, local.tm_sec);
		}
		
		switch (level)
		{
			case LOG_FATAL:
				fprintf(file_ptr, "FATAL: ");
				break;
			case LOG_ERROR:
				fprintf(file_ptr, "ERROR: ");
				break;
			case LOG_WARN:
				fprintf(file_ptr, "WARNING: ");
				break;
			case LOG_DEBUG:
				fprintf(file_ptr, "Debug: ");
				break;
			case LOG_TRACE:
				fprintf(file_ptr, "Trace: ");
				break;
			case LOG_INFO:
				fprintf(file_ptr, "Info: ");
				break;
			default:
				fprintf(file_ptr, "Info: ");
		}
		vfprintf(file_ptr, msg, args);
		va_end(args);
		if (level == LOG_FATAL) exit(1);
		return;
	}
	
	if (timestamp)
	{
		time_t t = time(NULL);
		struct tm local = *localtime(&t);
		
		printf("%04d-%02d-%02d %02d-%02d-%02d ", 1900 + local.tm_year, local.tm_mon, local.tm_mday, local.tm_hour, local.tm_min, local.tm_sec);
	}
	
	if (file_location || level == LOG_FATAL || level == LOG_ERROR)
	{
		set_terminal_color(T_YELLOW);
		FILE_LOCATION_PRINT(file_name, line_number, func_name);
	}
	
	set_terminal_color(text_colors[level]);
	set_terminal_bg_color(bg_colors[level]);
	switch (level)
	{
		case LOG_FATAL:

			printf("FATAL: ");
			break;
		case LOG_ERROR:
			set_terminal_color(T_RED);
			printf("ERROR: ");
			break;
	    case LOG_WARN:
			set_terminal_color(T_YELLOW);
			printf("WARNING: ");
			break;
	    case LOG_DEBUG:
			set_terminal_color(T_CYAN);
			printf("Debug: ");
			break;
	    case LOG_TRACE:
			set_terminal_color(T_GREEN);
			printf("Trace: ");
			break;
	    case LOG_INFO:
			printf("Info: ");
			break;
		default:
			printf("Unknown Level...: ");
	}
	
	reset_terminal_color();
	reset_terminal_bg_color();
	
	vprintf(msg, args);
	va_end(args);
	
	if (level == LOG_FATAL) exit(1);
}

#ifdef __cplusplus // extern c
} 
#endif

#endif
