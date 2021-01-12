#include <stdio.h>
#include <string.h>
#define BUFFSIZE 1024

void change_msgid_to_uosmsgid(const char *dest, const char *uosmessageid)
{
    FILE *fp;
    long len_sum = 0;
    char new_msgid[BUFFSIZE] = "Message-ID: <";
    strcat(new_msgid, uosmessageid);
    strcat(new_msgid, ">\n");
    char buf[BUFFSIZE] = {0};

    printf("[sxd]---------:%s",new_msgid);
    printf("[sxd]---------dest:%s\n", dest);

    if ((fp = fopen(dest, "r+")) == NULL) {
        perror("fopen error");
        return;
    }

    do {
        if (fgets(buf, BUFFSIZE, fp) == NULL) {
            fclose(fp);
            return;
        }
        if(strncmp(buf, "Message-ID:", 11) == 0) {
            printf("len_sum:%d\n", len_sum);
            fseek(fp, len_sum, SEEK_SET);
            fprintf(fp, "%s", new_msgid);
            len_sum += strlen(new_msgid);
            break;
        }
        len_sum += strlen(buf);
    } while (!feof(fp));
    while (fgets(buf, BUFFSIZE, fp) != NULL) {
        printf("buf: %s\n", buf);
        if(buf[0] == ' ' || buf[0] == '\t'){
            printf("len_sum:%d\n", len_sum);
            fseek(fp, len_sum, SEEK_SET);
            fprintf(fp, "%s", "\n");
        } else
            break;
        break;
    }


    fclose(fp);
}

int main(int argc, char ** argv)
{
    change_msgid_to_uosmsgid("hello.eml", "1234567890");
    return 0;
}