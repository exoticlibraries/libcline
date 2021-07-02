
/*!
    \copyright MIT License Copyright (c) 2021, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 12 February 2021
    \file font_effect.h

    font_effect.h is ...
*/

#ifndef EXOTIC_CLINE_FONT_EFFECT_H
#define EXOTIC_CLINE_FONT_EFFECT_H

#ifdef __cplusplus
extern "C" {
#endif

/*!

*/
#include "cline_common.h"

/*!
    The font effect macros used by cline.
    The values are appened to '\x1B[' and 'm' is appended at the end 
    for the combination of multiple effects they are seperated 
    by ';' 

    \see https://en.wikipedia.org/wiki/ANSI_escape_code
    \see http://www.ecma-international.org/publications/standards/Ecma-048.htm
*/
#define CLINE_FE_RESET                        0     /*!< reset the terminal color   */
#define CLINE_FE_BOLD                         1
#define CLINE_FE_FAINT                        2
#define CLINE_FE_ITALIC                       3
#define CLINE_FE_UNDERLINE                    4
#define CLINE_FE_SLOW_BLINK                   5
#define CLINE_FE_RAPID_BLINK                  6
#define CLINE_FE_REVERSE_VIDEO                7
#define CLINE_FE_CONCEAL                      8
#define CLINE_FE_CROSSED_OUT                  9
#define CLINE_FE_DEFAULT_FONT                 10
#define CLINE_FE_ALTERNATE_FONT_1             11
#define CLINE_FE_ALTERNATE_FONT_2             12
#define CLINE_FE_ALTERNATE_FONT_3             13
#define CLINE_FE_ALTERNATE_FONT_4             14
#define CLINE_FE_ALTERNATE_FONT_5             15
#define CLINE_FE_ALTERNATE_FONT_6             16
#define CLINE_FE_ALTERNATE_FONT_7             17
#define CLINE_FE_ALTERNATE_FONT_8             18
#define CLINE_FE_ALTERNATE_FONT_9             19
#define CLINE_FE_BLACKLETTER                  20
#define CLINE_FE_BOLD_OFF                     21
#define CLINE_FE_DOUBLE_UNDELINE              21
#define CLINE_FE_NORMAL_COLOR                 22
#define CLINE_FE_NOT_ITALIC                   23
#define CLINE_FE_NOT_BLACKLETTER              23
#define CLINE_FE_UNDERLINE_OFF                24
#define CLINE_FE_BLINK_OFF                    25
#define CLINE_FE_PROPORTIONAL_SPACING         26
#define CLINE_FE_INVERSE_OFF                  27
#define CLINE_FE_REVEAL                       28
#define CLINE_FE_NOT_CROSSED_OUT              29
#define CLINE_FE_FOREGROUND_BLACK             30
#define CLINE_FE_FOREGROUND_RED               31
#define CLINE_FE_FOREGROUND_GREEN             32
#define CLINE_FE_FOREGROUND_YELLOW            33
#define CLINE_FE_FOREGROUND_BLUE              34
#define CLINE_FE_FOREGROUND_MAGENTA           35
#define CLINE_FE_FOREGROUND_CYAN              36
#define CLINE_FE_FOREGROUND_WHITE             37
#define CLINE_FE_SET_FOREGROUND               38
#define CLINE_FE_DEFAULT_FOREGROUND_COLOR     39
#define CLINE_FE_BACKGROUND_BLACK             40
#define CLINE_FE_BACKGROUND_RED               41
#define CLINE_FE_BACKGROUND_GREEN             42
#define CLINE_FE_BACKGROUND_YELLOW            43
#define CLINE_FE_BACKGROUND_BLUE              44
#define CLINE_FE_BACKGROUND_MAGENTA           45
#define CLINE_FE_BACKGROUND_CYAN              46
#define CLINE_FE_BACKGROUND_WHITE             47
#define CLINE_FE_SET_BACKGROUND               48
#define CLINE_FE_DEFAULT_BACKGROUND_COLOR     49
#define CLINE_FE_DISABLE_PROPORTIONAL_SPACING 50
#define CLINE_FE_FRAMED                       51
#define CLINE_FE_ENCIRCLED                    52
#define CLINE_FE_OVERLINED                    53
#define CLINE_FE_NEITHER_FRAMED_NOR_ENCIRCLED 54
#define CLINE_FE_NOT_OVERLINED                55
#define CLINE_FE_SET_UNDERLINE_COLOR          58
#define CLINE_FE_DEFAULT_UNDERLINE_COLOR      59
#define CLINE_FE_IDEOGRAM_UNDERLINE_OR_RIGHT_SIDE_LINE                 60
#define CLINE_FE_IDEOGRAM_DOUBLE_UNDERLINE_OR_DOUBLE_RIGHT_SIDE_LINE   61
#define CLINE_FE_IDEOGRAM_OVERLINE_OR_LEFT_SIDE_LINE                   62
#define CLINE_FE_IDEOGRAM_DOUBLE_OVERLINE_OR_DOUBLE_LEFT_SIDE_LINE     63
#define CLINE_FE_IDEOGRAM_STRESS_MARKING                               64
#define CLINE_FE_NO_IDEOGRAM_ATTR             65
#define CLINE_FE_SUPERSCRIPT                  73
#define CLINE_FE_SUBSCRIPT                    74
#define CLINE_FE_FOREGROUND_BRIGHT_BLACK      90
#define CLINE_FE_FOREGROUND_BRIGHT_RED        91
#define CLINE_FE_FOREGROUND_BRIGHT_GREEN      92
#define CLINE_FE_FOREGROUND_BRIGHT_YELLOW     93
#define CLINE_FE_FOREGROUND_BRIGHT_BLUE       94
#define CLINE_FE_FOREGROUND_BRIGHT_MAGENTA    95
#define CLINE_FE_FOREGROUND_BRIGHT_CYAN       96
#define CLINE_FE_FOREGROUND_BRIGHT_WHITE      97
#define CLINE_FE_BACKGROUND_BRIGHT_BLACK      100
#define CLINE_FE_BACKGROUND_BRIGHT_RED        101
#define CLINE_FE_BACKGROUND_BRIGHT_GREEN      102
#define CLINE_FE_BACKGROUND_BRIGHT_YELLOW     103
#define CLINE_FE_BACKGROUND_BRIGHT_BLUE       104
#define CLINE_FE_BACKGROUND_BRIGHT_MAGENTA    105
#define CLINE_FE_BACKGROUND_BRIGHT_CYAN       106
#define CLINE_FE_BACKGROUND_BRIGHT_WHITE      107

/*!

*/
#define CLINE_FE_FOREGROUND_RGB(r, g, b) CLINE_FE_SET_FOREGROUND, 2, r, g, b

/*!

*/
#define CLINE_FE_BACKGROUND_RGB(r, g, b) CLINE_FE_SET_BACKGROUND, 2, r, g, b

/*!

*/
#define CLINE_FE_FOREGROUND_MODE(mode) CLINE_FE_SET_FOREGROUND, 5, mode

/*!

*/
#define CLINE_FE_BACKGROUND_MODE(mode) CLINE_FE_SET_BACKGROUND, 5, mode

/*!
    The font effect macros used by cline.
    The values are appened to '\x1B[' and prepended with 'm' 
    for the combination of multiple effects they are seperated 
    by ';' 

    if the first font effect option is CLINE_OPTION_NONE all the font 
    effect option following it will be ignored and the text only will 
    be returned which is euivalent to just specifying the text directly, 
    this can be used to quick disable the effects without having to 
    delete the other font effect options. 
*/
const char *cline_fe_str_with_end_fe(const char *file_name, const int line_number, const char *text, const char *fe, const char *end_fe)
{
    int fe_length = strlen(fe);
    int concatenated_length = strlen(text) + fe_length + (fe_length > 0 ? strlen(end_fe) : 0);
    char *concatenated = (char *) malloc(concatenated_length+1);
    snprintf(concatenated, concatenated_length+1, "%s%s%s", fe, text, (fe_length > 0 ? end_fe : ""));
    /*free((void *)text);*/
    return concatenated;
}

/*!
   
*/
#define CLINE_FE(...) CLINE_ANSI_ENCODER('m', __VA_ARGS__)

/*!
   
*/
#define CLINE_FE_STR(text, ...) cline_fe_str_with_end_fe(__FILE__, __LINE__, text, CLINE_ANSI_ENCODER('m', __VA_ARGS__), CLINE_ANSI_ENCODER('m', CLINE_FE_RESET))

/*!
   
*/
#define CLINE_FE_STR_NO_RESET(text, ...) cline_fe_str_with_end_fe(__FILE__, __LINE__, text, CLINE_ANSI_ENCODER('m', __VA_ARGS__), "")

/*!
   
*/
#define CLINE_FE_INT(number, ...) number

/*!
   
*/
#define CLINE_FE_FLOAT(number, ...) number

#ifdef __cplusplus
}
#endif

#endif