/*!gcc {0} -I. -I../include/ -o out -Wno-int-conversion; ./out --cester-verbose */

#include <stdio.h>
#include <stdlib.h>
#include <exotic/xtd/xvector.h>
#include <exotic/metaref.h>

#define EXECUTE_OR_FAIL(func) if (func != XTD_OK) goto fails;
typedef char* str;
SETUP_XVECTOR_FOR(str)

void to_string(int number) {
	
}

int main() {
	xvector(str) *numbers;

	EXECUTE_OR_FAIL(xvector_new(str)(&numbers))
	EXECUTE_OR_FAIL(xvector_add(str)(numbers, "1"))
	EXECUTE_OR_FAIL(xvector_add(str)(numbers, "2"))
	EXECUTE_OR_FAIL(xvector_add(str)(numbers, "3"))
	EXECUTE_OR_FAIL(xvector_add(str)(numbers, "4"))
	CLINE_PRINT_XVECTOR(stdout, str, numbers);

	xvector_destroy(numbers);
	return 0;
	fails:
		printf("Error");
		return 1;
}

void spaces(int count)
{
    int s;

    for(s=0;s<count;s++)
        putchar(' ');
}

int main1()
{
    int x;

    puts("i\\/\\/\\i");
    for(x=0;x<2;x++)
    {
        putchar('|');
        spaces(5);
        puts("|");
    }
    puts("| (O)(O)");
    putchar('C');
    spaces(5);
    printf("_)\n|");
    spaces(2);
    printf(",___|\n|");
    spaces(5);
    printf("/\n|");
    spaces(3);
    puts("/");

    return(0);
}
