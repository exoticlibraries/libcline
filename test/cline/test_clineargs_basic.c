/*!gcc {0} -I. -I../include/ -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/cline/cliarg.h>

CESTER_TEST(cline_arg_get_name, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_str_equal(cline_arg_get_name(cline_arg), "CliCalc");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_get_description, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_ptr_equal(cline_arg_get_description(cline_arg), XTD_NULL);
    cester_assert_int_eq(cline_args_set_description(cline_arg, "A simple command line calculator"), XTD_OK);
    cester_assert_str_equal(cline_arg_get_description(cline_arg), "A simple command line calculator");
    
    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_args_set_epilog, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_ptr_equal(cline_arg_get_epilog(cline_arg), XTD_NULL);
    cester_assert_int_eq(cline_args_set_epilog(cline_arg, "usage: CliCalc [-h] (--number | --letters)"), XTD_OK);
    cester_assert_str_equal(cline_arg_get_epilog(cline_arg), "usage: CliCalc [-h] (--number | --letters)");
    
    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_args_set_usage, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_ptr_equal(cline_arg_get_usage(cline_arg), XTD_NULL);
    cester_assert_int_eq(cline_args_set_usage(cline_arg, "Visit https://exoticlibraries.github.io/ for more"), XTD_OK);
    cester_assert_str_equal(cline_arg_get_usage(cline_arg), "Visit https://exoticlibraries.github.io/ for more");
    
    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_args_add_option, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "-v<:>--version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "--verbose", "Be extra verbose", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_DUPLICATE_ERR);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "--verbose", "Be extra verbose", FALSE), XTD_DUPLICATE_ERR);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_args_get_args_option, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;
    ClineArgsOption cline_arg_option;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "-v<:>--version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "--verbose", "Be extra verbose", FALSE), XTD_OK);
    
    cester_assert_int_eq(cline_args_get_args_option(cline_arg, XTD_NULL, "--version", &cline_arg_option), TRUE);
    cester_assert_str_equal(cline_arg_option.splited_option_keys[0], "-v");
    cester_assert_str_equal(cline_arg_option.splited_option_keys[1], "--version");
    cester_assert_str_equal(cline_arg_option.description, "Print the version information and exit");
    cester_assert_int_eq(cline_args_get_args_option(cline_arg, XTD_NULL, "--verbose", &cline_arg_option), TRUE);
    cester_assert_str_equal(cline_arg_option.splited_option_keys[0], "--verbose");
    cester_assert_str_equal(cline_arg_option.description, "Be extra verbose");
    cester_assert_int_eq(cline_args_get_args_option(cline_arg, XTD_NULL, "--debug", &cline_arg_option), FALSE);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_args_contains_option, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "-v<:>--version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "--verbose", "Be extra verbose", FALSE), XTD_OK);
    
    cester_assert_uint_eq(cline_args_contains_option(cline_arg, XTD_NULL, "--verbose"), TRUE);
    cester_assert_uint_eq(cline_args_contains_option(cline_arg, XTD_NULL, "-h<:>--help"), TRUE);
    cester_assert_uint_eq(cline_args_contains_option(cline_arg, XTD_NULL, "-v<:>--version"), TRUE);
    cester_assert_uint_eq(cline_args_contains_option(cline_arg, XTD_NULL, "-v<:>--version"), TRUE);
    cester_assert_uint_eq(cline_args_contains_option(cline_arg, XTD_NULL, "-v"), TRUE);
    cester_assert_uint_eq(cline_args_contains_option(cline_arg, XTD_NULL, "-f"), FALSE);
    cester_assert_uint_eq(cline_args_contains_option(cline_arg, XTD_NULL, "--version"), TRUE);
    cester_assert_uint_eq(cline_args_contains_option(cline_arg, XTD_NULL, "-v"), TRUE);
    cester_assert_uint_eq(cline_args_contains_option(cline_arg, XTD_NULL, "--force"), FALSE);
    cester_assert_uint_eq(cline_args_contains_option(cline_arg, XTD_NULL, "--help"), TRUE);
    cester_assert_uint_eq(cline_args_contains_option(cline_arg, XTD_NULL, "-h"), TRUE);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_args_contains_main_option, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "-v<:>--version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "--verbose", "Be extra verbose", FALSE), XTD_OK);
    
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "--verbose"), TRUE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "-h<:>--help"), TRUE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "-v<:>--version"), TRUE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "-v<:>--version"), TRUE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "-v"), TRUE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "-f"), FALSE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "--version"), TRUE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "-v"), TRUE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "--force"), FALSE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "--help"), TRUE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "-h"), TRUE);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_args_set_option_delimiter, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_str_equal(cline_arg_get_option_delimiter(cline_arg), "<:>");
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "-v-###---version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "--help"), TRUE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "-h"), TRUE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "--version"), FALSE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "-v"), FALSE);
    destroy_cline_arg(cline_arg);

    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_args_set_option_delimiter(cline_arg, "###"), XTD_OK);
    cester_assert_str_equal(cline_arg_get_option_delimiter(cline_arg), "###");
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_add_option(cline_arg, XTD_NULL, "-v###--version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "--help"), FALSE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "-h"), FALSE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "--version"), TRUE);
    cester_assert_uint_eq(cline_args_contains_main_option(cline_arg, "-v"), TRUE);
    
    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_args_add_argument, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_args_add_argument(cline_arg, XTD_NULL, "--help", "Print this help message", "section", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_add_argument(cline_arg, XTD_NULL, "--source", "The source file", "file", TRUE), XTD_OK);
    cester_assert_uint_eq(cline_args_contains_option(cline_arg, XTD_NULL, "--help"), TRUE);
    cester_assert_uint_eq(cline_args_contains_option(cline_arg, XTD_NULL, "--source"), TRUE);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_args_add_property, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;
    ClineArgsOption cline_arg_option;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_args_add_property(cline_arg, XTD_NULL, "-I<:>/I", "Specify the include path", "include_path", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_add_property(cline_arg, XTD_NULL, "-X<:>/X", "Send option to the assembler", "option", FALSE), XTD_OK);
    cester_assert_int_eq(cline_args_get_args_option(cline_arg, XTD_NULL, "-I", &cline_arg_option), TRUE);
    cester_assert_int_eq(cline_arg_option.is_prefix, TRUE);
    cester_assert_int_eq(cline_args_get_args_option(cline_arg, XTD_NULL, "/X", &cline_arg_option), TRUE);
    cester_assert_int_eq(cline_arg_option.is_prefix, TRUE);

    destroy_cline_arg(cline_arg);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(3);
)
