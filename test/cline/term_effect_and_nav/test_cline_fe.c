/*!gcc {0} -I. -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/cline/font_effect.h>

CESTER_TEST(test_font_effect_none, inst, {
    cester_assert_str_equal(CLINE_FE(CLINE_OPTION_NONE), "");
    cester_assert_str_equal(CLINE_FE(CLINE_OPTION_NONE, CLINE_FE_BOLD, CLINE_FE_UNDERLINE), "");
    cester_assert_str_equal(CLINE_FE(CLINE_OPTION_NONE, CLINE_FE_BOLD, CLINE_FE_BACKGROUND_YELLOW, CLINE_FE_FOREGROUND_RED), "");
    cester_assert_str_equal(CLINE_FE(CLINE_OPTION_NONE, CLINE_FE_FOREGROUND_BRIGHT_CYAN, CLINE_FE_BACKGROUND_BRIGHT_BLACK, CLINE_FE_FRAMED), "");
})

CESTER_TEST(test_single_value_font_effects, inst, {
    cester_assert_str_equal(CLINE_FE(CLINE_FE_RESET), "\x1B[0m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BOLD), "\x1B[1m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FAINT), "\x1B[2m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_ITALIC), "\x1B[3m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_UNDERLINE), "\x1B[4m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_SLOW_BLINK), "\x1B[5m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_RAPID_BLINK), "\x1B[6m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_REVERSE_VIDEO), "\x1B[7m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_CONCEAL), "\x1B[8m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_CROSSED_OUT), "\x1B[9m");
})

CESTER_TEST(test_multiple_font_effects_combinations, inst, {
    cester_assert_str_equal(CLINE_FE(CLINE_FE_RESET, CLINE_FE_BOLD, CLINE_FE_FAINT), "\x1B[0;1;2m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BOLD, CLINE_FE_UNDERLINE, CLINE_FE_SLOW_BLINK), "\x1B[1;4;5m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FAINT, CLINE_FE_RAPID_BLINK), "\x1B[2;6m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_CROSSED_OUT, CLINE_FE_RAPID_BLINK, CLINE_FE_ITALIC, CLINE_FE_UNDERLINE), "\x1B[9;6;3;4m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_REVERSE_VIDEO, CLINE_FE_CONCEAL), "\x1B[7;8m");
})

CESTER_TEST(test_alternate_font_effects, inst, {
    cester_assert_str_equal(CLINE_FE(CLINE_FE_DEFAULT_FONT), "\x1B[10m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_ALTERNATE_FONT_1), "\x1B[11m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_ALTERNATE_FONT_2), "\x1B[12m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_ALTERNATE_FONT_3), "\x1B[13m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_ALTERNATE_FONT_4), "\x1B[14m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_ALTERNATE_FONT_5), "\x1B[15m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_ALTERNATE_FONT_6), "\x1B[16m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_ALTERNATE_FONT_7), "\x1B[17m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_ALTERNATE_FONT_8), "\x1B[18m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_ALTERNATE_FONT_9), "\x1B[19m");
})

CESTER_TEST(test_foreground_font_effects, inst, {
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_BLACK), "\x1B[30m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_RED), "\x1B[31m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_GREEN), "\x1B[32m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_YELLOW), "\x1B[33m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_BLUE), "\x1B[34m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_MAGENTA), "\x1B[35m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_CYAN), "\x1B[36m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_WHITE), "\x1B[37m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_SET_FOREGROUND, 2, 68, 14, 156), "\x1B[38;2;68;14;156m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_SET_FOREGROUND, 5, 100), "\x1B[38;5;100m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_DEFAULT_FOREGROUND_COLOR), "\x1B[39m");
})

CESTER_TEST(test_background_font_effects, inst, {
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_BLACK), "\x1B[40m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_RED), "\x1B[41m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_GREEN), "\x1B[42m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_YELLOW), "\x1B[43m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_BLUE), "\x1B[44m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_MAGENTA), "\x1B[45m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_CYAN), "\x1B[46m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_WHITE), "\x1B[47m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_SET_BACKGROUND, 2, 68, 14, 156), "\x1B[48;2;68;14;156m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_SET_BACKGROUND, 5, 100), "\x1B[48;5;100m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_DEFAULT_BACKGROUND_COLOR), "\x1B[49m");
})

CESTER_TEST(test_foreground_background_font_effects, inst, {
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_RED, CLINE_FE_BACKGROUND_BLACK), "\x1B[31;40m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_YELLOW, CLINE_FE_BACKGROUND_GREEN), "\x1B[33;42m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_BLUE, CLINE_FE_BACKGROUND_MAGENTA), "\x1B[34;45m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_CYAN, CLINE_FE_FOREGROUND_WHITE), "\x1B[46;37m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_SET_BACKGROUND, 2, 68, 14, 156, CLINE_FE_SET_FOREGROUND, 5, 100), "\x1B[48;2;68;14;156;38;5;100m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_DEFAULT_FOREGROUND_COLOR, CLINE_FE_DEFAULT_BACKGROUND_COLOR), "\x1B[39;49m");
})

CESTER_TEST(test_generate_foreground_background_font_effects_rgb_and_mode, inst, {
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_RGB(68, 14, 156)), "\x1B[38;2;68;14;156m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_RGB(68, 14, 156)), "\x1B[48;2;68;14;156m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_MODE(100)), "\x1B[38;5;100m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_MODE(100)), "\x1B[48;5;100m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_RGB(68, 14, 156), CLINE_FE_FOREGROUND_MODE(100)), "\x1B[48;2;68;14;156;38;5;100m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_RGB(5, 34, 102), CLINE_FE_BACKGROUND_MODE(23)), "\x1B[38;2;5;34;102;48;5;23m");
})

CESTER_TEST(test_bright_foreground_font_effects, inst, {
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_BRIGHT_BLACK), "\x1B[90m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_BRIGHT_RED), "\x1B[91m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_BRIGHT_GREEN), "\x1B[92m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_BRIGHT_YELLOW), "\x1B[93m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_BRIGHT_BLUE), "\x1B[94m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_BRIGHT_MAGENTA), "\x1B[95m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_BRIGHT_CYAN), "\x1B[96m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_FOREGROUND_BRIGHT_WHITE), "\x1B[97m");
})

CESTER_TEST(test_bright_background_font_effects, inst, {
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_BRIGHT_BLACK), "\x1B[100m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_BRIGHT_RED), "\x1B[101m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_BRIGHT_GREEN), "\x1B[102m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_BRIGHT_YELLOW), "\x1B[103m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_BRIGHT_BLUE), "\x1B[104m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_BRIGHT_MAGENTA), "\x1B[105m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_BRIGHT_CYAN), "\x1B[106m");
    cester_assert_str_equal(CLINE_FE(CLINE_FE_BACKGROUND_BRIGHT_WHITE), "\x1B[107m");
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

