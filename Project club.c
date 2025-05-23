#include <stdio.h>
#include <stdlib.h>

// Functions
void adminMenu();
void userMenu();
void addUser();
void viewUsers();
void deleteUser();
void addFunction();
void viewFunctions();
void requestToJoin();
void addSuggestion();
void viewSuggestions();
void viewRequests();

int main()
{
    int choice;

    while (1)
    {
        printf("\n=== University Club Management System ===\n");
        printf("1. Admin\n");
        printf("2. User\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            adminMenu();
        }
        else if (choice == 2)
        {
            userMenu();
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}

// =============== Admin Panel ===============

void adminMenu()
{
    int choice;

    while (1)
    {
        printf("\n--- Admin Menu ---\n");
        printf("1. Add User\n");
        printf("2. View Users\n");
        printf("3. Delete User\n");
        printf("4. Add Function\n");
        printf("5. View Functions\n");
        printf("6. View Join Requests\n");
        printf("7. View Suggestions\n");
        printf("8. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) addUser();
        else if (choice == 2) viewUsers();
        else if (choice == 3) deleteUser();
        else if (choice == 4) addFunction();
        else if (choice == 5) viewFunctions();
        else if (choice == 6) viewRequests();
        else if (choice == 7) viewSuggestions();
        else if (choice == 8) break;
        else printf("Invalid choice.\n");
    }
}

void addUser()
{
    int id;
    char name[50], email[50];
    FILE *fp;

    fp = fopen("users.csv", "a");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &id);
    printf("Enter Name: ");
    scanf("%s", name);
    printf("Enter Email: ");
    scanf("%s", email);

    fprintf(fp, "%d,%s,%s\n", id, name, email);
    fclose(fp);
    printf("User added successfully.\n");
}

void viewUsers()
{
    FILE *fp;
    char data[100];
    int empty = 1;

    fp = fopen("users.csv", "r");
    if (fp == NULL)
    {
        printf("No users found.\n");
        return;
    }

    printf("\n--- User List ---\n");
    while (fgets(data, 100, fp))
    {
        printf("%s", data);
        empty = 0;
    }

    if (empty)
    {
        printf("No users found.\n");
    }

    fclose(fp);
}

void deleteUser()
{
    int id, uid;
    char name[50], email[50];
    int found = 0;

    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen("users.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    if (fp == NULL || temp == NULL)
    {
        printf("File error.\n");
        return;
    }

    while (fscanf(fp, "%d,%s,%s\n", &uid, name, email) != EOF)
    {
        if (uid != id)
        {
            fprintf(temp, "%d,%s,%s\n", uid, name, email);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("users.csv");
    rename("temp.csv", "users.csv");

    if (found)
        printf("User deleted.\n");
    else
        printf("User not found.\n");
}

void addFunction()
{
    char detail[100];
    FILE *fp = fopen("functions.csv", "a");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter function detail (one word): ");
    scanf("%s", detail);

    fprintf(fp, "%s\n", detail);
    fclose(fp);
    printf("Function added.\n");
}

void viewFunctions()
{
    FILE *fp;
    char data[100];
    int empty = 1;

    fp = fopen("functions.csv", "r");
    if (fp == NULL)
    {
        printf("No program.\n");
        return;
    }

    printf("\n--- Upcoming Functions ---\n");
    while (fgets(data, 100, fp))
    {
        printf("%s", data);
        empty = 0;
    }

    if (empty)
    {
        printf("No program.\n");
    }

    fclose(fp);
}

void viewRequests()
{
    FILE *fp;
    char line[100];
    int empty = 1;

    fp = fopen("requests.csv", "r");
    if (fp == NULL)
    {
        printf("No join requests.\n");
        return;
    }

    printf("\n--- Join Requests ---\n");
    while (fgets(line, sizeof(line), fp))
    {
        printf("ID: %s", line);
        empty = 0;
    }

    if (empty)
    {
        printf("No join requests.\n");
    }

    fclose(fp);
}

void viewSuggestions()
{
    FILE *fp;
    char line[100];
    int empty = 1;

    fp = fopen("suggestions.csv", "r");
    if (fp == NULL)
    {
        printf("No suggestions.\n");
        return;
    }

    printf("\n--- Suggestions ---\n");
    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
        empty = 0;
    }

    if (empty)
    {
        printf("No suggestions.\n");
    }

    fclose(fp);
}

// =============== User Panel ===============

void userMenu()
{
    int choice;

    while (1)
    {
        printf("\n--- User Menu ---\n");
        printf("1. View Functions\n");
        printf("2. Give Suggestion\n");
        printf("3. Request to Join\n");
        printf("4. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) viewFunctions();
        else if (choice == 2) addSuggestion();
        else if (choice == 3) requestToJoin();
        else if (choice == 4) break;
        else printf("Invalid choice.\n");
    }
}

void requestToJoin()
{
    int id;
    FILE *fp = fopen("requests.csv", "a");

    if (fp == NULL)
    {
        printf("File error.\n");
        return;
    }

    printf("Enter your Student ID: ");
    scanf("%d", &id);

    fprintf(fp, "%d\n", id);
    fclose(fp);
    printf("Join request submitted.\n");
}

void addSuggestion()
{
    char idea[100];
    FILE *fp = fopen("suggestions.csv", "a");

    if (fp == NULL)
    {
        printf("File error.\n");
        return;
    }

    printf("Enter your suggestion : ");
    scanf("%s", idea);

    fprintf(fp, "%s\n", idea);
    fclose(fp);
    printf("Suggestion submitted.\n");
}
