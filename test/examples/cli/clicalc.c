/*!gcc -ansi -pedantic-errors {0} -I. -I../../../include/ -o out; ./out */

#include <exotic/cli/clinearg.h>
#include <exotic/cli/colorfulterm.h>

void fail_with_message(const char *message)
{
    cline_color_printff(CLINE_FG_RED, "Error: %s", message);
    cline_platform_printnl_if();
    exit(EXIT_FAILURE);
}

void calculate_numbers(xvector(int) *numbers, char operator)
{
    int total = 0;
    XFOREACH(const int number, numbers, {
        switch (operator) {
            case '+':
                total += number;
                break;
            case '-':
                total -= number;
                break;
            case '*':
                total *= number;
                break;
            case '/':
                total /= number;
                break;
            default:
                total += number;
                break;
        }
    })
}

int main(int argc, char **argv)
{
    ClineArgs *cline_args;

    if (init_cline_arg(&cline_args, "CliCalc") != XTD_OK) {
        return EXIT_FAILURE;
    }
    cline_args_add_argument(cline_args, "numbers", cline_args_list_callback, "The numbers to sum together", TRUE, NULL, NULL, 20);
    cline_args_add_flag(cline_args, "-op,--operator", cline_args_int_callback, "The operator to use for the provided numbers", TRUE, "+,-,*,/", NULL, 1);
    cline_args_add_flag(cline_args, "--outputfile", cline_args_file_callback, "The numbers to sum together", FALSE, NULL, NULL, 1);
    cline_args_parse(cline_args, argc, argv);

    return EXIT_SUCCESS;
}