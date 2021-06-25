/*!gcc {0} -I. -I../include/ -I../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/cline/cliarg.h>

#define cester_assert_str_equal_(x,y) cester_assert_true(xstring_cstr_equals(x,y))

CESTER_BODY(
    bool compare_flag_luffy_gears(const char *entry_key, const char *flag) {
        return xstring_cstr_equals(entry_key, "-bounce-man") || 
            xstring_cstr_equals(entry_key, "snake-man") || 
            xstring_cstr_equals(entry_key, "--gear-second");
    }
)

CESTER_TEST(cline_arg_get_name, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_str_equal_(cline_arg_get_name(cline_arg), "CliCalc");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_get_description, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_ptr_equal(cline_arg_get_description(cline_arg), XTD_NULL);
    cester_assert_int_eq(cline_arg_set_description(cline_arg, "A simple command line calculator"), XTD_OK);
    cester_assert_str_equal_(cline_arg_get_description(cline_arg), "A simple command line calculator");
    
    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_set_epilog, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_ptr_equal(cline_arg_get_epilog(cline_arg), XTD_NULL);
    cester_assert_int_eq(cline_arg_set_epilog(cline_arg, "usage: CliCalc [-h] (--number | --letters)"), XTD_OK);
    cester_assert_str_equal_(cline_arg_get_epilog(cline_arg), "usage: CliCalc [-h] (--number | --letters)");
    
    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_set_usage, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_ptr_equal(cline_arg_get_usage(cline_arg), XTD_NULL);
    cester_assert_int_eq(cline_arg_set_usage(cline_arg, "Visit https://exoticlibraries.github.io/ for more"), XTD_OK);
    cester_assert_str_equal_(cline_arg_get_usage(cline_arg), "Visit https://exoticlibraries.github.io/ for more");
    
    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_add_option, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-v<:>--version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "--verbose", "Be extra verbose", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_DUPLICATE_ERR);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "--verbose", "Be extra verbose", FALSE), XTD_DUPLICATE_ERR);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_get_arg_option, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;
    ClineArgsOption cline_arg_option;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-v<:>--version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "--verbose", "Be extra verbose", FALSE), XTD_OK);
    
    cester_assert_int_eq(cline_arg_get_arg_option(cline_arg, XTD_NULL, "--version", &cline_arg_option), TRUE);
    cester_assert_str_equal_(cline_arg_option->splited_option_keys[0], "-v");
    cester_assert_str_equal_(cline_arg_option->splited_option_keys[1], "--version");
    cester_assert_str_equal_(cline_arg_option->description, "Print the version information and exit");
    cester_assert_int_eq(cline_arg_get_arg_option(cline_arg, XTD_NULL, "--verbose", &cline_arg_option), TRUE);
    cester_assert_str_equal_(cline_arg_option->splited_option_keys[0], "--verbose");
    cester_assert_str_equal_(cline_arg_option->description, "Be extra verbose");
    cester_assert_int_eq(cline_arg_get_arg_option(cline_arg, XTD_NULL, "--debug", &cline_arg_option), FALSE);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_contains_option, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-v<:>--version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "--verbose", "Be extra verbose", FALSE), XTD_OK);
    
    cester_assert_uint_eq(cline_arg_contains_option(cline_arg, XTD_NULL, "--verbose"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_option(cline_arg, XTD_NULL, "-h<:>--help"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_option(cline_arg, XTD_NULL, "-v<:>--version"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_option(cline_arg, XTD_NULL, "-v<:>--version"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_option(cline_arg, XTD_NULL, "-v"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_option(cline_arg, XTD_NULL, "-f"), FALSE);
    cester_assert_uint_eq(cline_arg_contains_option(cline_arg, XTD_NULL, "--version"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_option(cline_arg, XTD_NULL, "-v"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_option(cline_arg, XTD_NULL, "--force"), FALSE);
    cester_assert_uint_eq(cline_arg_contains_option(cline_arg, XTD_NULL, "--help"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_option(cline_arg, XTD_NULL, "-h"), TRUE);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_contains_main_option, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-v<:>--version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "--verbose", "Be extra verbose", FALSE), XTD_OK);
    
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "--verbose"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "-h<:>--help"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "-v<:>--version"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "-v<:>--version"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "-v"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "-f"), FALSE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "--version"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "-v"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "--force"), FALSE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "--help"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "-h"), TRUE);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_set_option_delimiter, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_str_equal_(cline_arg_get_option_delimiter(cline_arg), "<:>");
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-v-###---version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "--help"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "-h"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "--version"), FALSE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "-v"), FALSE);
    destroy_cline_arg(cline_arg);

    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_option_delimiter(cline_arg, "###"), XTD_OK);
    cester_assert_str_equal_(cline_arg_get_option_delimiter(cline_arg), "###");
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-v###--version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "--help"), FALSE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "-h"), FALSE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "--version"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_main_option(cline_arg, "-v"), TRUE);
    
    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_add_argument, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_argument(cline_arg, XTD_NULL, "--help", "Print this help message", "section", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_argument(cline_arg, XTD_NULL, "--source", "The source file", "file", TRUE), XTD_OK);
    cester_assert_uint_eq(cline_arg_contains_option(cline_arg, XTD_NULL, "--help"), TRUE);
    cester_assert_uint_eq(cline_arg_contains_option(cline_arg, XTD_NULL, "--source"), TRUE);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_add_property, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;
    ClineArgsOption cline_arg_option;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property(cline_arg, XTD_NULL, "-I<:>/I", "Specify the include path", "include_path", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property(cline_arg, XTD_NULL, "-X<:>/X", "Send option to the assembler", "option", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_get_arg_option(cline_arg, XTD_NULL, "-I", &cline_arg_option), TRUE);
    cester_assert_int_eq(cline_arg_option->is_prefix, TRUE);
    cester_assert_int_eq(cline_arg_get_arg_option(cline_arg, XTD_NULL, "/X", &cline_arg_option), TRUE);
    cester_assert_int_eq(cline_arg_option->is_prefix, TRUE);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_add_property_suffix, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;
    ClineArgsOption cline_arg_option;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property_suffix(cline_arg, XTD_NULL, "-I<:>/I", "Specify the include path", "include_path", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property_suffix(cline_arg, XTD_NULL, "-X<:>/X", "Send option to the assembler", "option", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_get_arg_option(cline_arg, XTD_NULL, "-I", &cline_arg_option), TRUE);
    cester_assert_int_eq(cline_arg_option->is_suffix, TRUE);
    cester_assert_int_eq(cline_arg_get_arg_option(cline_arg, XTD_NULL, "/X", &cline_arg_option), TRUE);
    cester_assert_int_eq(cline_arg_option->is_suffix, TRUE);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_add_choice, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_choice(cline_arg, XTD_NULL, "--user", "Specify the include path", "Student|Teacher|Admin", FALSE), XTD_OK);
    /*cester_assert_int_eq(cline_arg_add_property_suffix(cline_arg, XTD_NULL, "-X<:>/X", "Send option to the assembler", "option", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_get_arg_option(cline_arg, XTD_NULL, "-I", &cline_arg_option), TRUE);
    cester_assert_int_eq(cline_arg_option->is_suffix, TRUE);
    cester_assert_int_eq(cline_arg_get_arg_option(cline_arg, XTD_NULL, "/X", &cline_arg_option), TRUE);
    cester_assert_int_eq(cline_arg_option->is_suffix, TRUE);*/

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_add_ignored, inst, {
    ClineArgs *cline_arg;
    XAllocator allocator;
    ClineArgsOption cline_arg_option;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "--cester", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "--cline", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_get_arg_option(cline_arg, XTD_NULL, "--cester", &cline_arg_option), TRUE);
    cester_assert_int_eq(cline_arg_option->ignored, TRUE);
    cester_assert_int_eq(cline_arg_get_arg_option(cline_arg, XTD_NULL, "--cline", &cline_arg_option), TRUE);
    cester_assert_int_eq(cline_arg_option->ignored, TRUE);

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_find_like_arg_options, inst, {
    size_t fount_count;
    ClineArgs *cline_arg;
    XAllocator allocator;
    const int max_similar_count = 4;
    char *similar_options[max_similar_count];

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "apple", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "-better", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "-bet", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "--verbose", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "--keep", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "--clone", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "--cone", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "--cleanup", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "--close", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "--gear-second", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "-bounce-man", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_ignored(cline_arg, "snake-man", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_find_like_arg_options(cline_arg, "alabaster", similar_options, max_similar_count, XTD_NULL), 0);
    cester_assert_int_eq(cline_arg_find_like_arg_options(cline_arg, "grand-line", similar_options, max_similar_count, XTD_NULL), 0);
    fount_count = cline_arg_find_like_arg_options(cline_arg, "kee", similar_options, max_similar_count, XTD_NULL);
    cester_assert_int_eq(fount_count, 1);
    cester_assert_str_equal_(similar_options[0], "--keep");
    fount_count = cline_arg_find_like_arg_options(cline_arg, "--", similar_options, max_similar_count, XTD_NULL);
    cester_assert_int_eq(fount_count, max_similar_count);
    cester_assert_str_equal_(similar_options[0], "--cone");
    cester_assert_str_equal_(similar_options[1], "--close");
    cester_assert_str_equal_(similar_options[2], "--cleanup");
    cester_assert_str_equal_(similar_options[3], "--gear-second");
    fount_count = cline_arg_find_like_arg_options(cline_arg, "cl", similar_options, max_similar_count, XTD_NULL);
    cester_assert_int_eq(fount_count, 3);
    cester_assert_str_equal_(similar_options[0], "--close");
    cester_assert_str_equal_(similar_options[1], "--cleanup");
    cester_assert_str_equal_(similar_options[2], "--clone");
    fount_count = cline_arg_find_like_arg_options(cline_arg, "--cloud", similar_options, max_similar_count, XTD_NULL);
    cester_assert_int_eq(fount_count, 2);
    cester_assert_str_equal_(similar_options[0], "--close");
    cester_assert_str_equal_(similar_options[1], "--clone");
    fount_count = cline_arg_find_like_arg_options(cline_arg, "apply", similar_options, max_similar_count, XTD_NULL);
    cester_assert_int_eq(fount_count, 1);
    cester_assert_str_equal_(similar_options[0], "apple");
    fount_count = cline_arg_find_like_arg_options(cline_arg, "-bethoven", similar_options, max_similar_count, XTD_NULL);
    cester_assert_int_eq(fount_count, 2);
    cester_assert_str_equal_(similar_options[0], "-better");
    cester_assert_str_equal_(similar_options[1], "-bet");
    fount_count = cline_arg_find_like_arg_options(cline_arg, "--gear-?", similar_options, max_similar_count, compare_flag_luffy_gears);
    cester_assert_int_eq(fount_count, 3);
    cester_assert_str_equal_(similar_options[0], "-bounce-man");
    cester_assert_str_equal_(similar_options[1], "snake-man");
    cester_assert_str_equal_(similar_options[2], "--gear-second");

})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(3);
)
