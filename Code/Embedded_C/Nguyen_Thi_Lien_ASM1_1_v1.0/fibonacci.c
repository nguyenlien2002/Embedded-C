#include "fibonacci.h"

unsigned long long fibonacci(int n){
	unsigned long long a = 0, b = 1, c;
	if(n == 0){
		return a;
	}
	int i;
	for(i = 2; i <= n; i++){
		c = a + b;
		a = b;
		b = c;
	}
	return b;
}


