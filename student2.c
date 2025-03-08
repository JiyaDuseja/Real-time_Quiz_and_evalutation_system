#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
int fd1,fd_st;
// FIFO file path
char * myfifo1 = "/tmp/myfifo1";
char * myfifo4="/tmp/myfifo4";
mkfifo(myfifo1, 0666);
mkfifo(myfifo4,0666);
char str1[80], str2[80];
while (1)
{
fd1 = open(myfifo1,O_RDONLY);
read(fd1, str1, 80);
// Print the read string and close
printf("Teacher %s\n", str1);
close(fd1);
fd_st=open(myfifo4,O_WRONLY);
// Take an input from user.
// 80 is maximum length
fgets(str2, 80, stdin);
write(fd_st, str2, strlen(str2)+1);
close(fd_st);
}
return 0;
}
