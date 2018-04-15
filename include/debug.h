#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG 1
#ifdef DEBUG

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define log_error_exit(fmt, ...) {\
            fprintf(stderr, RED "ERROR" RESET " ==> "YEL"%s:%d"RESET" "CYN"%s()"RESET" ==> " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__);\
            exit(-1);\
        }

#define log_error(fmt, ...) {\
            fprintf(stderr, RED "ERROR" RESET " ==> "YEL"%s:%d"RESET" "CYN"%s()"RESET" ==> " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__);\
        }

#define log_debug(fmt, ...) { \
            fprintf(stderr, MAG "DEBUG" RESET " ==> "YEL"%s:%d"RESET" "CYN"%s()"RESET" ==> " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__);\
        }

#define log(fmt, ...) { \
            fprintf(stdout, "" GRN fmt RESET, __VA_ARGS__);\
        }

#else
#define log_error_exit(str, ...)
#define log_debug(str, ...)
#define log(str, ...)
#endif

#endif