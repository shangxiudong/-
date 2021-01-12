#include <stdio.h>
#include <sys/mman.h> //mmap函数的必要头文件
#include <sys/stat.h> // struct stat 需要的头文件
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LEN 128

//  mmap映射的3个主要函数
//  void mmap(void *addr, size_t len, int prot,int flags, int fildes, off_t off)
//  int msync(void *addr, size_t len, int flags);
//  int munmap(void *addr, size_t len);

/**
 * @brief mmap方式写文本
 * @param path mmap 打开文件的路径
 * @param text 要输入的文本
 */
int my_mmap_write(const char *path, const char *text)
{
    //打开文件
    int fd;
    if( (fd = open(path, O_RDWR)) < 0) {
        perror("open\n");
        return -1;
    }

    //获取文件属性
    struct stat sb;
    if(fstat(fd, &sb) == -1)  perror("fstat");
    //映射地址空间
    char *mmapped;
    if( (mmapped = mmap(NULL, sb.st_size, PROT_READ|\
          PROT_WRITE, MAP_SHARED, fd, 0)) == (void*)-1)  perror("mmap\n");
    close(fd);
    //修改同步文件内容的磁盘文件
    const char *p = text;
    char *q = mmapped;
    for(; *p != '\0'; ++p, ++q) *q = *p;
    if((msync((void*)mmapped, sb.st_size, MS_SYNC)) == -1)  perror("msync");

    //映射区释放
    if((munmap((void *)mmapped, sb.st_size)) == -1)  perror("munmap\n");
}

void my_mmap_read(char *path)
{
    char buf[MAX_LEN] = {0};

    int fd;
    if( (fd = open(path, O_RDWR)) < 0) {
        perror("open\n");
        return;
    }

    struct stat sb;
    if(fstat(fd, &sb) == -1)  perror("fstat");

    char *mmapped;
    if((mmapped = mmap(NULL, sb.st_size, PROT_READ, 
        MAP_SHARED, fd, 0)) == (void*)-1)  perror("mmap\n");
    close(fd);

    printf("[sxd]------buf:%s\n", mmapped);
}
int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("param number:%d\n", argc);
        printf("need two paramters\n");
        return -1;
    }
    // argv[0] 是运行程序本身的命令
    my_mmap_write(argv[1], argv[2]);
    my_mmap_read(argv[1]);
    return 0;
}