#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void displayFileContent(FILE *file);
void appendStringToFile(FILE *file);
void searchStringInFile(FILE *file);
void menu(FILE *file);

/*******************************************************************************
 * Code
 ******************************************************************************/
int main() 
{
    char filePath[256];
    FILE *file;

    printf("Enter the file path: ");
    scanf("%255s", filePath);

    file = fopen(filePath, "r+");
    if (file == NULL) 
    {
        /* File does not exist, create it*/
        file = fopen(filePath, "w+");
        if (file == NULL) 
        {
            printf("Error creating file!\n");
            return 1;
        }
        printf("File created: %s\n", filePath);
    }

    menu(file);
    fclose(file);
    return 0;
}

void menu(FILE *file) 
{
    int choice;
    printf("\nMenu:\n");
    printf("1. Display the content of the file\n");
    printf("2. Append a string to the file\n");
    printf("3. Search for a string in the file\n");
    printf("4. Exit\n");
    do 
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                displayFileContent(file);
                break;
            case 2:
                appendStringToFile(file);
                break;
            case 3:
                searchStringInFile(file);
                break;
            case 4:
                printf("Exiting program.");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 4);
}

void displayFileContent(FILE *file) 
{
    char ch;
    rewind(file); /* Set file position to the beginning */
    printf("File Content:\n");
    while ((ch = fgetc(file)) != EOF) 
    {
        putchar(ch);
    }
    rewind(file); /* Reset file position to the beginning */
}

void appendStringToFile(FILE *file) 
{
    char buffer[1024];
    printf("Enter the string to append: ");
    getchar(); /* Clear newline character from the buffer */
    fgets(buffer, sizeof(buffer), stdin);
    fseek(file, 0, SEEK_END); /* Move to the end of the file */
    fprintf(file, "%s", buffer);
    fflush(file); /* Ensure the buffer is written to the file */
    printf("String appended to the file.\n");
}

void searchStringInFile(FILE *file) 
{
    char search[256];
    char line[1024];
    int lineNumber = 0;
    int lastline =0;
    int found = 0;
    int i, j, pos;

    printf("Enter the string to search for: ");
    getchar(); /* Clear newline character from the buffer */
    fgets(search, sizeof(search), stdin);
    /* Remove newline character from search string */
    for (i = 0; search[i] != '\0'; i++) 
    {
        if (search[i] == '\n') 
        {
            search[i] = '\0';
            break;
        }
    }
    
    while (fgets(line, sizeof(line), file) != NULL) 
    {
        lastline++;
    }  
    rewind(file); /* Set file position to the beginning */
    while (fgets(line, sizeof(line), file) != NULL) 
    {
        lineNumber++;
        pos = 0;
        for (i = 0; line[i] != '\0'; i++) 
        {
            /* Check if search string matches the line at the current position */
            for (j = 0; search[j] != '\0' && line[i + j] != '\0'; j++) 
            {
                if (search[j] != line[i + j]) 
                {
                    break;
                }
            }
            if (search[j] == '\0') 
            {
                /* Found the search string in the line */
                found = 1;
                pos = i;
                break;
            }
        }
        if (found) 
        {
            if(lineNumber!=lastline) found=0;
            printf("Found at line %d, position %d\n", lineNumber, pos);
            if(lineNumber==lastline)    break;
        }
    }
    if (!found) 
    {
        printf("Not found!\n");
    }
}

