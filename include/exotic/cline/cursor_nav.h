
/*!
    \copyright MIT License Copyright (c) 2021, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 19 February 2021
    \file cursor_nav.h

    cursor_nav.h is ...
*/

#ifndef EXOTIC_CLINE_CURSOR_NAV_H
#define EXOTIC_CLINE_CURSOR_NAV_H

#ifdef __cplusplus
extern "C" {
#endif

/*!

*/
#include "cline_common.h"

/*!
    The character that indicate which direction and position 
    the cursor should move to or which opertation should be 
    executed. 

    The asci code is getten by adding "\x1B[" follow by the number 
    of times n the operation is executed or the cursor is moved 
    (in required case) then the character. e.g. The character to 
    move the cursor up is 'A' and if we inted to move the cursor up 
    5 times we get "\x1B[5A" This will move the cursor up 5 times
*/
#define CLINE_CN_UP                    'A'
#define CLINE_CN_DOWN                  'B'
#define CLINE_CN_RIGHT                 'C'
#define CLINE_CN_LEFT                  'D'
#define CLINE_CN_NEXT_LINE             'E'
#define CLINE_CN_PREVIOUS_LINE         'F'
#define CLINE_CN_SET_COLUMN            'G'
#define CLINE_CN_POSITION              'H'
#define CLINE_CN_CLEAR_SCREEN          'J'
#define CLINE_CN_CLEAR_LINE            'K'
#define CLINE_CN_SAVE_POSITION         'K'
#define CLINE_CN_CLEAR_LINE            'K'

/*!

*/
#define CLINE_CN_MOVE_UP(times) CLINE_ANSI_ENCODER(CLINE_CN_UP, times)

/*!

*/
#define CLINE_CN_MOVE_DOWN(times) CLINE_ANSI_ENCODER(CLINE_CN_DOWN, times)

/*!

*/
#define CLINE_CN_MOVE_RIGHT(times) CLINE_ANSI_ENCODER(CLINE_CN_RIGHT, times)

/*!

*/
#define CLINE_CN_MOVE_LEFT(times) CLINE_ANSI_ENCODER(CLINE_CN_LEFT, times)

/*!

*/
#define CLINE_CN_MOVE_NEXT_LINE(position) CLINE_ANSI_ENCODER(CLINE_CN_NEXT_LINE, position)

/*!

*/
#define CLINE_CN_MOVE_PREVIOUS_LINE(position) CLINE_ANSI_ENCODER(CLINE_CN_PREVIOUS_LINE, position)

/*!

*/
#define CLINE_CN_MOVE_TO_COLUMN(column) CLINE_ANSI_ENCODER(CLINE_CN_SET_COLUMN, column)

/*!

*/
#define CLINE_CN_MOVE_TO_POSITION(row, column) CLINE_ANSI_ENCODER(CLINE_CN_POSITION, row, column)

/*!

*/
#define CLINE_CN_CLEAR_TERMINAL_SCREEN_WITH(code) CLINE_ANSI_ENCODER(CLINE_CN_CLEAR_SCREEN, code)

/*!

*/
#define CLINE_CN_CLEAR_TERMINAL_SCREEN_TO_BOTTOM() CLINE_ANSI_ENCODER(CLINE_CN_CLEAR_SCREEN, 0)

/*!

*/
#define CLINE_CN_CLEAR_TERMINAL_SCREEN_TO_TOP() CLINE_ANSI_ENCODER(CLINE_CN_CLEAR_SCREEN, 1)

/*!

*/
#define CLINE_CN_CLEAR_TERMINAL_SCREEN() CLINE_ANSI_ENCODER(CLINE_CN_CLEAR_SCREEN, 2)

/*!

*/
#define CLINE_CN_CLEAR_TERMINAL_LINE_WITH(code) CLINE_ANSI_ENCODER(CLINE_CN_CLEAR_LINE, code)

/*!

*/
#define CLINE_CN_CLEAR_TERMINAL_LINE_TO_END() CLINE_ANSI_ENCODER(CLINE_CN_CLEAR_LINE, 0)

/*!

*/
#define CLINE_CN_CLEAR_TERMINAL_LINE_TO_BEGINNING() CLINE_ANSI_ENCODER(CLINE_CN_CLEAR_LINE, 1)

/*!

*/
#define CLINE_CN_CLEAR_TERMINAL_LINE() CLINE_ANSI_ENCODER(CLINE_CN_CLEAR_LINE, 2)


#ifdef __cplusplus
}
#endif

#endif