
/**
    \copyright MIT License Copyright (c) 2021, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 12 April 2021
    \file colorfulterm.h

    colorfulterm.h is ...
*/

#ifndef EXOTIC_CLINE_COLORFUL_TERM_H
#define EXOTIC_CLINE_COLORFUL_TERM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <exotic/xtd/xcommon.h>

#ifdef _WIN32
#include <windows.h>
#include <stdarg.h>
#endif

/**
    The font effect macros used by cline.
    The values are appened to '\x1B[' and prepended with 'm' 
    for the combination of multiple effects they are seperated 
    by ';' 

    \see https://stackoverflow.com/a/33206814
    \see http://www.ecma-international.org/publications/standards/Ecma-048.htm
*/
#define CLINE_FE_RESET                 0
#define CLINE_FE_BOLD                  1
#define CLINE_FE_FAINT                 2
#define CLINE_FE_ITALIC                3
#define CLINE_FE_UNDERLINE             4

#define CLINE_RESET_TERMINAL   "\x1B[0m"     /**< reset the terminal color   */
#define CLINE_BOLD             "\x1B[1m"     /**< bold text                  */
#define CLINE_FG_BLACK         "\x1B[30m"    /**< gray terminal FG color     */
#define CLINE_FG_RED           "\x1B[31m"    /**< red terminal FG color      */
#define CLINE_FG_GREEN         "\x1B[32m"    /**< green FG color             */
#define CLINE_FG_YELLOW        "\x1B[33m"    /**< yellow terminal FG color   */
#define CLINE_FG_BLUE          "\x1B[34m"    /**< blue terminal FG color     */
#define CLINE_FG_MAGENTA       "\x1B[35m"    /**< magenta terminal FG color  */
#define CLINE_FG_CYAN          "\x1B[36m"    /**< cyan terminal FG color     */
#define CLINE_FG_WHITE         "\x1B[37m"    /**< white terminal FG color    */
#define CLINE_FG_GRAY          "\x1B[90m"    /**< gray terminal FG color     */
#define CLINE_BG_BLACK         "\x1B[40m"    /**< black terminal BG color    */
#define CLINE_BG_RED           "\x1B[41m"    /**< red terminal BG color      */
#define CLINE_BG_GREEN         "\x1B[42m"    /**< green terminal BG color    */
#define CLINE_BG_YELLOW        "\x1B[43m"    /**< yellow terminal BG color   */
#define CLINE_BG_BLUE          "\x1B[44m"    /**< blue terminal BG color     */
#define CLINE_BG_MAGENTA       "\x1B[45m"    /**< magenta terminal BG color  */
#define CLINE_BG_CYAN          "\x1B[46m"    /**< cyan terminal BG color     */
#define CLINE_BG_GRAY          "\x1B[100m"   /**< gray terminal BG color     */
#define CLINE_BG_WHITE         "\x1B[47m"    /**< gray terminal BG color     */

#ifdef _WIN32
/**

*/
#define CLINE_WIN32_RESET_TERMINAL   15                                                        /**< reset the terminal color //Nothing */
#define CLINE_WIN32_BOLD             15                                                        /**< bold text                //Nothing */
#define CLINE_WIN32_FG_BLACK         8                                                         /**< gray terminal FG color             */
#define CLINE_WIN32_FG_RED           4                                                         /**< red terminal FG color              */
#define CLINE_WIN32_FG_GREEN         2                                                         /**< green FG color                     */
#define CLINE_WIN32_FG_YELLOW        6                                                         /**< yellow terminal FG color           */
#define CLINE_WIN32_FG_BLUE          3                                                         /**< blue terminal FG color             */
#define CLINE_WIN32_FG_MAGENTA       5                                                         /**< magenta terminal FG color          */
#define CLINE_WIN32_FG_CYAN          11                                                        /**< cyan terminal FG color             */
#define CLINE_WIN32_FG_WHITE         15                                                        /**< white terminal FG color            */
#define CLINE_WIN32_FG_GRAY          8                                                         /**< gray terminal FG color             */
#define CLINE_WIN32_BG_BLACK         0                                                         /**< black terminal BG color            */
#define CLINE_WIN32_BG_RED           64                                                        /**< red terminal BG color              */
#define CLINE_WIN32_BG_GREEN         39                                                        /**< green terminal BG color            */
#define CLINE_WIN32_BG_YELLOW        96                                                        /**< yellow terminal BG color           */
#define CLINE_WIN32_BG_BLUE          48                                                        /**< blue terminal BG color             */
#define CLINE_WIN32_BG_MAGENTA       87                                                        /**< magenta terminal BG color          */
#define CLINE_WIN32_BG_CYAN          176                                                       /**< cyan terminal BG color             */
#define CLINE_WIN32_BG_GRAY          0                                                         /**< gray terminal BG color             */
#define CLINE_WIN32_BG_WHITE         10                                                        /**< gray terminal BG color             */

