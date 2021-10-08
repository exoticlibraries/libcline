/*!gcc -ansi -pedantic-errors {0} -I. -I../../../include/ -o out; ./out */

#include <exotic/cline/cliarg.h>
#include <exotic/cline/font_effect.h>

void fail_with_message(const char *message)
{
    cline_color_printff(CLINE_FG_RED, "Error: %s", message);
    printf("Error: %s", CLINE_TERM_COLOR(CLINE_FG_RED, message));

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
    xvector(int) *numbers;
    char operator;
    char *output_file;

    if (init_cline_arg(&cline_args, "CliCalc") != XTD_OK) {
        return EXIT_FAILURE;
    }
    cline_args_add_argument(cline_args, "numbers", numbers, "The numbers to sum together", TRUE, NULL, NULL, 20);
    cline_args_add_flag(cline_args, "-op,--operator", operator, "The operator to use for the provided numbers", TRUE, "+,-,*,/", NULL, 1);
    cline_args_add_flag(cline_args, "--outputfile", output_file, "The numbers to sum together", FALSE, NULL, NULL, 1);
    cline_args_parse(cline_args, argc, argv);

    calculate_numbers(numbers, operator);

    destroy_cline_arg(cline_args);
    return EXIT_SUCCESS;
}