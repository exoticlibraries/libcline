/*!gcc {0} -I. -I../../../include/ -o out; ./out */

#include <exotic/cline/font_effect.h>
#include <exotic/cline/cursor_nav.h>
#ifndef _WIN32
#include <unistd.h>
#else
#define sleep Sleep
#endif

void print_percentage()
{
    long percentage = -1;
    char *cleaner = CLINE_CN_MOVE_LEFT(20);
    while (percentage++ < 100 ) {
        printf("%sLoading %d%%...", cleaner, percentage);
        sleep(5);
    }
    printf("\n");
    free(cleaner);
}

void print_progressbar()
{
    long percentage = 0;
    unsigned progress_count = 25;
    char *cleaner = CLINE_CN_MOVE_LEFT(200);
    while (percentage++ < 100 ) {
        int width = (percentage + 1) / 4;
        printf("%s[", cleaner);
        for (unsigned int index = 0; index < progress_count; index++) {
            if (index <= width) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("]");
        sleep(1);
    }
    printf("\n");
    free(cleaner);
}

int main(int argc, char **argv)
{
    print_percentage();
    print_progressbar();
    cline_platform_printnl_if();
}
