/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/cline/colorfulterm.h>

#ifdef _WIN32
CESTER_TEST(validate_color_values, inst, {
    cester_assert_uint_eq(CLINE_FG_BLACK, 8);
    cester_assert_uint_eq(CLINE_FG_RED, 4);
    cester_assert_uint_eq(CLINE_FG_GREEN, 2);
    cester_assert_uint_eq(CLINE_RESET_TERMINAL, CLINE_BOLD);
})
#else
CESTER_TEST(validate_color_values, inst, {
    cester_assert_str_equal(CLINE_FG_BLACK, "\x1B[30m");
    cester_assert_str_equal(CLINE_FG_RED, "\x1B[31m");
    cester_assert_str_equal(CLINE_FG_GREEN, "\x1B[32m");
    cester_assert_str_not_equal(CLINE_RESET_TERMINAL, CLINE_BOLD);
})
#endif
