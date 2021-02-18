/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/cline/colorfulterm.h>

CESTER_TEST(validate_negative_font_effect_values, inst, {
    cester_assert_uint_eq(CLINE_FE_NONE, -1);
})

CESTER_TEST(validate_first_11_font_effect_values, inst, {
    cester_assert_uint_eq(CLINE_FE_RESET, 0);
    cester_assert_uint_eq(CLINE_FE_BOLD, 1);
    cester_assert_uint_eq(CLINE_FE_FAINT, 2);
    cester_assert_uint_eq(CLINE_FE_ITALIC, 3);
    cester_assert_uint_eq(CLINE_FE_UNDERLINE, 4);
    cester_assert_uint_eq(CLINE_FE_SLOW_BLINK, 5);
    cester_assert_uint_eq(CLINE_FE_RAPID_BLINK, 6);
    cester_assert_uint_eq(CLINE_FE_REVERSE_VIDEO, 7);
    cester_assert_uint_eq(CLINE_FE_CONCEAL, 8);
    cester_assert_uint_eq(CLINE_FE_CROSSED_OUT, 9);
    cester_assert_uint_eq(CLINE_FE_DEFAULT_FONT, 10);
})

CESTER_TEST(validate_next_10_font_effect_values, inst, {
    cester_assert_uint_eq(CLINE_FE_ALTERNATE_FONT_1, 11);
    cester_assert_uint_eq(CLINE_FE_ALTERNATE_FONT_2, 12);
    cester_assert_uint_eq(CLINE_FE_ALTERNATE_FONT_3, 13);
    cester_assert_uint_eq(CLINE_FE_ALTERNATE_FONT_4, 14);
    cester_assert_uint_eq(CLINE_FE_ALTERNATE_FONT_5, 15);
    cester_assert_uint_eq(CLINE_FE_ALTERNATE_FONT_6, 16);
    cester_assert_uint_eq(CLINE_FE_ALTERNATE_FONT_7, 17);
    cester_assert_uint_eq(CLINE_FE_ALTERNATE_FONT_8, 18);
    cester_assert_uint_eq(CLINE_FE_ALTERNATE_FONT_9, 19);
    cester_assert_uint_eq(CLINE_FE_BLACKLETTER, 20);
})

CESTER_TEST(validate_next_9_font_effect_values, inst, {
    cester_assert_uint_eq(CLINE_FE_BOLD_OFF, 21);
    cester_assert_uint_eq(CLINE_FE_DOUBLE_UNDELINE, 21);
    cester_assert_uint_eq(CLINE_FE_NORMAL_COLOR, 22);
    cester_assert_uint_eq(CLINE_FE_NOT_ITALIC, 23);
    cester_assert_uint_eq(CLINE_FE_NOT_BLACKLETTER, 23);
    cester_assert_uint_eq(CLINE_FE_UNDERLINE_OFF, 24);
    cester_assert_uint_eq(CLINE_FE_BLINK_OFF, 25);
    cester_assert_uint_eq(CLINE_FE_PROPORTIONAL_SPACING, 26);
    cester_assert_uint_eq(CLINE_FE_INVERSE_OFF, 27);
    cester_assert_uint_eq(CLINE_FE_REVEAL, 28);
    cester_assert_uint_eq(CLINE_FE_NOT_CROSSED_OUT, 29);
})

CESTER_TEST(validate_font_effect_foreground_values, inst, {
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_BLACK, 30);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_RED, 31);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_GREEN, 32);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_YELLOW, 33);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_BLUE, 34);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_MAGENTA, 35);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_CYAN, 36);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_WHITE, 37);
    cester_assert_uint_eq(CLINE_FE_SET_FOREGROUND, 38);
    cester_assert_uint_eq(CLINE_FE_DEFAULT_FOREGROUND_COLOR, 39);
})

CESTER_TEST(validate_font_effect_background_values, inst, {
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_BLACK, 40);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_RED, 41);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_GREEN, 42);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_YELLOW, 43);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_BLUE, 44);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_MAGENTA, 45);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_CYAN, 46);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_WHITE, 47);
    cester_assert_uint_eq(CLINE_FE_SET_BACKGROUND, 48);
    cester_assert_uint_eq(CLINE_FE_DEFAULT_BACKGROUND_COLOR, 49);
})

CESTER_TEST(validate_next_font_effect_values_1, inst, {
    cester_assert_uint_eq(CLINE_FE_DISABLE_PROPORTIONAL_SPACING, 50);
    cester_assert_uint_eq(CLINE_FE_FRAMED, 51);
    cester_assert_uint_eq(CLINE_FE_ENCIRCLED, 52);
    cester_assert_uint_eq(CLINE_FE_OVERLINED, 53);
    cester_assert_uint_eq(CLINE_FE_NEITHER_FRAMED_NOR_ENCIRCLED, 54);
    cester_assert_uint_eq(CLINE_FE_NOT_OVERLINED, 55);
    cester_assert_uint_eq(CLINE_FE_SET_UNDERLINE_COLOR, 58);
    cester_assert_uint_eq(CLINE_FE_DEFAULT_UNDERLINE_COLOR, 59);
    cester_assert_uint_eq(CLINE_FE_IDEOGRAM_UNDERLINE_OR_RIGHT_SIDE_LINE, 60);
    cester_assert_uint_eq(CLINE_FE_IDEOGRAM_DOUBLE_UNDERLINE_OR_DOUBLE_RIGHT_SIDE_LINE, 61);
    cester_assert_uint_eq(CLINE_FE_IDEOGRAM_OVERLINE_OR_LEFT_SIDE_LINE, 62);
    cester_assert_uint_eq(CLINE_FE_IDEOGRAM_DOUBLE_OVERLINE_OR_DOUBLE_LEFT_SIDE_LINE, 63);
    cester_assert_uint_eq(CLINE_FE_IDEOGRAM_STRESS_MARKING, 64);
    cester_assert_uint_eq(CLINE_FE_NO_IDEOGRAM_ATTR, 65);
    cester_assert_uint_eq(CLINE_FE_SUPERSCRIPT, 73);
    cester_assert_uint_eq(CLINE_FE_SUBSCRIPT, 74);
})

CESTER_TEST(validate_font_effect_bright_foreground_values, inst, {
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_BRIGHT_BLACK, 90);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_BRIGHT_RED, 91);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_BRIGHT_GREEN, 92);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_BRIGHT_YELLOW, 93);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_BRIGHT_BLUE, 94);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_BRIGHT_MAGENTA, 95);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_BRIGHT_CYAN, 96);
    cester_assert_uint_eq(CLINE_FE_FOREGROUND_BRIGHT_WHITE, 97);
})

CESTER_TEST(validate_font_effect_bright_background_values, inst, {
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_BRIGHT_BLACK, 100);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_BRIGHT_RED, 101);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_BRIGHT_GREEN, 102);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_BRIGHT_YELLOW, 103);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_BRIGHT_BLUE, 104);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_BRIGHT_MAGENTA, 105);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_BRIGHT_CYAN, 106);
    cester_assert_uint_eq(CLINE_FE_BACKGROUND_BRIGHT_WHITE, 107);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)
