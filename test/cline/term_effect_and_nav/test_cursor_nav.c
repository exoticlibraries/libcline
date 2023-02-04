/*!gcc {0} -I. -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/cline/cursor_nav.h>

CESTER_TEST(validate_the_nav_characters, inst, {
    cester_assert_char_eq(CLINE_CN_UP, 'A');
    cester_assert_char_eq(CLINE_CN_DOWN, 'B');
    cester_assert_char_eq(CLINE_CN_RIGHT, 'C');
    cester_assert_char_eq(CLINE_CN_LEFT, 'D');
    cester_assert_char_eq(CLINE_CN_NEXT_LINE, 'E');
    cester_assert_char_eq(CLINE_CN_PREVIOUS_LINE, 'F');
    cester_assert_char_eq(CLINE_CN_SET_COLUMN, 'G');
    cester_assert_char_eq(CLINE_CN_POSITION, 'H');
    cester_assert_char_eq(CLINE_CN_CLEAR_SCREEN, 'J');
    cester_assert_char_eq(CLINE_CN_CLEAR_LINE, 'K');
})

CESTER_TEST(navigate_cursor_n_times_cline_ansi_encoder, inst, {
    cester_assert_str_equal(CLINE_CN_MOVE_UP(1), "\x1B[1A");
    cester_assert_str_equal(CLINE_CN_MOVE_UP(4), "\x1B[4A");
    cester_assert_str_equal(CLINE_CN_MOVE_DOWN(1), "\x1B[1B");
    cester_assert_str_equal(CLINE_CN_MOVE_RIGHT(1), "\x1B[1C");
    cester_assert_str_equal(CLINE_CN_MOVE_LEFT(1), "\x1B[1D");
})

CESTER_TEST(navigate_cursor_position_and_line, inst, {
    cester_assert_str_equal(CLINE_CN_MOVE_NEXT_LINE(2), "\x1B[2E");
    cester_assert_str_equal(CLINE_CN_MOVE_PREVIOUS_LINE(2), "\x1B[2F");
    cester_assert_str_equal(CLINE_CN_MOVE_TO_COLUMN(0), "\x1B[0G");
    cester_assert_str_equal(CLINE_CN_MOVE_TO_POSITION(2, 1), "\x1B[2;1H");
})

CESTER_TEST(clear_terminal_screen, inst, {
    cester_assert_str_equal(CLINE_CN_CLEAR_TERMINAL_SCREEN_WITH(1), "\x1B[1J");
    cester_assert_str_equal(CLINE_CN_CLEAR_TERMINAL_SCREEN_TO_BOTTOM(), "\x1B[0J");
    cester_assert_str_equal(CLINE_CN_CLEAR_TERMINAL_SCREEN_TO_TOP(), "\x1B[1J");
    cester_assert_str_equal(CLINE_CN_CLEAR_TERMINAL_SCREEN(), "\x1B[2J");
})

CESTER_TEST(clear_terminal_line, inst, {
    cester_assert_str_equal(CLINE_CN_CLEAR_TERMINAL_LINE_WITH(1), "\x1B[1K");
    cester_assert_str_equal(CLINE_CN_CLEAR_TERMINAL_LINE_TO_END(), "\x1B[0K");
    cester_assert_str_equal(CLINE_CN_CLEAR_TERMINAL_LINE_TO_BEGINNING(), "\x1B[1K");
    cester_assert_str_equal(CLINE_CN_CLEAR_TERMINAL_LINE(), "\x1B[2K");
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(1);
)

