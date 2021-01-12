#include <stdio.h>
#include <stdarg.h>

void my_print(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char c;
    while(*fmt != '\0')
	{
		c = *fmt++; 
		if(c !=	'%') {
			putchar(c);
		} else {
			switch(*fmt++)
			{
				case 's':
					printf("%s" ,va_arg(args, char*)); 
					break; 
				case 'd':
					printf("%d", va_arg(args, int)); 
					break; 
				case 'c':
					printf("%c", va_arg(args, char));
					break; 
				case 'f':
					printf("%f", va_arg(args, double)); 
					break; 
				default:
					break;
			}
		}
    }
    va_end(args);
    return;
}

void my_print2(const char *fmt, va_list args)
{
    char c;
    while(*fmt != '\0')
	{
		c = *fmt++; 
		if(c !=	'%') {
			putchar(c);
		} else {
			switch(*fmt++)
			{
				case 's':
					printf("%s" ,va_arg(args, char*)); 
					break; 
				case 'd':
					printf("%d", va_arg(args, int)); 
					break; 
				case 'c':
					printf("%c", va_arg(args, char));
					break; 
				case 'f':
					printf("%f", va_arg(args, double)); 
					break; 
				default:
					break;
			}
		}
    }
    return;
}

void cover_print(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    my_print2(fmt, args);
    va_end(args);
}

int main()
{
    cover_print("hello, %s %d\n", "thank you", 1314);
    return 0;
}