#ifndef __MY_PRINT_H__
#define __MY_PRINT_H__
#define BUF_MAX_LEN 256
/*
*关于可变参数的宏定义
*/
#ifndef VA_PARAM
#define VA_PARAM
	typedef void* VA_list;
	#define INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))	/* int字节对齐 */
	#define VA_start(ap, v) (ap = (VA_list)&v + INTSIZEOF(v))       /* 令ap指向v的下一个元素*/
	#define VA_arg(ap, type) (*(type *)((ap += INTSIZEOF(type))-INTSIZEOF (type))) /*接_型递进指针并取值*/ 
	#define VA_end(ap) ((void)0)
#endif // VA_PARAM

int my_print(const char* fmt, ...);

#endif // __MY_PRINT_H__
