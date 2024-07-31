#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*******************************************************************************
*Define 
******************************************************************************/
struct student
{
    char name[50];
    unsigned int ID;
    float Mathscore;
    struct student* next;
};

typedef struct student * Node;

struct Collection
{
    Node head;
};

/*******************************************************************************
* Prototypes
******************************************************************************/
void AddToStudent(struct Collection* c, char* name, int ID, float Mathscore);
void DeleteToStudent(struct Collection* c, int id);
void FindStudent(struct Collection* c, int id);
void PrintCollection(struct Collection* c);
void Menu(struct Collection* c);


/*******************************************************************************
* Code
******************************************************************************/
int main() 
{
    struct Collection c;
    c.head = NULL;
    Menu(&c);
    return 0;
}

/* Them sinh vien */
void AddToStudent(struct Collection* c, char* name, int ID, float Mathscore) 
{
    Node new = (Node)malloc(sizeof(struct student));
    strcpy(new->name, name);
    new->ID = ID;
    new->Mathscore = Mathscore;
    new->next = c->head;
    c->head = new;
}

/* Ham xoa sinh vien */
void DeleteToStudent(struct Collection* c, int id)
{
    Node n = c->head;
    Node prev = NULL;
    while (n != NULL) 
    {
        if (n->ID == id) 
        {
            if (prev == NULL) /* prev == NULL khi dang xu ly node dau tien cua danh sach */
            { 
                c->head = n->next; /* tro toi sinh vien tiep theo */
            } 
            else 
            {
                prev->next = n->next; /* cap nhat con tro next cua prev de bo qua node n hien tai và tro den node tiep theo */
            }
            free(n);
            printf("Deleted student with ID %d\n", id);
            return;
        }
        prev = n;
        n = n->next;
    }
    printf("Student with ID %d not found.\n", id);
}

/* Hàm tìm sinh viên theo ID */
void FindStudent(struct Collection* c, int id) 
{
    Node n = c->head;
    while (n != NULL) 
    {
        if (n->ID == id) 
        {
            printf("Student found - Name: %s, ID: %u, Math Score: %.2f\n", n->name, n->ID, n->Mathscore);
            break; /* khong tiep tuc duyet cac node tiep theo */
        }
        n = n->next;
    }
    if (n == NULL) 
    {
        printf("Student with ID %d not found.\n", id);
    }
}

/* Ham in danh sach sinh vien */
void PrintCollection(struct Collection* c) 
{
    Node n = c->head;
    while (n != NULL) 
    {
        printf("Name: %s, ID: %u, Math Score: %.2f\n", n->name, n->ID, n->Mathscore);
        n = n->next;
    }
}

/* Sap xep thu tu sinh vien theo diem */
void SortStudent(struct Collection* c) 
{
    int swapped;
    int check = 1;
    Node n;
    Node lptr = NULL; /* lptr de danh dau vi tri phan tu cuoi cung da duoc sap xep, de giam so lan duyet*/
    
    if (c->head == NULL || c->head->next == NULL) 
    {
        check = 0; /* Neu danh sach rong hoac chi co mot sinh vien thi khong can sap xep */
    }
    if(check == 1)
    {
        do 
        {
            swapped = 0;
            n = c->head;
        
            while (n->next != lptr) 
            {
                if (n->Mathscore < n->next->Mathscore) 
                {
                    // Hoan doi du lieu giua n và n->next
                    char tempName[50];
                    unsigned int tempID;
                    float tempMathscore;
        
                    strcpy(tempName, n->name);
                    tempID = n->ID;
                    tempMathscore = n->Mathscore;
        
                    strcpy(n->name, n->next->name);
                    n->ID = n->next->ID;
                    n->Mathscore = n->next->Mathscore;
        
                    strcpy(n->next->name, tempName);
                    n->next->ID = tempID;
                    n->next->Mathscore = tempMathscore;
        
                    swapped = 1;
                }
                n = n->next;
            }
            lptr = n;
        } 
        while (swapped);
    }
}

/* Ham hien thi menu */
void Menu(struct Collection* c) 
{
    int choice;
    char name[50];
    int id;
    float score;
    Node student;
    
    printf("1. Add Student\n");
    printf("2. Delete Student\n");
    printf("3. Find Student\n");
    printf("4. Print All Students\n");
    printf("5. Sort Students By Score From High To Low\n");
    printf("6. Exit\n");

    do 
    {
        choice = 0;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        while(getchar() != '\n');
        
        switch (choice) 
        {
            case 1: 
                printf("Enter student name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; 
                printf("Enter student ID: ");
                scanf("%d", &id);
                while(getchar() != '\n');
                printf("Enter Math score: ");
                scanf("%f", &score);
                while(getchar() != '\n');
                AddToStudent(c, name, id, score);
                break;
            case 2:
                printf("Enter student ID to delete: ");
                scanf("%d", &id);
                DeleteToStudent(c, id);
                break;
            case 3:
                printf("Enter student ID to find: ");
                scanf("%d", &id);
                FindStudent(c, id);
                break;
            case 4:
                PrintCollection(c);
                break;
            case 5:
                SortStudent(c);
                break;
            case 6:
                break;
            default:
                printf("Invalid choice. Please try again.\n"); 
        }
    } 
    while (choice != 6);
}


