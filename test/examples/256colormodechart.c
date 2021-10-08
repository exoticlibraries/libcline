/*!gcc {0} -I. -I../../../include/ -o out; ./out */

#include <exotic/cline/font_effect.h>

void print_first_15()
{
    int color_mode = 0;    
    printf("\t\t\t\tStandard colors\t\t\t\t\t\t\t\t\t\t\tHigh-intensity colors\n\n");
    while (color_mode <= 15 ) {
        unsigned foreground = color_mode < 7 ? CLINE_FE_FOREGROUND_WHITE : CLINE_FE_FOREGROUND_BLACK;
        printf("%s     %d    %s", CLINE_FE(CLINE_FE_BACKGROUND_MODE(color_mode), foreground), color_mode, CLINE_FE(CLINE_FE_RESET));
        if (color_mode == 7) {
            printf("              ");
        }
        color_mode++;
    }
    printf("\n");
}

void print_next_216()
{
    int color_mode = 16;
    printf("\n\t\t\t\t\t\t\t\t\t\t  216 colors\n\n");
    while (color_mode <= 231 ) {
        unsigned foreground = color_mode <= 33 || (color_mode >= 52 && color_mode <= 69) || (color_mode >= 88 && color_mode <= 105) || 
                                (color_mode >= 124 && color_mode <= 141) || (color_mode >= 160 && color_mode <= 177) || 
                                (color_mode >= 196 && color_mode <= 213)
                             ? CLINE_FE_FOREGROUND_WHITE : CLINE_FE_FOREGROUND_BLACK;
        printf("%s %d %s%s", CLINE_FE(CLINE_FE_BACKGROUND_MODE(color_mode), foreground), color_mode, (color_mode < 100? " " : ""), CLINE_FE(CLINE_FE_RESET));
        if (color_mode == 51 || color_mode == 87 || color_mode == 123 || color_mode == 159 || color_mode == 195 || color_mode == 231) {
            printf("\n");
        }
        color_mode++;
    }
    printf("\n");
}

void print_grayscale_colors()
{
    int color_mode = 232;
    printf("\n\t\t\t\t\t\t\t\t\t\tGrayscale colors\n\n\t    ");
    while (color_mode <= 255 ) {
        unsigned foreground = color_mode <= 243 ? CLINE_FE_FOREGROUND_WHITE : CLINE_FE_FOREGROUND_BLACK;
        printf("%s  %d  %s", CLINE_FE(CLINE_FE_BACKGROUND_MODE(color_mode), foreground), color_mode, CLINE_FE(CLINE_FE_RESET));
        color_mode++;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int color_mode = 16;

    printf("\t\t\t\t\t\t\t\t\t%s\n\n", CLINE_FE_STR("256 Color Mode - libcline - Adewale Azeez", CLINE_FE_UNDERLINE));
    print_first_15();
    print_next_216();
    print_grayscale_colors();
    printf("\n");

    cline_platform_printnl_if();
}