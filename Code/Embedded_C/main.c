#include<stdio.h>

//#pragma pack(1)
struct hocsinh
{
	char ten[20];
	char sdt[11];
	unsigned short tuoi;
	double gpa;
	float diemtoan;
	float diemly;
};
int a=7;
extern void cong(void);
void In(void){
	int b=10;
	b++;
	printf("Chay chuong trinh ham In\n");
	printf("Gia tri cua b = %d\n",b);
	a++;	
}
int main(void){
	char* c;
	struct hocsinh Lien;
	printf("size cua struct Lien = %d\n",sizeof(Lien));
	printf("Gia tri cua a = %d\n",a);
	In();
	printf("Gia tri cua a = %d\n",a);
	In();
	cong();
	printf("Gia tri cua a = %d\n",a);
	int i;
	for(i=0;i<1000;i++){
		if(i==100) {
			printf("Gia tri cua i = %d\n",i);
		}
	}
	printf("size cua c = %d\n",sizeof(c));
	return 0;
}
