#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;

static void
sig_usr(int signo) /* one signal handler for SIGUSR1 and SIGUSR2 */
{
    sigflag = 1;
}

static void TELL_WAIT(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        perror("signal(SIGUSR1) error");

    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        perror("signal(SIGUSR2) error");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    /* Block SIGUSR1 and SIGUSR2, and save current signal mask */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        perror("SIG_BLOCK error");
}

static void TELL_PARENT(void)
{
    kill(getppid(), SIGUSR2); /* tell parent we’re done */
}

static void WAIT_PARENT(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask); /* and wait for parent */
    sigflag = 0;
    /* Reset signal mask to original value */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("SIG_SETMASK error");
}

static void TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1); /* tell child we’re done */
}

static void WAIT_CHILD(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask); /* and wait for child */
    sigflag = 0;
    /* Reset signal mask to original value */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("SIG_SETMASK error");
}

static int increment_counter(FILE *const file)
{
    /* TODO */ //increment counter inside the txt file
    fseek(file, 0, SEEK_SET);
    int counter;
    fscanf(file, "%d", &counter);
    fseek(file, 0, SEEK_SET);
    fprintf(file, "%d", ++counter);
    fflush(file); //flushes the buffer
    return counter;
}

int main(void)
{
    /* TODO */
    FILE *file = fopen("text.txt", "w+"); 
    pid_t pid;
    int counter;
    fwrite("0", 1, 1, file);
    fflush(file);
    
    TELL_WAIT(); 

    if ((pid = fork()) < 0) {
        perror("Fork error");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) { // Child process
        for (int i = 0; i < 50; i++) {
            counter = increment_counter(file); //child go first
            printf("Child incrementing, value: %d\n", counter);
            TELL_PARENT(); 
            WAIT_PARENT(); 
        }
        fclose(file); 
    } 
    else { // Parent process
        for (int i = 0; i < 50; i++) {
            WAIT_CHILD(); // child go first, so parent wait
            counter = increment_counter(file);
            printf("Parent incrementing, value: %d\n", counter);
            TELL_CHILD(pid); // Notify the child that the increment is done
        }
        fclose(file); 
    }

    return 0;
}
