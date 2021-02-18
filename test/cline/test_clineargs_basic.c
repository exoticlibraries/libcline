/*!gcc -ansi -pedantic-errors {0} -I. -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/cline/cliarg.h>

/*CESTER_TEST(cline_arg_name, inst, {
    ClineArgs *cline_arg;

    cester_assert_int_eq(init_cline_arg(&cline_arg, "CliCalc"), XTD_OK);
    cester_assert_str_equal(cline_arg_name(cline_arg), "CliCalc");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_description, inst, {
    ClineArgs *cline_arg;

    cester_assert_int_eq(init_cline_arg(&cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_args_set_description(cline_arg, "A simple command line calculator"), XTD_OK);
    cester_assert_str_equal(cline_arg_description(cline_arg), "A simple command line calculator");
    
    destroy_cline_arg(cline_arg);
})*/

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(3);
)
