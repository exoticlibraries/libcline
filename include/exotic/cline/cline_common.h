
/*!
    \copyright MIT License Copyright (c) 2021, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 19 February 2021
    \file cline_common.h

    cline_common.h is ...
*/

#ifndef EXOTIC_CLINE_COMMON_H
#define EXOTIC_CLINE_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

/*! 
    parameter padding for variadic.
    this should be temporal
*/
#define CLINE_FE_PADDING_INTERNAL    -100

/*! 
    if this is part of the options all other 
    options sent to the function will be ignored.
*/
#define CLINE_OPTION_NONE    -101

/*! 
    The bell char that do ding in the terminal
*/
#define CLINE_BELL    '\a'

/*!

*/
#define NARGS_SEQ(_1,_2,_3,_4,_5,_6,_7,_8,_9,N,...) N

/*!

*/
#define NARGS(...) NARGS_SEQ(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1)

/*!
   The max number of font effect options the \ref cline_fe_str accepts 
*/
#define CLINE_MAX_OPTIONS_COUNT 20

/*!
   30 should be big enough memory size to add to the text for the 
   font effects options.
*/
#define CLINE_MAX_OPTIONS_MEM_LENGTH 30

/*!

*/
void cline_platform_printnl_if()
{
    #ifndef _WIN32
        printf("\n");
    #endif
}

#define CLINE_INTERNAL_DIE(file_name, line_number, ...) {\
    printf("libcline FATAL_ERROR -> %s:%d ", file_name, line_number);\
    printf(__VA_ARGS__); \
    cline_platform_printnl_if(); \
    exit(EXIT_FAILURE);\
}

#ifdef _WIN32
/*!

*/
static unsigned already_change_mode = 0;

/*!

*/
#ifndef CLINE_WIN32_STD_STREAM_HANDLE
/*!

*/
#define CLINE_WIN32_STD_STREAM_HANDLE STD_OUTPUT_HANDLE
#endif
#endif

#ifndef snprintf
#define snprintf(buffer, size, ...) sprintf(buffer, __VA_ARGS__)
#endif

/*  TODO use reference counting to free mallocated str at end of program on call cline_terminal_cleanup
 use vector to collect them and free*/

/*!

*/
char *cline_ansi_encoder(const char *file_name, const int line_number, const char ansi_code_terminator, const int argscount, ...)
{
    va_list ap;
    const char *p;
    int argsindex = 0;
    if (argscount <= 0 && ansi_code_terminator == '\0') {
        return "";
    }
    if (argscount > CLINE_MAX_OPTIONS_COUNT) {
        CLINE_INTERNAL_DIE(file_name, line_number, "the font effect options cannot be more than %d", CLINE_MAX_OPTIONS_COUNT);
    }
    size_t index = 0;
    int concatenated_length = CLINE_MAX_OPTIONS_MEM_LENGTH;
    char *concatenated = (char *) malloc(concatenated_length+1);

#ifdef _WIN32
    if (!already_change_mode) {
        /*DWORD dw_mode = 0;
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleMode(handle, &dw_mode)) {
            dw_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            if (!SetConsoleMode(handle, dw_mode));
        }*/
        already_change_mode = 1;
    }
#endif
    concatenated[index++] = '\x1B';
    concatenated[index++] = '[';
    va_start(ap, argscount);
    while (argsindex < argscount) {
        unsigned int font_effect = va_arg(ap, unsigned int);
        if (argsindex == 1 && font_effect == CLINE_OPTION_NONE) {
            free(concatenated);
            return "";
        }
        if (font_effect == CLINE_FE_PADDING_INTERNAL) {
            argsindex++;
            continue;
        }
        concatenated[index] = '\0';
        if (argsindex > 1) {
            snprintf(concatenated, concatenated_length+1, "%s;%d", concatenated, font_effect);
            index++;
        } else {
            snprintf(concatenated, concatenated_length+1, "%s%d", concatenated, font_effect);
        }
        if (font_effect < 10) {
            index += 1;
        } else if (font_effect < 100) {
            index += 2;
        } else {
            index += 3;
        }
        argsindex++;
    }
    va_end(ap);
    concatenated[index++] = ansi_code_terminator;
    concatenated[index] = '\0';
    return concatenated;
}

/*!
   
*/
#define CLINE_ANSI_ENCODER(ansi_code_terminator, ...) cline_ansi_encoder(__FILE__, __LINE__, ansi_code_terminator, NARGS(CLINE_FE_PADDING_INTERNAL, __VA_ARGS__), CLINE_FE_PADDING_INTERNAL, __VA_ARGS__)

/*!
   
*/
#define CLINE_ANSI_ENCODER_ESCAPE_ONLY(ansi_code_terminator) cline_ansi_encoder(__FILE__, __LINE__, ansi_code_terminator, 0)

#ifdef __cplusplus
}
#endif

#endif