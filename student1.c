#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
//the header files used for string manipulation
//(fcntl) header files used for setting the flag in open and close
//(stat) header file used for mkfifo
//(types) size_t, clock and other functions
//(unistd) used for symbolic constants
int main()
{
int fd1,fd_st;
// (fd1) pipe used for communication between teacher and student for questions of the exam
//(fd_st) pipe used for communication between student,student and teacher
// FIFO file path
char * myfifo = "/tmp/myfifo";
char * myfifo3="/tmp/myfifo3";
//read and write permissions are given to both the pipe users
mkfifo(myfifo, 0666);
mkfifo(myfifo3,0666);
char str1[80], str2[80];
//(str1) for the question data from the pipe
//(str2) for the answer data to the pipe
while (1)
{
fd1 = open(myfifo,O_RDONLY);
read(fd1, str1, 80);
// Print the question and close
printf("Teacher: %s\n", str1);
close(fd1);
//opening pipe to accept answers in write only mode
fd_st=open(myfifo3,O_WRONLY);
// Take the answer from student.
fgets(str2, 80, stdin);
write(fd_st, str2, strlen(str2)+1);
close(fd_st);
}
return 0;
}
