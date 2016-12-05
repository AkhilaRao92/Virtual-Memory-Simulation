#include<stdio.h>

int main()
{
	FILE* f;
	int a;
	char m;
	char b[4];
	
	f = fopen("/home/apoorva/OS_assignment/OS_assignment/input1.txt","r");
	
	fscanf(f,"%d,%c,%c%c%c%c",&a,&m,&b[0],&b[1],&b[2],&b[3]);
		
	printf("a = %d\n",a);
	
	fclose(f);
	
	return 0;
}
