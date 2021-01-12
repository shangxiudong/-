#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
struct timespec tout;
void print_hello();

void print_hello(void)
{
    pthread_mutex_lock(&lock);
    printf("hello world\n");
    sleep(2);
    pthread_mutex_unlock(&lock);

}


int main()
{
	tout.tv_nsec = 0;
	tout.tv_sec = 10;
	// pthread_mutex_init(&lock, NULL);
	pthread_t ntid, ntid2;
	void(*func)(void) = print_hello;
	pthread_create(&ntid, NULL, func, NULL);
	usleep(10000);
	printf("prepare another print\n");
	pthread_create(&ntid2, NULL, func, NULL);

	//必须加join，否则主线程退出，次线程都没跑完就退出了
	pthread_join(ntid, NULL);
    pthread_join(ntid2, NULL);
	return 0;
}
