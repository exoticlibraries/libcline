/*!clang {0} -I. -I../include/ -I../../../include/ -o out; ./out */

#include <exotic/cester.h>
#include <exotic/cline/cliarg.h>

CESTER_BODY(
    
)

CESTER_TEST(cline_arg_help_section_name_and_description, inst, {
    char *help_text;
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_description(cline_arg, "A simple command line calculator"), XTD_OK);
    cester_assert_int_eq(cline_arg_section_help(cline_arg, XTD_NULL, XTD_NULL, &help_text), XTD_OK);
    cester_assert_str_eq(help_text, "usage: CliCalc\n\nA simple command line calculator\n");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_help_section_usage, inst, {
    char *help_text;
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_usage(cline_arg, "usage: CliCalc [-h] (--number | --letters)"), XTD_OK);
    cester_assert_int_eq(cline_arg_section_help(cline_arg, XTD_NULL, XTD_NULL, &help_text), XTD_OK);
    cester_assert_str_eq(help_text, "usage: CliCalc [-h] (--number | --letters)\n\n");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_help_section_epilog, inst, {
    char *help_text;
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_epilog(cline_arg, "Visit https://exoticlibraries.github.io/ for more"), XTD_OK);
    cester_assert_int_eq(cline_arg_section_help(cline_arg, XTD_NULL, XTD_NULL, &help_text), XTD_OK);
    cester_assert_str_eq(help_text, "usage: CliCalc\n\n\nVisit https://exoticlibraries.github.io/ for more\n");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_help_section_description_usage_epilog, inst, {
    char *help_text;
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_usage(cline_arg, "usage: CliCalc [-h] (--number | --letters)"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_description(cline_arg, "A simple command line calculator"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_epilog(cline_arg, "Visit https://exoticlibraries.github.io/ for more"), XTD_OK);
    cester_assert_int_eq(cline_arg_section_help(cline_arg, XTD_NULL, XTD_NULL, &help_text), XTD_OK);
    cester_assert_str_eq(help_text, "usage: CliCalc [-h] (--number | --letters)\n\nA simple command line calculator\n\nVisit https://exoticlibraries.github.io/ for more\n");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_help_name_and_description, inst, {
    char *help_text;
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_usage(cline_arg, "usage: CliCalc [-h] (--number | --letters)"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_description(cline_arg, "A simple command line calculator"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_epilog(cline_arg, "Visit https://exoticlibraries.github.io/ for more"), XTD_OK);
    cester_assert_int_eq(cline_arg_help(cline_arg, XTD_NULL, XTD_NULL, &help_text), XTD_OK);
    cester_assert_str_eq(help_text, "usage: CliCalc [-h] (--number | --letters)\n\nA simple command line calculator\n\nVisit https://exoticlibraries.github.io/ for more\n\n");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_help_description_and_options, inst, {
    char *help_text;
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_description(cline_arg, "A simple command line calculator"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "--version", "Print the version information and exit", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "--verbose", "Be extra verbose", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_section_help(cline_arg, XTD_NULL, XTD_NULL, &help_text), XTD_OK);
    cester_assert_str_eq(help_text, "usage: CliCalc [-h|--help] [--verbose] [--version]\n"
    "\n"
    "A simple command line calculator\n"
    "\n"
    "  -h, --help            Print this help message\n"
    "  --verbose             Be extra verbose\n"
    "  --version             Print the version information and exit\n");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_help_description_and_arguments, inst, {
    char *help_text;
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_description(cline_arg, "A simple command line calculator"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_argument(cline_arg, XTD_NULL, "--help", "Print this help message", "section", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_argument(cline_arg, XTD_NULL, "--source", "The source file", "file", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_section_help(cline_arg, XTD_NULL, XTD_NULL, &help_text), XTD_OK);
    cester_assert_str_eq(help_text, "usage: CliCalc --source <file> [--help <section>]\n"
    "\n"
    "A simple command line calculator\n"
    "\n"
    "  --source <file>       The source file\n"
    "  --help <section>      Print this help message\n");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_help_description_and_properties, inst, {
    char *help_text;
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_description(cline_arg, "A simple command line calculator"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property(cline_arg, XTD_NULL, "-I<:>/I", "Specify the include path", "include_path", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property(cline_arg, XTD_NULL, "-X", "Send option to the assembler", "option", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_section_help(cline_arg, XTD_NULL, XTD_NULL, &help_text), XTD_OK);
    cester_assert_str_eq(help_text, "usage: CliCalc [-X<option> ...] [-I<include_path>|/I<include_path> ...]\n"
    "\n"
    "A simple command line calculator\n"
    "\n"
    "  -X<option> ...        Send option to the assembler\n"
    "  -I<include_path>, /I<include_path> ... Specify the include path\n");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_help_description_and_properties_suffix, inst, {
    char *help_text;
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_description(cline_arg, "A simple command line calculator"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property_suffix(cline_arg, XTD_NULL, ".c", "C sourcefile", "source", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_property_suffix(cline_arg, XTD_NULL, ".cpp", "C++ source file", "source", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_section_help(cline_arg, XTD_NULL, XTD_NULL, &help_text), XTD_OK);
    cester_assert_str_eq(help_text, "usage: CliCalc [<source>.cpp ...] [<source>.c ...]\n"
    "\n"
    "A simple command line calculator\n"
    "\n"
    "  <source>.cpp ...      C++ source file\n"
    "  <source>.c ...        C sourcefile\n");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_help_description_and_choices, inst, {
    char *help_text;
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_description(cline_arg, "A simple command line calculator"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_choice(cline_arg, XTD_NULL, "-u<:>--user", "Specify the include path", "Student|Teacher|Admin|Executive", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_choice(cline_arg, XTD_NULL, "--door<:>--ilekun", "Send option to the assembler", "Open|Close", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_section_help(cline_arg, XTD_NULL, XTD_NULL, &help_text), XTD_OK);
    cester_assert_str_eq(help_text, "usage: CliCalc [-u|--user] [--door|--ilekun]\n"
    "\n"
    "A simple command line calculator\n"
    "\n"
    "  -u, --user            Specify the include path\n"
    "  --door, --ilekun      Send option to the assembler\n");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_help_description_and_options_mandatory, inst, {
    char *help_text;
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_description(cline_arg, "A simple command line calculator"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "-h<:>--help", "Print this help message", FALSE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "--version", "Print the version information and exit", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "--verbose", "Be extra verbose", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_section_help(cline_arg, XTD_NULL, XTD_NULL, &help_text), XTD_OK);
    cester_assert_str_eq(help_text, "usage: CliCalc [-h|--help] --verbose --version\n"
    "\n"
    "A simple command line calculator\n"
    "\n"
    "  -h, --help            Print this help message\n"
    "  --verbose             Be extra verbose\n"
    "  --version             Print the version information and exit\n");

    destroy_cline_arg(cline_arg);
})

CESTER_TEST(cline_arg_help_description_and_others, inst, {
    char *help_text;
    ClineArgs *cline_arg;
    XAllocator allocator;

    init_xallocator(&allocator);
    cester_assert_int_eq(init_cline_arg(&allocator, &cline_arg, "CliCalc"), XTD_OK);
    cester_assert_int_eq(cline_arg_set_description(cline_arg, "A simple command line calculator"), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "--version", "Print the version information and exit", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_option(cline_arg, XTD_NULL, "--verbose", "Be extra verbose", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_add_cli_args_option(cline_arg, XTD_NULL, "--help", XTD_NULL, "Display help information for specific section", 
                                                        XTD_NULL, "section", "=", FALSE, FALSE, FALSE, FALSE, FALSE, 1, 1), XTD_OK);
    cester_assert_int_eq(cline_arg_collect_orphans(cline_arg, "source", TRUE), XTD_OK);
    cester_assert_int_eq(cline_arg_section_help(cline_arg, XTD_NULL, XTD_NULL, &help_text), XTD_OK);
    printf("%s", help_text);
    /*cester_assert_str_eq(help_text, "usage: CliCalc [-h] [--help <section>] --verbose --version\n"
    "\n"
    "A simple command line calculator\n"
    "\n"
    "  -h, --help            Print this help message\n"
    "  --verbose             Be extra verbose\n"
    "  --version             Print the version information and exit\n");*/

    destroy_cline_arg(cline_arg);
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(3);
)


