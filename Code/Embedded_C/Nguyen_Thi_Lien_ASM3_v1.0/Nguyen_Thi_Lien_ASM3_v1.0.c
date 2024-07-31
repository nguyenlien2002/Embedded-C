#include<stdio.h>
#include<stdint.h>
#define size 100
uint8_t Arr[size];

// Delete the entire array
void del(void)
{
	int i;
	for(i = 0; i < size; i++)
	{
		Arr[i] = 0xff;
	}	
}

// check
int checkArray(void)
{
	int i;
	for(i = 0; i < size; i++)
	{
		if(Arr[i] != 0xff)
		{
			return 1;
		}
	}
	return 0;
}

// print Array
void printArray(void){
	if(checkArray())
	{
		int i;
		for(i = 0; i < size; i++)
		{
			printf("%d ",Arr[i]);
			if(!((i + 1) % 10) && (i != 0))
			{
				printf("\n");
			} 
		}
		printf("\n");
	}
	else printf("Array is empty\n");
}

// insert 1 element into position k of the array
void insert(int a, int k)
{
	if(Arr[k] == 0xff)
	{
		Arr[k] = a;
		printf("Inserted %d at position %d.\n", a, k);
	}
	else printf("Position %d already contains a value.\n", k);
}

// Delete k element
int delk(int k){
	if(Arr[k] != 0xff)
	{
		Arr[k] = 0xff;
		printf("The element at position %d has been deleted\n",k);
	}
	else printf("there is no element at position %d\n",k);
}

// Search for elements in the array
void searchArray(int x)
{
	int i,j;
	int index = 0;
	for(i = 0; i < size; i++)
	{
		if(x == Arr[i]) 
		{
			j = i;
			index++;
		}
	}
	if (index != 0) printf("Found %d at position %d.\n", x, j);
	else printf("Value %d not found in the array.\n", x);
}

// Sort the array in order from smallest to largest
void arrangedSTL() 
{
    int index;
    int i,j;
    for(i = 0; i < size; i++)
	{
        for(j = i + 1; j < size; j++)
		{
            if(Arr[i] > Arr[j])
			{
                index = Arr[i];
                Arr[i] = Arr[j];
                Arr[j] = index;
            }
        }
    }
	for (i = 0; i < size; i++) 
	{
	    if (Arr[i] != 0xff) 
		{
	        printf("%d ", Arr[i]);
	    }
	}
	printf("\n");
}

// Sort the array in order from largest to smallest
void arrangedLTS(){
    int index;
    int i,j;
    for(i = 0; i < size; i++)
	{
        for(j = i + 1; j < size; j++)
		{
            if(Arr[i] < Arr[j])
			{
                index = Arr[i];
                Arr[i] = Arr[j];
                Arr[j] = index;
            }
        }
    }
    for (i = 0; i < size; i++) 
	{
	    if (Arr[i] != 0xff) 
		{
	        printf("%d ", Arr[i]);
		}
    }
    printf("\n");
}
// Find the largest number in the array
void searchMax(void)
{
	int i;
	int index = Arr[0];
	for(i = 0; i < size; i++)
	{
		if(index < Arr[i])
		{
			index = Arr[i];
		}
	}
	printf("The largest element in the array is %d\n", index);
}

// Find the smallest number in the array
void searchMin(void)
{
	int i;
	int index = Arr[0];
	for(i = 0; i < size; i++)
	{
		if(index > Arr[i])
		{
			index = Arr[i];
		}
	}
	printf("The smallest element in the array is %d\n", index);
}

int main()
{
	printf("				Array Management Program:\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Enter 'c' to clear the data of the current array and allow the user to input new values.\n");
	printf("Enter 'p' to print the array .\n");
	printf("Enter 'i' to insert an element into the array at position k.\n");
	printf("Enter 'd' to delete an element at position k.\n");
	printf("Enter 's' to print the array in ascending order.\n");
	printf("Enter 'x' to print the array in descending order.\n");
	printf("Enter 't' to search for a number x in the array (x entered from the keyboard) and display its position if found.\n");
	printf("Enter 'a' to print the largest number in the array.\n");
	printf("Enter 'w' to print the smallest number in the array.\n");
	printf("Enter 'e' to exit the program.\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	del();
	printArray();
	char c;
	int a, k, x;
	
	printf("Enter command: ");
	while(1)
	{	
		scanf("%c", &c);
		switch (c)
		{
			case 'c':
				del();
				break;
			case 'p':
				printArray();
				break;
			case 'i':
				printf("Enter position (0-99): ");
                scanf("%d", &k);
                printf("Enter value (0-100): ");
                scanf("%d", &a);
                insert(a, k);
                break;
			case 'd':
				printf("Enter position: ");
				scanf("%d", &k);
				delk(k);
				break;
			case 's':
				arrangedSTL();
				break;
			case 'x':
				arrangedLTS();
				break;
			case 't':
				printf("Enter value to search (0-100): ");
                scanf("%d", &x);
				searchArray(x);
				break; 
			case 'a':
				searchMax();
				break;
			case 'w':
				searchMin();
				break;
			case 'e':
				return 0;
			default:
				printf("Enter command: ");
                break;
		}
	}
	return 0;
}
