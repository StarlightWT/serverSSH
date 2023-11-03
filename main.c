#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *f;
int serverAmount = -1;

int main()
{
    int input, i = 0, helperInt = 0;
    char read[40], helperChar;
    char *servers[50];
    char server[60] = "C:\\\"Program Files\"\\Git\\usr\\bin\\ssh.exe ";
    // Read all servers from serverlist
    // Save them into servers array
    f = fopen("C:\\serverSSH\\serverlist.txt", "r");
    while (fgets(read, 40, f) != NULL)
    {
        servers[i] = strdup(read); // Allocate memory and copy the string
        serverAmount++;
        i++;
    }
    i = 0;
    fclose(f);

    printf("Server list:\n");
    for (int i = 0; i <= serverAmount; i++)
    {
        char *colonLocation = strchr(servers[i], ':');
        int colonIndex = colonLocation - servers[i];
        char cleanIP[50];

        strcpy(cleanIP, servers[i] + colonIndex + 1);
        printf("[%d] %s", i, servers[i]);
        strcpy(servers[i], cleanIP);
    }

    printf("\nSelect server: ");
    scanf("%d", &input);

    system("cls");
    if (input >= 0)
    {
        strcat(server, servers[input]);
        system(server);
        system("cls");
    }
    else
        printf("Error: Invalid input!\n");

    // Free the allocated memory
    for (int i = 0; i <= serverAmount; i++)
    {
        free(servers[i]);
    }

    return 0;
}
