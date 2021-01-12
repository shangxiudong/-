#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h> //mmap函数的必要头文件
#include <sys/stat.h> // struct stat 需要的头文件
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <pthread.h>

#define MAX_LEN 128

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct _thread_param thread_param;
struct _thread_param {
    char *path;
    char *text;
};

void *my_mmap_write(void *arg)
{
    if(arg == NULL) return NULL;
    thread_param *param = (thread_param *)arg;
    char *path = param->path;
    char *text = param->text;
    int fd;
    if( (fd = open(path, O_RDWR)) < 0) {
        perror("open\n");
        return NULL;
    }

    struct stat sb;
    if(fstat(fd, &sb) == -1)  perror("fstat");
    char *mmapped;
    if( (mmapped = mmap(NULL, sb.st_size, PROT_READ|\
          PROT_WRITE, MAP_SHARED, fd, 0)) == (void*)-1)  perror("mmap\n");
    close(fd);
    const char *p = text;
    char *q = mmapped;
    for(; *p != '\0'; ++p, ++q) {*q = *p; usleep(1000);}
    if((msync((void*)mmapped, sb.st_size, MS_SYNC)) == -1)  perror("msync");
    printf("write complete\n");

    if((munmap((void *)mmapped, sb.st_size)) == -1)  perror("munmap\n");
    return NULL;
}

void *my_mmap_read(void *arg)
{
    if (arg == NULL) return NULL;
    const char *path = (char *)arg;
    char buf[MAX_LEN] = {0};
    
    printf("read:path:%s\n", path);
    int fd;
    if((fd = open(path, O_RDWR)) < 0) {
        perror("open\n");
        return NULL;
    }
    struct stat sb;
    if(fstat(fd, &sb) == -1)  perror("fstat");
    char *mmapped;
    if((mmapped = mmap(NULL, sb.st_size, PROT_READ, 
        MAP_SHARED, fd, 0)) == (void*)-1)  perror("mmap\n");
    close(fd);
    char *p = mmapped;
    printf("buf is:\n");
    for(; *p != '\0'; ++p) { printf("%c", *p); usleep(1000);}
    printf("\n");
    return NULL;
}

int main(int argc, char **argv)
{
    char *path = (char *)malloc(MAX_LEN);
    char *text = (char *)malloc(MAX_LEN);
    strncpy(path, argv[1], strlen(argv[1]));
    strncpy(text, argv[2], strlen(argv[2]));
    
    thread_param *param = (thread_param *)malloc(sizeof(thread_param));
    param->path = path;
    param->text = text;

    //起线程
    pthread_t ntid, ntid2;
    printf("read\n");
    pthread_create(&ntid, NULL, my_mmap_read, argv[1]);
    printf("write\n");
    pthread_create(&ntid2, NULL, my_mmap_write, (void *)param);

    //回收线程
    pthread_join(ntid, NULL);
    pthread_join(ntid2, NULL);
    return 0;
}
