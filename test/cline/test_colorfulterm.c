/*!clang++ -ansi -pedantic-errors {0} -I. -I../../include/ -o out.exe; ./out.exe */

#include <exotic/cester.h>
#include <exotic/cline/colorfulterm.h>

CESTER_TEST(no_font_effect, inst, {
    cester_assert_str_equal(CLINE_FE_STR("No Effect 1", CLINE_FE_NONE), "No Effect 1");
    cester_assert_int_eq(CLINE_FE_INT(30, CLINE_FE_NONE), 30);
    cester_assert_float_eq(CLINE_FE_FLOAT(1.65, CLINE_FE_NONE), 1.65);
    
    cester_assert_str_equal(CLINE_FE_STR("Ignore Other Options", CLINE_FE_NONE, CLINE_FE_BOLD, CLINE_FE_UNDERLINE), "Ignore Other Options");
    cester_assert_int_eq(CLINE_FE_INT(30, CLINE_FE_NONE, CLINE_FE_BOLD, CLINE_FE_BACKGROUND_YELLOW, CLINE_FE_FOREGROUND_RED), 30);
    cester_assert_float_eq(CLINE_FE_FLOAT(1.65, CLINE_FE_NONE, CLINE_FE_FOREGROUND_BRIGHT_CYAN, CLINE_FE_BACKGROUND_BRIGHT_BLACK, CLINE_FE_FRAMED), 1.65);
})

CESTER_TEST(dont_reset_font_effect, inst, {
    cester_assert_str_equal(CLINE_FE_STR_NO_RESET("Bold Effect", CLINE_FE_BOLD), "\x1B[1mBold Effect");
    cester_assert_str_equal(CLINE_FE_STR_NO_RESET("Faint Effect", CLINE_FE_FAINT), "\x1B[2mFaint Effect");
    cester_assert_str_equal(CLINE_FE_STR_NO_RESET("Italic Effect", CLINE_FE_ITALIC), "\x1B[3mItalic Effect");
    cester_assert_str_equal(CLINE_FE_STR_NO_RESET("Undeline Effect", CLINE_FE_UNDERLINE), "\x1B[4mUndeline Effect");
    cester_assert_str_equal(CLINE_FE_STR_NO_RESET("Slow Blink Effect", CLINE_FE_SLOW_BLINK), "\x1B[5mSlow Blink Effect");
})

CESTER_TEST(basic_single_font_effect_str, inst, {
    cester_assert_str_equal(CLINE_FE_STR("Pointless", CLINE_FE_RESET), "\x1B[0mPointless\x1B[0m");
    cester_assert_str_equal(CLINE_FE_STR("Bold Effect", CLINE_FE_BOLD), "\x1B[1mBold Effect\x1B[0m");
    cester_assert_str_equal(CLINE_FE_STR("Faint Effect", CLINE_FE_FAINT), "\x1B[2mFaint Effect\x1B[0m");
    cester_assert_str_equal(CLINE_FE_STR("Italic Effect", CLINE_FE_ITALIC), "\x1B[3mItalic Effect\x1B[0m");
    cester_assert_str_equal(CLINE_FE_STR("Undeline Effect", CLINE_FE_UNDERLINE), "\x1B[4mUndeline Effect\x1B[0m");
    cester_assert_str_equal(CLINE_FE_STR("Slow Blink Effect", CLINE_FE_SLOW_BLINK), "\x1B[5mSlow Blink Effect\x1B[0m");
    cester_assert_str_equal(CLINE_FE_STR("Rapid Blink Effect", CLINE_FE_RAPID_BLINK), "\x1B[6mRapid Blink Effect\x1B[0m");
    cester_assert_str_equal(CLINE_FE_STR("Reverse Video Effect", CLINE_FE_REVERSE_VIDEO), "\x1B[7mReverse Video Effect\x1B[0m");
    cester_assert_str_equal(CLINE_FE_STR("Conceal Effect", CLINE_FE_CONCEAL), "\x1B[8mConceal Effect\x1B[0m");
    cester_assert_str_equal(CLINE_FE_STR("Crossed Out Effect", CLINE_FE_CROSSED_OUT), "\x1B[9mCrossed Out Effect\x1B[0m");
})

