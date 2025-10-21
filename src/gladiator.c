#include <stdio.h>
#include <unistd.h>

int opponets_attack[3] = {0, 0, 0};

int get_opponent_attack(int opponent)
{
   return opponets_attack[opponent];
}

int main(int argc, char *argv[])
{
   char name[64];
   sprintf(name, "%s", argv[1]);
   FILE *fp = fopen(name, "r");
   if (!fp) {
      perror("Error opening gladiator file");
      return 1;
   }
   int health, attack, opponents[3];
   fscanf(fp, "%d, %d, %d, %d, %d", &health, &attack, &opponents[0], &opponents[1], &opponents[2]);

   for(int i = 0 ; i < 3 ; i++){
      char oponnent_file[64];
      sprintf(oponnent_file, "data/G%d.txt", opponents[i]);
      FILE *opponent_fp = fopen(oponnent_file, "r");
      int opponent_attack;
      int opponent_health;
      fscanf(opponent_fp, "%d, %d", &opponent_health, &opponent_attack);
      fclose(opponent_fp);
      opponets_attack[i] = opponent_attack;
   }

   char log[64];
   sprintf(log, "%s_log.txt", argv[1] + 5);
   FILE *log_fp = fopen(log, "w");
   fprintf(log_fp, "Gladiator process started. %d: \n", getpid());

   // print here the pid as I mentioned
   while (health > 0)
   {
      for (int i = 0; i < 3; i++)
      {
         int opponent_attack = opponets_attack[i];
         fprintf(log_fp, "Facing opponent %d... Taking %d damage\n", opponents[i], opponent_attack);
         health -= opponent_attack;
         if (health > 0)
         {
            fprintf(log_fp, "Are you not entertained? Remaining health: %d\n", health);
         }
         else
         {
            fprintf(log_fp, "The gladiator has fallen... Final health: %d\n", health);
            break;
         }
      }
   }

   return 0;
}