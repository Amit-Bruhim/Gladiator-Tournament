#include <stdio.h>
#include <sys/wait.h>

#include <sys/types.h>
#include <unistd.h>
#define NUM_GLADIATORS 4
char *gladiator_names[NUM_GLADIATORS] = {"Maximus", "Lucius", "Commodus", "Spartacus"};
char *gladiator_files[NUM_GLADIATORS] = {
    "data/G1.txt",
    "data/G2.txt",
    "data/G3.txt",
    "data/G4.txt"
};

int main(int argc, char *argv[])
{
   int status;
   pid_t pids[NUM_GLADIATORS];
   for (int i = 0; i < NUM_GLADIATORS; i++)
   {
      pid_t pid = fork();
      if (pid == 0)
      {
         char *args[] = {"gladiator",gladiator_files[i] , NULL};
         execv("./src/gladiator", args);
      }
      else{
         pids[i] = pid;
      }
   }
   for(int i = 0; i < NUM_GLADIATORS; i++)
   {
   //   printf("%d\n", pids[i]);
   }
   pid_t last = -1;
   for (int i = 0; i < NUM_GLADIATORS; i++)
   {
      pid_t finished = wait(&status);
      last = finished;
      // printf("Gladiator %d has finished\n", finished);
   }
   for(int i = 0; i < NUM_GLADIATORS; i++)
   {
      if (pids[i] == last)
      {
         printf("The gods have spoken, the winner of the tournament is %s!\n", gladiator_names[i]);
         break;
      }
   }
   
   return 0;
}