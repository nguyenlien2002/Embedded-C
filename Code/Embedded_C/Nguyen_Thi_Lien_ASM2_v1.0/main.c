#include<stdio.h>

int len(char s[]){
	int i=0;
	while(s[i]!= '\0'){
		i++;
	}
	return i;
}

int Palidrome(char s[]){
	int x=len(s);
	int i;
	for( i = 0; i < x/2; i++){
		if(s[i] != s[x - 1 - i]){
			return 0;
		}
	}
	return 1;
}

void rev(char s[]){
	char s1[255];
	int x=len(s);
	int i;
	for( i = 0; i < x; i++){
		s1[i]=s[x-1-i];
	}
	printf("Chuoi nguoc lai la: %s",s1);
}
int main(){
	char S[255];
	scanf("%s",S);
	if(Palidrome(S)){
		printf("%s la chuoi Palidrome",S);
	}
	else{
		printf("%s khong phai là chuoi Palidrome\n",S);
		rev(S);
	}
	return 0;
}
