#include <stdio.h>
#include <stdlib.h>
#include "my_print.h"

int my_print(const char* fmt, ...); 
int my_print(const char* fmt, ...)
{
	va_list ptr = NULL;
	char c;
	VA_start(ptr, fmt);  //ptr points to the end_next of fmt
	while(*fmt != '\0')
	{
		c = *fmt++; 
		if(c !=	'%') {
			putchar(c);
		} else {
			switch(*fmt++)
			{
				case 's':
					printf("%s" ,VA_arg(ptr, char*)); 
					break; 
				case 'd':
					printf("%d", VA_arg(ptr, int)); 
					break; 
				case 'c':
					printf("%c", VA_arg(ptr, char));
					break; 
				case 'f':
					printf("%f", VA_arg(ptr, double)); 
					break; 
				default:
					putchar('\n');
					printf ("there is no such a type\n");
					break;
			}
		}
	}
	VA_end(ptr);
	return;
}
