#include<stdio.h>
#include<math.h>
#include<string.h>
#define maxNumbers 2

int snt(unsigned int n)
{
	if(n < 2) return 0;
	int i;
	for(i = 2; i <= sqrt(n); i++){
		if(n % i == 0) return 0;
	}
	return 1;
}
//trich xuat cac so nguyen vao mang
int extractNumber(char *input, unsigned int *Arr){
	int count = 0;
	char* token = strtok(input," "); //strtok() de tach chuoi thanh cac token dua tren dau cach
	while(token != NULL){
		if(token[0] < '0' || token[0] > '9'){
			return 0;
		}
		else{
			Arr[count] = (unsigned int) atoi(token);
		}
		count++;	
        if (count > maxNumbers) {
            return 3;
        }
        token = strtok(NULL, " ");
	}
	return count;
}

void xuly(void){
	char str[22];
	unsigned int Arr[maxNumbers];
	fgets(str,sizeof(str),stdin);
	if(str[0] == '\n'){
		printf("Loi chua nhap vao du lieu.\n");
		return;
	}
	str[strcspn(str, "\n")] = 0;
	int check = extractNumber(str,Arr);
	switch(check){
		case 0:
			printf("Loi nhap vao ki tu.\n");
			break;
		case 1:
			printf("Loi nhap vao 1 so.\n");
			break;
		case 2:
			if(snt(Arr[0]) == 1) printf("So %u la so nguyen to.\n",Arr[0]);
			else printf("So %u khong la so nguyen to.\n",Arr[0]);
			if(snt(Arr[1]) == 1) printf("So %u la so nguyen to.\n",Arr[1]);
			else printf("So %u khong la so nguyen to.\n",Arr[1]);
			break;	
		case 3: 
			printf("Loi nhap vao hon 2 so.\n");
			break;
		default:
			break;			
	}	
}

void help() {
    printf("Chuong trinh nay cho phep ban nhap vao 2 so va kiem tra xem co phai so nguyen to hay khong.\n");
    printf("Vui long nhap chinh xac 2 so nguyen cach nhau boi dau cach.\n");
    printf("Vi du: 12 17\n");
}

int main()
{
	help();
	xuly();
	return 0;
}
