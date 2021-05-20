/*!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <stdio.h>

void spaces(int count)
{
    int s;

    for(s=0;s<count;s++)
        putchar(' ');
}

int main()
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