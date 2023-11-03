#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *f;
char *servers[50];
char *hostnames[50];
int serverAmount = -1;

char serverListPath[] = "C:\\serverSSH\\serverlist.txt";

void loadServers();
void separateServerHostname();
void printHostList();
void addServer(char server[]);

int main()
{
    int input, i = 0, helperInt = 0;
    char helperChar, read[50];
    char server[60] = "C:\\\"Program Files\"\\Git\\usr\\bin\\ssh.exe ";
    loadServers();
    do
    {
        printf("[0]End\n");
        printf("[1]Connect to a server\n");
        printf("[2]Add a server\n");
        printf("[3]Remove a server\n");
        scanf("%d", &input);
        system("cls");
        switch (input)
        {
        case 0:
            break;
        case 1:
            printf("\nSelect server: ");
            printHostList();
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
            break;
        case 2:
            printf("Add a server:\nTitle:username@ip_adress\n");
            scanf(" %s", &read);
            addServer(read);
            break;
        case 3:
            break;
        }
    } while (input != 0);

    // Free the allocated memory
    for (int i = 0; i <= serverAmount; i++)
    {
        free(servers[i]);
        free(hostnames[i]);
    }

    return 0;
}

void separateServerHostname()
{
    for (int i = 0; i <= serverAmount; i++)
    {
        char *colonLocation = strchr(servers[i], ':');
        int colonIndex = colonLocation - servers[i];
        char cleanIP[50], hostname[20];

        // Get server's name
        strncpy(hostname, servers[i], colonIndex);
        hostname[colonIndex] = '\0';
        strcpy(hostnames[i], hostname);

        // Get server's user@ip
        strcpy(cleanIP, servers[i] + colonIndex + 1);
        // printf("[%d] %s", i, servers[i]);
        strcpy(servers[i], cleanIP);
    }
}

void printHostList()
{
    for (int i = 0; i <= serverAmount; i++)
    {
        printf("\n[%d] %s", i, hostnames[i]);
    }
}

void loadServers()
{
    // Read all servers from serverlist
    // Save them into servers array
    char read[40];
    int i = 0;
    f = fopen(serverListPath, "r");
    while (fgets(read, 40, f) != NULL)
    {
        servers[i] = strdup(read); // Allocate memory and copy the string
        hostnames[i] = strdup(read);
        serverAmount++;
        i++;
    }
    fclose(f);

    separateServerHostname();
}

void addServer(char server[])
{
    char read[50];
    f = fopen(serverListPath, "a");
    fprintf(f, "\n");
    fprintf(f, server);
    fclose(f);
}