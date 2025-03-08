#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd, fd4, fd_ts1, fd_ts2;
    char *myfifo = "/tmp/myfifo";
    char *myfifo1 = "/tmp/myfifo1";
    char *myfifo3 = "/tmp/myfifo3";
    char *myfifo4 = "/tmp/myfifo4";

    mkfifo(myfifo, 0666);
    mkfifo(myfifo1, 0666);
    mkfifo(myfifo3, 0666);
    mkfifo(myfifo4, 0666);

    int mark1 = 0, mark2 = 0, n = 0;
    char answer[20];

    FILE *f_questions = fopen("questions.txt", "r");
    FILE *f_answers = fopen("answers.txt", "r");

    if (f_questions == NULL || f_answers == NULL) {
        perror("Error opening file");
        return 1;
    }

    char arr2[80], arr3[80], arr4[80], correct_answer[80];
    int i = 0;

    while (fgets(arr2, sizeof(arr2), f_questions) != NULL) {
        // Process each line (question) here
        printf("Question %d: %s", i + 1, arr2);

        // Reading correct answer from answers.txt
        fgets(correct_answer, sizeof(correct_answer), f_answers);

        // Writing the data into student interaction pipe
        fd = open(myfifo, O_WRONLY);
        fd4 = open(myfifo1, O_WRONLY);

        write(fd, arr2, strlen(arr2) + 1);
        write(fd4, arr2, strlen(arr2) + 1);

        close(fd);
        close(fd4);

        fd_ts1 = open(myfifo3, O_RDONLY);
        fd_ts2 = open(myfifo4, O_RDONLY);

        read(fd_ts1, arr3, sizeof(arr3));
        printf("Student1 %s\n", arr3);
        close(fd_ts1);

        read(fd_ts2, arr4, sizeof(arr4));
        printf("Student2 %s\n", arr4);
        close(fd_ts2);

        // Comparing the answers and updating the marks
        if (strcmp(arr3, correct_answer) == 0)
            mark1++;
        else if (strcmp(arr4, correct_answer) == 0)
            mark2++;
        else
            n++;

        i++;  // Incrementing i for the next question

        // Check for end condition
        if (strcmp(arr2, "END\n") == 0)
            break;
    }

    fclose(f_questions);
    fclose(f_answers);

    //updating the marks into file
    FILE *f1 = fopen("marks.txt", "w");
    fprintf(f1, "Student 1: %d\n", mark1);
    fprintf(f1, "Student 2: %d\n", mark2);
    fprintf(f1, "No Answer: %d\n", n);
    fclose(f1);

    return 0;
}
