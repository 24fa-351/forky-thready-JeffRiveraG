#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void pattern_1(int numberOfThings, FILE *file) {
    fprintf(file, "Main process PID: %d beginning\n", getpid());

    srand(time(NULL));
    int sleep_time = rand() % 8 + 1;
    sleep(sleep_time);

    for (int i = 1; i <= numberOfThings; i++) {
        pid_t PID = fork();
        if (PID == 0) {
            fprintf(file, "Process %d PID: %d beginning\n", i, getpid());
            sleep_time = rand() % 8 + 1;
            sleep(sleep_time);
            fprintf(file, "Process %d exiting\n", i);
            exit(0);
        } else if (PID < 0) {
            perror("Fork failed");
            exit(1);
        }
    }

    fprintf(file, "Main process exiting\n");
}

void pattern_2(int numberOfThings, FILE *file) {
    fprintf(file, "Main process PID: %d beginning\n", getpid());

    srand(time(NULL));
    int sleep_time = rand() % 8 + 1;
    sleep(sleep_time);

    for (int i = 1; i <= numberOfThings; i++) {
        pid_t PID = fork();
        if (PID == 0) {
            fprintf(file, "Process %d PID: %d beginning\n", i, getpid());
            sleep_time = rand() % 8 + 1;
            sleep(sleep_time);
            continue;
        } else if (PID < 0) {
            perror("Fork failed");
            exit(1);
        }
        break;
    }

    fprintf(file, "Main process exiting\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <numberOfThings> <pattern>\n", argv[0]);
        exit(1);
    }

    int numberOfThings = atoi(argv[1]);
    int patternChoice = atoi(argv[2]);

    if (numberOfThings < 1 || numberOfThings > 256) {
        fprintf(stderr, "Number of things must be between 1 and 256\n");
        exit(1);
    }
    if (patternChoice != 1 && patternChoice != 2) {
        fprintf(stderr, "Pattern Choice must be 1 or 2\n");
        exit(1);
    }

    FILE *file = fopen("results.txt", "w");
    if (file == NULL) {
        perror("Could not open file :(");
        exit(1);
    }

    if (patternChoice == 1) {
        pattern_1(numberOfThings, file);
    } else if (patternChoice == 2) {
        pattern_2(numberOfThings, file);
    }

    fclose(file);

    return 0;
}
