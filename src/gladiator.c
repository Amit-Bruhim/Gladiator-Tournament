#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

// Array to store the attack values of the three opponents
int opponents_attack[3] = {0, 0, 0};

/**
 * get_opponent_attack – returns the attack value of a specific opponent
 * @opponent: index of the opponent (0-2)
 */
int get_opponent_attack(int opponent)
{
    return opponents_attack[opponent];
}

/**
 * main function – simulates the gladiator's battle process.
 * It reads the gladiator's stats from a file, reads opponents' stats,
 * logs the battle progress to a log file, and tracks the gladiator's health.
 */
int main(int argc, char *argv[])
{
    // Read gladiator file name from arguments
    char name[64];
    sprintf(name, "%s", argv[1]);

    // Open the gladiator's data file
    FILE *fp = fopen(name, "r");
    if (!fp) {
        perror("Error opening gladiator file");
        return 1;
    }

    // Variables to store gladiator's stats and opponents
    int health, attack, opponents[3];
    fscanf(fp, "%d, %d, %d, %d, %d", &health, &attack, &opponents[0], &opponents[1], &opponents[2]);
    fclose(fp);

    // Read opponents' attack values from their files
    for (int i = 0; i < 3; i++)
    {
        char opponent_file[64];
        sprintf(opponent_file, "data/G%d.txt", opponents[i]);
        FILE *opponent_fp = fopen(opponent_file, "r");

        int opponent_health, opponent_attack;
        fscanf(opponent_fp, "%d, %d", &opponent_health, &opponent_attack);
        fclose(opponent_fp);

        opponents_attack[i] = opponent_attack;
    }

    // Create logs directory if it doesn't exist
    mkdir("logs", 0777);

    // Open log file for this gladiator
    char log[64];
    sprintf(log, "logs/%s_log.txt", argv[1] + 5);  // Skip "data/" prefix
    FILE *log_fp = fopen(log, "w");

    // Log the start of the gladiator process
    fprintf(log_fp, "Gladiator process started. PID: %d\n", getpid());

    // Battle loop – gladiator takes damage from each opponent until health reaches 0
    while (health > 0)
    {
        for (int i = 0; i < 3; i++)
        {
            int opponent_attack = opponents_attack[i];

            // Apply damage from opponent
            health -= opponent_attack;

            if (health > 0)
            {
                // Log remaining health
                fprintf(log_fp, "Facing opponent %d... Taking %d damage\n", opponents[i], opponent_attack);
                fprintf(log_fp, "Remaining health: %d\n", health);
            }
            else
            {
                // Log that gladiator has fallen
                fprintf(log_fp, "Facing opponent %d... Taking %d damage\n", opponents[i], opponent_attack);
                fprintf(log_fp, "The gladiator has fallen... Final health: %d\n", health);
                break;
            }
        }
    }

    fclose(log_fp);
    return 0;
}
