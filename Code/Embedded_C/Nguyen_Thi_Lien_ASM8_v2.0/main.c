#include<stdio.h>
#include<stdint.h>


/*******************************************************************************
*Define 
******************************************************************************/
#define SIZE 20

/*******************************************************************************
* Variables
******************************************************************************/
uint8_t assignment4[SIZE];
typedef struct Node 
{
    uint8_t* value;
    struct Node* next;
} Node;

Node b[20];

/*******************************************************************************
* Prototypes
******************************************************************************/
void InitArray(void);
void EnterValue(void);
void menu(void);
// Ham thay doi gia tri cua mot phan tu trong mang assignment4 thông qua linked list b
void modifyArray(uint8_t index, uint8_t newValue) 
{
    Node* current = &b[0];
    uint8_t count = 0;
    while (current != NULL) 
    {
        if (count == index) 
        {
            *(current->value) = newValue;
            return;
        }
        current = current->next;
        count++;
    }
}
/*******************************************************************************
* Code
******************************************************************************/
int main()
{
    InitArray();
    menu();
    return 0;
}

/*Khoi tao gia tri mang*/
void InitArray(void)
{
    int i;
    for(i = 0; i < 20; i++)
    {
        assignment4[i] = 0xffu;
    }
    // Khoi tao cac Node trong mang b
    for (i = 0; i < SIZE; i++) 
    {
        b[i].value = &assignment4[i];
        if (i < SIZE - 1) 
        {
            b[i].next = &b[i + 1];
        } 
        else 
        {
            b[i].next = NULL; // Node cuoi cung khong co next
        }
    }
}

/* Ham nhap vao gia tri cua mang*/
void EnterValue(void)
{
    uint8_t value;
    uint8_t position;
    uint8_t error = 0;
    printf("Enter position: ");
    scanf("%d",&position);
    if(position < 0 || position > 19)
    {
        printf("The position selected by the user is outside the range of 0 to 19.\n");
        error = 1;
    }
    else if(assignment4[position] != 0xffu)
    {
        printf("The position has already been filled.\n");
        error = 1;
    }
    if (!error) 
    {
        printf("Enter a value: ");
        scanf("%d", &value);
        if (value >100) 
        {
            printf("The value selected by the user is outside the range of 0 to 100.\n");
            error = 1;
        } 
        else 
        {
			Node* current = &b[0];
			while (current != NULL) 
            {
			    if(*(current->value) == value) 
				{
                    printf("The value selected by the user already exists in the array.\n");
                    error = 1;
                    break;
			    }
			    current = current->next;
			}
        }

        if (!error) {
            //assignment4[position] = value;
            modifyArray(position, value);
            //InsertSorted(value);
        }
    }
}
/* Ham xoa gia tri khoi mang */
void DeleteValue(void) 
{
    uint8_t value;
    uint8_t error = 0;
    int found = 0;
    int i;
    printf("Enter the value to delete: ");
    scanf("%d", &value);
    if (value > 100U) 
    {
        printf("The value selected by the user is outside the range of 0 to 100.\n");
        error = 1;
    }
    if(!error)
    {
		Node* current = &b[0];
		while (current != NULL) 
        {
		    if(*(current->value) == value) 
			{
				*(current->value)=0xffu;
				found = 1;
	            printf("The value has been deleted from the array.\n");	
                break;
		    }
		    current = current->next;
		}
	    if (!found) 
        {
	        printf("The value does not exist in the array.\n");	        	
		}
    }
}
// Ham hoan doi gia tri cua hai node
void swap(Node* a, Node* b) 
{
    uint8_t temp = *(a->value);
    *(a->value) = *(b->value);
    *(b->value) = temp;
}

// Ham sap xep danh sach lien ket su dung Bubble Sort
void sortLinkedList(void) 
{
    int swapped;
    Node *ptr1;
    Node *lptr = NULL;
    // Kiem tra danh sach trong
    if ( &b[0]== NULL)
    {
        return;
    } 
    do 
    {
        swapped = 0;
        ptr1 = &b[0];

        while (ptr1->next != lptr) 
        {
            if (*(ptr1->value) > *(ptr1->next->value)) 
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
/* Ham in gia tri cua mang sau khi nhap*/
void PrintValues(void) 
{
    Node* current = &b[0];
    while (current != NULL) 
    {
        printf("%d ", *(current->value));
        current = current->next;
    }
    printf("\n");
}

/*Ham hien thi menu*/
void menu(void)
{
    int choice;
    
    printf("1. Enter a value into a specified element of the array\n");
    printf("2. Delete a specific value from the array\n");
    printf("3. Print the values of the elements entered into the array\n");
    printf("4. End the program\n");
    
    while(1)
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1:
                EnterValue();
                break;
            case 2:
                DeleteValue();
                break;
            case 3:
                printf("    1. Print the values entered into the array before sorting\n");
                printf("    2. Print the values entered into the array after sorting\n");
                printf("    Enter your choice: ");
                scanf("%d", &choice);
                switch(choice)
                {
                    case 1:
                        PrintValues();
                        break;
                    case 2:
                    	sortLinkedList();
                        PrintValues();
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                        break;
                }
                break;
            case 4:                
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

