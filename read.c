#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"file.h"

void extract(int pid,char a[],char page_no[6])   // to extract the first 6 bits
{
	int i;
	char bin_addr[8];
	
	for(i=0;i<2;i++)				
	{
		switch(a[i])	
		{
			case '0':
				if(i == 0)
					strcpy(bin_addr,"0000");	
				
				if(i == 1)
					strcat(bin_addr,"0000");
				break;
			
			case '1':
				if(i == 0)
					strcpy(bin_addr,"0001");	
				
				if(i == 1)
					strcat(bin_addr,"0001");
				break;
			
			case '2':
				if(i == 0)
					strcpy(bin_addr,"0010");	
				
				if(i == 1)
					strcat(bin_addr,"0010");
				break;

			case '3':
				if(i == 0)
					strcpy(bin_addr,"0011");	
				
				if(i == 1)
					strcat(bin_addr,"0011");
				break;
			
			case '4':
				if(i == 0)
					strcpy(bin_addr,"0100");	
				
				if(i == 1)
					strcat(bin_addr,"0100");
				break;
			
			case '5':
				if(i == 0)
					strcpy(bin_addr,"0101");	
				
				if(i == 1)
					strcat(bin_addr,"0101");
				break;
			
			case '6':
				if(i == 0)
					strcpy(bin_addr,"0110");	
				
				if(i == 1)
					strcat(bin_addr,"0110");
				break;
			
			case '7':
				if(i == 0)
					strcpy(bin_addr,"0111");	
				
				if(i == 1)
					strcat(bin_addr,"0111");
				break;
			
			case '8':
				if(i == 0)
					strcpy(bin_addr,"1000");	
				
				if(i == 1)
					strcat(bin_addr,"1000");
				break;
			
			case '9':
				if(i == 0)
					strcpy(bin_addr,"1001");	
				
				if(i == 1)
					strcat(bin_addr,"1001");
				break;
			
			case 'A':
				if(i == 0)
					strcpy(bin_addr,"1010");	
				
				if(i == 1)
					strcat(bin_addr,"1010");
				break;
		
			case 'B':
				if(i == 0)
					strcpy(bin_addr,"1011");	
				
				if(i == 1)
					strcat(bin_addr,"1011");
				break;
			
			case 'C':
				if(i == 0)
					strcpy(bin_addr,"1100");	
				
				if(i == 1)
					strcat(bin_addr,"1100");
				break;
			
			case 'D':
				if(i == 0)
					strcpy(bin_addr,"1101");	
				
				if(i == 1)
					strcat(bin_addr,"1101");
				break;
			
			case 'E':
				if(i == 0)
					strcpy(bin_addr,"1110");	
				
				if(i == 1)
					strcat(bin_addr,"1110");
				break;		
			
			case 'F':
				if(i == 0)
					strcpy(bin_addr,"1111");	
				
				if(i == 1)
					strcat(bin_addr,"1111");
				break;
		}
	}


		for(i=0;i<6;i++)
		{
			page_no[i] = bin_addr[i];	
		}
		
}

int convert(char page_no[6])  // to convert the page number from binary to decimal
{
	int res = 0;

	if(page_no[0] == '1')
	{
		res += 32;
	}

	if(page_no[1] == '1')
	{
		res += 16;
	}
	
	if(page_no[2] == '1')
	{
		res += 8;
	}
	
	if(page_no[3] == '1')
	{
		res += 4;
	}
	
	if(page_no[4] == '1')
	{
		res += 2;
	}

	if(page_no[5] == '1')
	{
		res += 1;
	}

	return res;
}


