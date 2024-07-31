#include<stdio.h>
#include "fibonacci.h"

int main(void){
	int a;
	scanf("%d",&a);
	unsigned long long res = fibonacci(a);
	printf("So fibonacci thu %d la %llu\n",a,res);
	return 0;
}