#ifndef CLINE_WIN32_STD_STREAM_HANDLE
/**

*/
#define CLINE_WIN32_STD_STREAM_HANDLE STD_OUTPUT_HANDLE
#endif
#endif

/* TODO */
/*#define CLINE_DONT_RESET_TERMINAL_INDIVIDUALLY*/

void cline_platform_printnl_if()
{
    #ifndef _WIN32
        printf("\n");
    #endif
}

void cline_die(const char *message)
{
    printf(message);
    cline_platform_printnl_if();
    exit(EXIT_FAILURE);
}

#ifdef _WIN32
/* use equal function from xtd */
static bool cline_string_equals(char* arg, char* arg1) {
    unsigned i = 0;
    if (arg == NULL || arg1 == NULL) {
        return FALSE;
    }
    while (1) {
        if (arg[i] == '\0' && arg1[i] == '\0') {
            break;
        }
        if (arg[i] != arg1[i]) {
            return FALSE;
        }
        ++i;
    }
    return TRUE;
}

void cline_win32_print_colored_str_se(HANDLE console, FILE *stream, unsigned int start_color, unsigned int end_color, const char *text)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (GetConsoleScreenBufferInfo(console, &info)) {
        if (start_color == CLINE_WIN32_RESET_TERMINAL) {
            start_color = info.wAttributes;
        } else if (end_color == CLINE_WIN32_RESET_TERMINAL) {
            end_color = info.wAttributes;
        }
    }
    SetConsoleTextAttribute(console, start_color);
    fprintf(stream, "%s", text);
    SetConsoleTextAttribute(console, end_color);
}

void cline_win32_print_colored_str(HANDLE console, FILE *stream, unsigned int color, const char *text)
{
    unsigned int default_text_attr;
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (GetConsoleScreenBufferInfo(console, &info)) {
        default_text_attr = info.wAttributes;
    }
    cline_win32_print_colored_str_se(console, stream, color, default_text_attr, text);
}

