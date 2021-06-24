/*!gcc {0} -I. -I../include/ -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/cline/cliarg.h>

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))

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

CESTER_TEST(cline_arg_parse_add_argument, inst, {
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
    char **values;
    ClineArgs *cline_arg;
    XAllocator allocator;
    char *arguments1[] = {"--source", "test_clineargs_parse.c", "--help"};
    char *arguments2[] = {"--formats", "txt", "csv", "-h", "--formats", "yml"};

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK); add_options_to_ignore(cline_arg);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_argument(cline_arg, XTD_NULL, "--source", "The source file", "file", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_parse(cline_arg, 3, arguments1), XTD_OK);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "--source"), TRUE);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "--help"), TRUE);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "--help", XTD_NULL), 0);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "--source", XTD_NULL), 1);
    cester_assert_uint_gt(cline_arg_get_option_values(cline_arg, XTD_NULL, "--source", &values), 0);
    cester_assert_ptr_not_equal(values, XTD_NULL);
    cester_assert_str_equal_(values[0], "test_clineargs_parse.c");
    destroy_cline_arg(cline_arg);

    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK); add_options_to_ignore(cline_arg);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_cli_args_option(cline_arg, XTD_NULL, "--formats", XTD_NULL, "Supported file formats", 
                                                        XTD_NULL, "file-format", XTD_NULL, FALSE, FALSE, FALSE, FALSE, FALSE, 1, 3), XTD_OK);
    cester_assert_int_eq(cline_arg_parse(cline_arg, 6, arguments2), XTD_OK);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "-h"), TRUE);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "--help"), TRUE);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "--formats"), TRUE);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "-h", XTD_NULL), 0);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "--help", XTD_NULL), 0);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "--formats", &values), 3);
    cester_assert_ptr_not_equal(values, XTD_NULL);
    cester_assert_str_equal_(values[0], "txt");
    cester_assert_str_equal_(values[1], "csv");
    cester_assert_str_equal_(values[2], "yml");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_parse_add_property, inst, {
    char **values;
    ClineArgs *cline_arg;
    XAllocator allocator;
    char *arguments1[] = {"/I../include", "-I/usr/lib/", "-X"};
    char *arguments2[] = {"/I../include", "-I/usr/lib/", "-Xwin"};

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property(cline_arg, XTD_NULL, "-I<:>/I", "Specify the include path", "include_path", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property(cline_arg, XTD_NULL, "-X<:>/X", "Send option to the assembler", "option", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_parse(cline_arg, 3, arguments1), XTD_VALUE_NOT_FOUND_ERR);
    destroy_cline_arg(cline_arg);

    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property(cline_arg, XTD_NULL, "-I<:>/I", "Specify the include path", "include_path", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property(cline_arg, XTD_NULL, "-X<:>/X", "Send option to the assembler", "option", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_parse(cline_arg, 3, arguments2), XTD_OK);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "-h"), FALSE);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "-I"), TRUE);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "/I"), TRUE);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "/X"), TRUE);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "--help", XTD_NULL), 0);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "/I", XTD_NULL), 2);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "-I", &values), 2);
    cester_assert_ptr_not_equal(values, XTD_NULL);
    cester_assert_str_equal_(values[0], "../include");
    cester_assert_str_equal_(values[1], "/usr/lib/");
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "/X", XTD_NULL), 1);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "-X", &values), 1);
    cester_assert_ptr_not_equal(values, XTD_NULL);
    cester_assert_str_equal_(values[0], "win");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_parse_add_property_suffix, inst, {
    char **values;
    ClineArgs *cline_arg;
    XAllocator allocator;
    char *arguments1[] = {"../include/I", "/usr/lib/-I", "-X"};
    char *arguments2[] = {"../include/I", "/usr/lib/-I", "win-X"};

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property_suffix(cline_arg, XTD_NULL, "-I<:>/I", "Specify the include path", "include_path", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property_suffix(cline_arg, XTD_NULL, "-X<:>/X", "Send option to the assembler", "option", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_parse(cline_arg, 3, arguments1), XTD_VALUE_NOT_FOUND_ERR);
    destroy_cline_arg(cline_arg);

    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property_suffix(cline_arg, XTD_NULL, "-I<:>/I", "Specify the include path", "include_path", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property_suffix(cline_arg, XTD_NULL, "-X<:>/X", "Send option to the assembler", "option", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_parse(cline_arg, 3, arguments2), XTD_OK);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "-h"), FALSE);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "-I"), TRUE);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "/I"), TRUE);
    cester_assert_uint_eq(cline_arg_has_option(cline_arg, XTD_NULL, "/X"), TRUE);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "--help", XTD_NULL), 0);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "/I", XTD_NULL), 2);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "-I", &values), 2);
    cester_assert_ptr_not_equal(values, XTD_NULL);
    cester_assert_str_equal_(values[0], "../include");
    cester_assert_str_equal_(values[1], "/usr/lib/");
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "/X", XTD_NULL), 1);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "-X", &values), 1);
    cester_assert_ptr_not_equal(values, XTD_NULL);
    cester_assert_str_equal_(values[0], "win");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_parse_add_property_suffix_file_extension, inst, {
    char **values;
    ClineArgs *cline_arg;
    XAllocator allocator;
    char *arguments[] = {"test_cline.c", "xcommon.c", "fl.cpp", "cliarg.c", "stdio.cpp"};

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property_suffix(cline_arg, XTD_NULL, ".c", "C sourcefile", "c-source", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property_suffix(cline_arg, XTD_NULL, ".cpp", "C++ source file", "cpp-source", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_parse(cline_arg, 5, arguments), XTD_OK);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, "--help", XTD_NULL), 0);
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, ".cpp", &values), 2);
    cester_assert_ptr_not_equal(values, XTD_NULL);
    cester_assert_str_equal_(values[0], "fl");
    cester_assert_str_equal_(values[1], "stdio");
    cester_assert_uint_eq(cline_arg_get_option_values(cline_arg, XTD_NULL, ".c", &values), 3);
    cester_assert_ptr_not_equal(values, XTD_NULL);
    cester_assert_str_equal_(values[0], "test_cline");
    cester_assert_str_equal_(values[1], "xcommon");
    cester_assert_str_equal_(values[2], "cliarg");

    destroy_cline_arg(cline_arg);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(3);
)


