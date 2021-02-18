/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/cline/colorfulterm.h>

CESTER_TEST(preety_print, _, {
    printf("%s%s%s\n", CLINE_FE(CLINE_FE_REVERSE_VIDEO), "Hello World", CLINE_FE(CLINE_FE_RESET));
    printf("%s%s%s\n", CLINE_FE(CLINE_FE_SET_FOREGROUND, 2, 201, 133, 173), "Hello World", CLINE_FE(CLINE_FE_RESET));
    printf("%s%s%s\n", CLINE_FE(CLINE_FE_SET_BACKGROUND, 5, 30), "Hello World", CLINE_FE(CLINE_FE_RESET));
    printf("%s%s%s\n", CLINE_FE(CLINE_FE_SET_FOREGROUND, 2, 141, 153, 116, CLINE_FE_SET_BACKGROUND, 5, 88), "Hello World", CLINE_FE(CLINE_FE_RESET));
    printf("%s%s%s\n", CLINE_FE(CLINE_FE_FOREGROUND_YELLOW, CLINE_FE_BACKGROUND_GREEN), "Hello World", CLINE_FE(CLINE_FE_RESET));
})

CESTER_TEST(test_font_effect_printf, _, {
    CESTER_CAPTURE_STDOUT();

    CESTER_RESET_STDOUT();
    printf("%sThe Only No Effect", CLINE_FE(CLINE_FE_NONE, CLINE_FE_FAINT, CLINE_FE_RAPID_BLINK));
    cester_assert_stdout_stream_content_equal("The Only No Effect");

    CESTER_RESET_STDOUT();
    printf("%sCrossed Out\n", CLINE_FE(CLINE_FE_CROSSED_OUT));
    printf("%s", CLINE_FE(CLINE_FE_RESET));
    cester_assert_stdout_stream_content_equal("\x1B[9mCrossed Out\n\x1B[0m");

    CESTER_RESET_STDOUT();
    printf("%sCustom Font", CLINE_FE(CLINE_FE_ALTERNATE_FONT_6));
    printf("%s", CLINE_FE(CLINE_FE_RESET));
    cester_assert_stdout_stream_content_equal("\x1B[16mCustom Font\x1B[0m");

    CESTER_RESET_STDOUT();
    printf("%sMultiple Font Effects", CLINE_FE(CLINE_FE_BOLD, CLINE_FE_UNDERLINE, CLINE_FE_SLOW_BLINK));
    printf("%s", CLINE_FE(CLINE_FE_RESET));
    cester_assert_stdout_stream_content_equal("\x1B[1;4;5mMultiple Font Effects\x1B[0m");

    CESTER_RELEASE_STDOUT();
})

CESTER_TEST(test_font_effect_fprintf, _, {
    CESTER_CAPTURE_STDERR();

    CESTER_RESET_STDERR();
    fprintf(stderr, "%sThe Only No Effect", CLINE_FE(CLINE_FE_NONE, CLINE_FE_FAINT, CLINE_FE_RAPID_BLINK));
    cester_assert_stderr_stream_content_equal("The Only No Effect");

    CESTER_RESET_STDERR();
    fprintf(stderr, "%sCrossed Out\n", CLINE_FE(CLINE_FE_CROSSED_OUT));
    fprintf(stderr, "%s", CLINE_FE(CLINE_FE_RESET));
    cester_assert_stderr_stream_content_equal("\x1B[9mCrossed Out\n\x1B[0m");

    CESTER_RESET_STDERR();
    fprintf(stderr, "%sCustom Font", CLINE_FE(CLINE_FE_ALTERNATE_FONT_6));
    fprintf(stderr, "%s", CLINE_FE(CLINE_FE_RESET));
    cester_assert_stderr_stream_content_equal("\x1B[16mCustom Font\x1B[0m");

    CESTER_RESET_STDERR();
    fprintf(stderr, "%sMultiple Font Effects", CLINE_FE(CLINE_FE_BOLD, CLINE_FE_UNDERLINE, CLINE_FE_SLOW_BLINK));
    fprintf(stderr, "%s", CLINE_FE(CLINE_FE_RESET));
    cester_assert_stderr_stream_content_equal("\x1B[1;4;5mMultiple Font Effects\x1B[0m");

    CESTER_RELEASE_STDERR();
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

