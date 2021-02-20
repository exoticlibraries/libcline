/*!gcc {0} -I. -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/cline/cline_common.h>

CESTER_TEST(validate_cline_common_values, inst, {
    cester_assert_uint_eq(CLINE_FE_PADDING_INTERNAL, -100);
    cester_assert_uint_eq(CLINE_OPTION_NONE, -101);
    cester_assert_char_eq(CLINE_BELL, '\a');
})

CESTER_TEST(test_cline_ansi_encoder, inst, {
    cester_assert_str_equal(CLINE_ANSI_ENCODER('m', CLINE_OPTION_NONE), "");
    cester_assert_str_equal(CLINE_ANSI_ENCODER('m', 1, 2, 3), "\x1B[1;2;3m");
    cester_assert_str_equal(CLINE_ANSI_ENCODER('D', 1, 2, 3), "\x1B[1;2;3D");
    cester_assert_str_equal(CLINE_ANSI_ENCODER('A', 100), "\x1B[100A");
    cester_assert_str_equal(CLINE_ANSI_ENCODER('D', 21), "\x1B[21D");
    cester_assert_str_equal(CLINE_ANSI_ENCODER('J', 2), "\x1B[2J");
    cester_assert_str_equal(CLINE_ANSI_ENCODER_ESCAPE_ONLY('H'), "\x1B[H");
})

CESTER_TEST(test_cline_reporters, inst, {
    /*printf("\7");*/
    CLINE_INTERNAL_DIE(__FILE__, __LINE__, "Do Kill\n");
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
    CESTER_TEST_SHOULD_FAIL(test_cline_reporters);
)