/* test other types */
CESTER_TEST(str_with_color_bg, inst, {
    cester_assert_str_equal(CLINE_FE_STR("Color Red", CLINE_FE_BACKGROUND_RED), "\x1B[41mColor Red\x1B[0m");
    cester_assert_str_equal(CLINE_FE_STR("Color Green", CLINE_FE_BACKGROUND_GREEN), "\x1B[42mColor Green\x1B[0m");
    cester_assert_str_equal(CLINE_FE_STR("Color Blue", CLINE_FE_BACKGROUND_BLUE), "\x1B[44mColor Blue\x1B[0m");
})

CESTER_TEST(printf_stream_output_fg, inst, {
    CESTER_CAPTURE_STDOUT();

    CESTER_RESET_STDOUT();
    printf("%s", CLINE_FE_STR("Color Red", CLINE_FE_FOREGROUND_RED));
    cester_assert_printf_equal("\x1B[31mColor Red\x1B[0m");

    CESTER_RESET_STDOUT();
    printf("%s", CLINE_FE_STR("Color Green", CLINE_FE_FOREGROUND_GREEN));
    cester_assert_printf_equal("\x1B[32mColor Green\x1B[0m");

    CESTER_RESET_STDOUT();
    printf("%s", CLINE_FE_STR("Color Blue", CLINE_FE_FOREGROUND_BLUE));
    cester_assert_printf_equal("\x1B[34mColor Blue\x1B[0m");

    CESTER_RELEASE_STDOUT();
})

CESTER_TEST(printf_stream_output_bg, inst, {
    CESTER_CAPTURE_STREAM(stdout);

    printf("%s", CLINE_FE_STR("Red", CLINE_FE_BACKGROUND_RED));
    cester_assert_stream_content_equal(stdout, "\x1B[41mRed\x1B[0m");

    printf("%s", CLINE_FE_STR("Color Green", CLINE_FE_BACKGROUND_GREEN));
    cester_assert_stream_content_equal(stdout, "\x1B[41mRed\x1B[0m\x1B[42mColor Green\x1B[0m");

    printf("%s", CLINE_FE_STR("Color Blue", CLINE_FE_BACKGROUND_BLUE));
    puts("");
    cester_assert_stream_content_equal(stdout, "\x1B[41mRed\x1B[0m\x1B[42mColor Green\x1B[0m\x1B[44mColor Blue\x1B[0m\n");

    CESTER_RELEASE_STREAM(stdout);
})

CESTER_TEST(fprintf_stream_output, inst, {
    CESTER_CAPTURE_STREAM(stdout);

    fprintf(stdout, "%s", CLINE_FE_STR("Red", CLINE_FE_FOREGROUND_RED));
    cester_assert_stream_content_equal(stdout, "\x1B[31mRed\x1B[0m");
    fprintf(stdout, "%s", CLINE_FE_STR("Color Blue", CLINE_FE_BACKGROUND_BLUE));
    cester_assert_stream_content_equal(stdout, "\x1B[31mRed\x1B[0m\x1B[44mColor Blue\x1B[0m");
    CESTER_RESET_STDOUT();
    fprintf(stdout, "%s %s %s %s\n", CLINE_FE_STR("Red", CLINE_FE_FOREGROUND_RED), CLINE_FE_STR("Green", CLINE_FE_FOREGROUND_GREEN), 
                            CLINE_FE_STR("Blue", CLINE_FE_FOREGROUND_BLUE), CLINE_FE_STR("Yellow", CLINE_FE_FOREGROUND_YELLOW));
    cester_assert_stream_content_equal(stdout, "\x1B[31mRed\x1B[0m \x1B[32mGreen\x1B[0m \x1B[34mBlue\x1B[0m \x1B[33mYellow\x1B[0m\n");

    CESTER_RELEASE_STREAM(stdout);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
    CESTER_PRINT_ERROR_ONLY(1);
)

