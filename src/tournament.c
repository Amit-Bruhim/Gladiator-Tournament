#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM_GLADIATORS 4  

// Array of gladiator names
char *gladiator_names[NUM_GLADIATORS] = {
    "Maximus",
    "Lucius",
    "Commodus",
    "Spartacus"
};

// Array of file paths for each gladiator's data
char *gladiator_files[NUM_GLADIATORS] = {
    "data/G1.txt",
    "data/G2.txt",
    "data/G3.txt",
    "data/G4.txt"
};

/**
 * main function – manages the gladiator tournament.
 * It creates a separate process for each gladiator, runs the "gladiator" program
 * with the corresponding data file, waits for all processes to finish,
 * and declares the last one to finish as the winner.
 */
int main(int argc, char *argv[])
{
    int status;
    pid_t pids[NUM_GLADIATORS];

    // Create a child process for each gladiator
    for (int i = 0; i < NUM_GLADIATORS; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            // Child process executes the "gladiator" program with its data file
            char *args[] = {"gladiator", gladiator_files[i], NULL};
            execv("./bin/gladiator", args);
        }
        else
        {
            // Store the PID of the child process
            pids[i] = pid;
        }
    }

    // Variable to store the PID of the last process that finishes
    pid_t last = -1;

    // Wait for all gladiator processes to finish
    for (int i = 0; i < NUM_GLADIATORS; i++)
    {
        pid_t finished = wait(&status);
        last = finished;
    }

    // Identify and announce the winning gladiator (the last one to finish)
    for (int i = 0; i < NUM_GLADIATORS; i++)
    {
        if (pids[i] == last)
        {
            printf("The gods have spoken, the winner of the tournament is \033[32m%s 🏆\033[0m!\n", gladiator_names[i]);
            break;
        }
    }

    return 0;
}
