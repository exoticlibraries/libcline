/*!gcc {0} -I. -I../include/ -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/cline/cliarg.h>

CESTER_BODY(
    void add_options_to_ignore(ClineArgs *cline_arg) {
        cline_arg_add_ignored(cline_arg, "--cester", TRUE);
    }
)

CESTER_TEST(cline_arg_parse_wrong_params, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_parse(cline_arg, 0, XTD_NULL), XTD_INVALID_PARAMETER);
    cester_assert_int_eq(cline_arg_parse(XTD_NULL, 0, inst->argv), XTD_INVALID_PARAMETER);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_parse_invalid_param, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_parse(cline_arg, inst->argc, inst->argv), XTD_INVALID_PARAMETER_FOUND_ERR);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_parse_in_range_basic_option, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    add_options_to_ignore(cline_arg);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_parse_in_range(cline_arg, 1, inst->argc, inst->argv), XTD_OK);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_parse_add_option_basic_option, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;
    char *arguments[] = {"--help", "-v"};

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    add_options_to_ignore(cline_arg);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-v<:>--version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_parse_in_range(cline_arg, 0, 2, arguments), XTD_OK);

    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "-h"), TRUE);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_parse_add_argument_1, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;
    char *arguments1[] = {"--source"};
    char *arguments2[] = {"--source test_clineargs_parse.c"};
    char *arguments3[] = {"--source", "test_clineargs_parse.c", "--help"};

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK); add_options_to_ignore(cline_arg);
    cester_assert_int_eq(cline_arg_add_argument(cline_arg, XTD_NULL, "--source", "The source file", "file", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_parse(cline_arg, 1, arguments1), XTD_VALUE_NOT_FOUND_ERR);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "--source"), TRUE);
    destroy_cline_arg(cline_arg);
    
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK); add_options_to_ignore(cline_arg);
    cester_assert_int_eq(cline_arg_add_argument(cline_arg, XTD_NULL, "--source", "The source file", "file", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_parse(cline_arg, 1, arguments2), XTD_INVALID_PARAMETER_FOUND_ERR);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "--source"), FALSE);
    destroy_cline_arg(cline_arg);

    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK); add_options_to_ignore(cline_arg);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_argument(cline_arg, XTD_NULL, "--source", "The source file", "file", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_parse(cline_arg, 3, arguments3), XTD_OK);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "--source"), TRUE);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "--help"), TRUE);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_parse_add_argument_values, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;
    char *arguments1[] = {"--source", "test_clineargs_parse.c", "--help"};

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK); add_options_to_ignore(cline_arg);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_argument(cline_arg, XTD_NULL, "--source", "The source file", "file", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_parse(cline_arg, 3, arguments1), XTD_OK);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "--source"), TRUE);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "--help"), TRUE);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "--help", XTD_NULL), 0);
    //cester_assert_uint_gt(cline_arg_get_option_values(cline_arg, XTD_NULL, "--source"), 0);
    //cester_assert_uint_gt(cline_arg_get_option_values(cline_arg, XTD_NULL, "--source"), 0);

    destroy_cline_arg(cline_arg);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(3);
)


