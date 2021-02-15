/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/cline/colorfulterm.h>

CESTER_TEST(STR_with_color_fg, inst, {
    cester_assert_str_equal(CLINE_COLORSTR("Color Red", CLINE_FG_RED, CLINE_UNDERLINE), "\x1B[31mColor Red\x1B[0m");
    /*cester_assert_str_equal(CLINE_COLORSTR(CLINE_FG_GREEN, "Color Green"), "\x1B[32mColor Green\x1B[0m");
    cester_assert_str_equal(CLINE_COLORSTR(CLINE_FG_BLUE, "Color Blue"), "\x1B[34mColor Blue\x1B[0m");*/
})

/* use variadic to accept bold et.t.c)*/
CESTER_TODO_TEST(STR_with_color_bg, inst, {
    cester_assert_str_equal(CLINE_COLORSTR(CLINE_BG_RED, "Color Red"), "\x1B[41mColor Red\x1B[0m");
    cester_assert_str_equal(CLINE_COLORSTR(CLINE_BG_GREEN, "Color Green"), "\x1B[42mColor Green\x1B[0m");
    cester_assert_str_equal(CLINE_COLORSTR(CLINE_BG_BLUE, "Color Blue"), "\x1B[44mColor Blue\x1B[0m");
})

CESTER_TODO_TEST(printf_stream_output_fg, inst, {
    CESTER_CAPTURE_STDOUT();

    CESTER_RESET_STDOUT();
    printf("%s", CLINE_COLORSTR(CLINE_FG_RED, "Color Red"));
    cester_assert_printf_equal("\x1B[31mColor Red\x1B[0m");

    CESTER_RESET_STDOUT();
    printf("%s", CLINE_COLORSTR(CLINE_FG_GREEN, "Color Green"));
    cester_assert_printf_equal("\x1B[32mColor Green\x1B[0m");

    CESTER_RESET_STDOUT();
    printf("%s", CLINE_COLORSTR(CLINE_FG_BLUE, "Color Blue"));
    cester_assert_printf_equal("\x1B[34mColor Blue\x1B[0m");

    CESTER_RELEASE_STDOUT();
})

CESTER_TODO_TEST(printf_stream_output_bg, inst, {
    CESTER_CLAIM_STREAM(stdout);

    printf("%s", CLINE_COLORSTR(CLINE_BG_RED, "Red"));
    cester_assert_stream_content_equals(stdout, "\x1B[41mColor Red\x1B[0m");

    printf("%s", CLINE_COLORSTR(CLINE_BG_GREEN, "Color Green"));
    cester_assert_stream_content_equals(stdout, "\x1B[42mColor Green\x1B[0m");

    printf("%s", CLINE_COLORSTR(CLINE_BG_BLUE, "Color Blue"));
    cester_assert_stream_content_equals(stdout, "\x1B[44mColor Blue\x1B[0m");

    CESTER_RELEASE_STREAM(stdout);
})

CESTER_TODO_TEST(fprintf_stream_output, inst, {
    CESTER_ARREST_STREAM(stdout);

    fprintf(stdout, "%s", CLINE_COLORSTR(CLINE_FG_RED, "Red"));
    cester_assert_stream_content_equals(stdout, "\x1B[31mColor Red\x1B[0m");
    fprintf(stdout, "%s", CLINE_COLORSTR(CLINE_FG_RED, "Red"));
    cester_assert_stream_content_equals(stdout, "\x1B[31mColor Red\x1B[0m");

    CESTER_RELEASE_STREAM(stdout);
    /*fprintf(stdout, "%s %s %s %s\n", CLINE_COLORSTR(CLINE_FG_RED, "Red"), CLINE_COLORSTR(CLINE_FG_GREEN, "Green"), 
                            CLINE_COLORSTR(CLINE_FG_BLUE, "Blue"), CLINE_COLORSTR(CLINE_FG_YELLOW, "Yellow"));*/
})

CESTER_TODO_TEST(cline_fprintf_fg, inst, {
    /*cline_fprintf(stdout, "Colors: %s %s %s %s %d neat\n", CLINE_COLORSTR(CLINE_FG_RED, "Red"), CLINE_COLORSTR(CLINE_FG_GREEN, "Green"), 
                            CLINE_COLORSTR(CLINE_FG_BLUE, "Blue"), CLINE_COLORSTR(CLINE_FG_YELLOW, "Yellow"), 2020);
    cline_fprintf(stdout, "Hello %s\n", "World");*/
    printf("Hello World\n");
    fprintf(stdout, "%s %s %s %s End\n", CLINE_COLORSTR(CLINE_FG_RED, "Red"), CLINE_COLORSTR(CLINE_FG_GREEN, "Green"), 
                            CLINE_COLORSTR(CLINE_FG_BLUE, "Blue"), "\x1B[32mColor Green");
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

