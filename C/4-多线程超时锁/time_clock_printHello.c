#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void print_hello();

void print_hello(void)
{
    struct timespec tout;
    clock_gettime(CLOCK_REALTIME, &tout);
    tout.tv_sec += 2;  //max wait time = 2
    // wait 10 second while mutex is locked
    int err = pthread_mutex_timedlock(&lock, &tout);
    if (err == 0)
        printf("hello world\n");
    else
        printf("can not print hello world\n");
    sleep(3);
    pthread_mutex_unlock(&lock);
}


int main()
{
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