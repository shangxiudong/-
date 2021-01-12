#include <stdio.h>
#include "my_print.h"

int main()
{
	char s[] = "sad";
	my_print("this is a %s story, told %d girls kidnap a boy\n", s, 2);
	return 0;
}