/* test edge case */
void cline_fprintf_win32_print_colored_str(HANDLE console, FILE *stream, const char *text)
{
    unsigned int start_color = CLINE_WIN32_RESET_TERMINAL, index = 0, color_byte_index = 0, color_byte_size = 0;
    unsigned int end_color = CLINE_WIN32_RESET_TERMINAL;
    char *color_bytes;
    char *actual_text = (char *) malloc(strlen(text));
    if (!actual_text) {
        cline_die("Unable to allocate memory in cline_fprintf_win32_print_colored_str, use fprintf instead");
    }
    cline_fprintf_win32_parse_color_bytes:
        color_byte_index = 0;
        color_bytes = (char *) malloc(sizeof(char) * 8);
        if (!color_bytes) {
            cline_die("Unable to allocate memory in cline_fprintf_win32_print_colored_str, use fprintf instead");
        }
        while (text[index] != '\0' && text[index] != 'm') {
            color_bytes[color_byte_index++] = text[index];
            index++;
        }
    if (start_color == CLINE_WIN32_RESET_TERMINAL && (color_bytes[0] != '\x1B' || color_bytes[1] != '[' || text[index] != 'm')) {
        cline_win32_print_colored_str(console, stream, start_color, text);
        goto cline_fprintf_win32_cleanup;
    }
    color_bytes[color_byte_index] = 'm';
    color_bytes[color_byte_index+1] = '\0';
    if (cline_string_equals(color_bytes, CLINE_FG_RED) == TRUE) {
        if (index <= color_byte_index) {
            start_color = CLINE_WIN32_FG_RED;
        } else {
            end_color = CLINE_WIN32_FG_RED;
        }
    } else if (cline_string_equals(color_bytes, CLINE_FG_GREEN) == TRUE) {
        if (index <= color_byte_index) {
            start_color = CLINE_WIN32_FG_GREEN;
        } else {
            end_color = CLINE_WIN32_FG_GREEN;
        }
    } else if (cline_string_equals(color_bytes, CLINE_FG_BLUE) == TRUE) {
        if (index <= color_byte_index) {
            start_color = CLINE_WIN32_FG_BLUE;
        } else {
            end_color = CLINE_WIN32_FG_BLUE;
        }
    } else if (cline_string_equals(color_bytes, CLINE_FG_YELLOW) == TRUE) {
        if (index <= color_byte_index) {
            start_color = CLINE_WIN32_FG_YELLOW;
        } else {
            end_color = CLINE_WIN32_FG_YELLOW;
        }
    } else if (cline_string_equals(color_bytes, CLINE_RESET_TERMINAL) == TRUE) {
        if (index <= color_byte_size) {
            start_color = CLINE_WIN32_RESET_TERMINAL;
        } else {
            end_color = CLINE_WIN32_RESET_TERMINAL;
        }
    }
    /* if support variadic do SetConsoleTextAttribute here */
    index++;
    color_byte_size = index;
    while (text[index] != '\0') {
        if (text[index] == '\x1B') {
            actual_text[index-color_byte_size] = '\0';
            free(color_bytes);
            goto cline_fprintf_win32_parse_color_bytes;
        }
        actual_text[index-color_byte_size] = text[index];
        index++;
    }
    cline_win32_print_colored_str_se(console, stream, start_color, end_color, actual_text);

    cline_fprintf_win32_cleanup:
        free(color_bytes);
        free(actual_text);
        return;

    cline_fprintf_win32_join_color_bytes:
        printf("To Join\n");
}

void cline_fprintf_win32(HANDLE console, FILE *stream, const char *format, va_list ap)
{
    const char *p;
    while (*format != '\0') {
        if(*format != '%') {
            fprintf(stream, "%c", *format);
            format++;
            continue;
        }
        format++;
        if(*format == '\0') {
            break;
        }
        switch (*format) {
            case 's':
                cline_fprintf_win32_print_colored_str(console, stream, va_arg(ap, const char *));
                break;
        }
        format++;
    }
}

void cline_fprintf(FILE *stream, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    cline_fprintf_win32(GetStdHandle(CLINE_WIN32_STD_STREAM_HANDLE), stream, format, ap);
    va_end(ap);
}
#else
#define cline_fprintf fprintf
#endif

/**
 TODO use reference counting to free mallocated str at end of program on call cline_terminal_cleanup
*/
const char *cline_color_str(const char *text, ...)
{
    va_list ap;
    va_start(ap, text);

    va_end(ap);
    /*size_t color_length = strlen(color), text_length = strlen(text), reset_length = strlen(CLINE_RESET_TERMINAL);
    size_t index, concatenated_length = (color_length + text_length + reset_length);
    char *concatenated = (char *) malloc(concatenated_length);

    /*index = color_length;
    while (index > 0) {
        concatenated[index-1] = color[index-1];
        index--;
    }
    index = 0;
    while (index < text_length) {
        concatenated[color_length+index] = text[index];
        index++;
    }
    index = 0;
    while (index < reset_length) {
        concatenated[color_length+text_length+index] = CLINE_RESET_TERMINAL[index];
        index++;
    }
    concatenated[concatenated_length] = '\0';
    return concatenated;*/
    return "";
}

#define cline_color_printff(...)

#define cline_color_printfb(...)

#define cline_color_printffb(...)

#define CLINE_COLORSTR cline_color_str

#ifdef __cplusplus
}
#endif

#endif