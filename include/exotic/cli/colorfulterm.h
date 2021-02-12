
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

/**

*/
#ifdef _WIN32

#define CLINE_RESET_TERMINAL           15                                                /**< reset the terminal color //Nothing */
#define CLINE_BOLD                     15                                                /**< bold text                //Nothing */
#define CLINE_FG_BLACK         8                                                         /**< gray terminal FG color             */
#define CLINE_FG_RED           4                                                         /**< red terminal FG color              */
#define CLINE_FG_GREEN         2                                                         /**< green FG color                     */
#define CLINE_FG_YELLOW        6                                                         /**< yellow terminal FG color           */
#define CLINE_FG_BLUE          3                                                         /**< blue terminal FG color             */
#define CLINE_FG_MAGENTA       5                                                         /**< magenta terminal FG color          */
#define CLINE_FG_CYAN          11                                                        /**< cyan terminal FG color             */
#define CLINE_FG_WHITE         15                                                        /**< white terminal FG color            */
#define CLINE_FG_GRAY          8                                                         /**< gray terminal FG color             */
#define CLINE_BG_BLACK         0                                                         /**< black terminal BG color            */
#define CLINE_BG_RED           64                                                        /**< red terminal BG color              */
#define CLINE_BG_GREEN         39                                                        /**< green terminal BG color            */
#define CLINE_BG_YELLOW        96                                                        /**< yellow terminal BG color           */
#define CLINE_BG_BLUE          48                                                        /**< blue terminal BG color             */
#define CLINE_BG_MAGENTA       87                                                        /**< magenta terminal BG color          */
#define CLINE_BG_CYAN          176                                                       /**< cyan terminal BG color             */
#define CLINE_BG_GRAY          0                                                         /**< gray terminal BG color             */
#define CLINE_BG_WHITE         10                                                        /**< gray terminal BG color             */
#define CLINE_RESET_TERMINAL_ATTR() SetConsoleTextAttribute(hConsole, default_color);    /**< reset the terminal color           */

#else

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
#define CLINE_RESET_TERMINAL_ATTR()    ;     /**< reset the terminal color   */

#endif

void cline_platform_printnl_if()
{
    #ifndef _WIN32
        printf("\n");
    #endif
}

#define cline_color_printff(...)

#define cline_color_printfb(...)

#define cline_color_printffb(...)

#ifdef __cplusplus
}
#endif

#endif