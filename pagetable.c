#include<stdio.h>
#include<stdlib.h>
#include"file.h"

void Init_pagetable(int pid, int page, int frame)		
{
	process_table[pid].Ptable[page].P = 0;
	process_table[pid].Ptable[page].M = 0;
	process_table[pid].Ptable[page].frame_no = frame;
}

void Setmode(int pid, int page, char mode)		// to set the mode of the process accordingly
{
	if(mode == 'R')
	{
		process_table[pid].Ptable[page].M = 0;	
	}
	
	else
	{
		process_table[pid].Ptable[page].M = 1;
	}
}

void SetEntry(int pid, int page, int frame)		// to set the page entry of the process when it is put in the main memory
{
	process_table[pid].Ptable[page].P = 1;
	process_table[pid].Ptable[page].frame_no = frame;
}

void SwapProcess(int pid, int page)		// to reset  the page entry of the process when it is removed from the main memory
{
	process_table[pid].Ptable[page].P = 0;
	process_table[pid].Ptable[page].frame_no = -1;
}

int GetEntry(int pid,int page,int* frame)   // to get the frame number and also to check if the page being swapped is a dirty page
{
	if(frame)
		*frame = process_table[pid].Ptable[page].frame_no;
	
	if( process_table[pid].Ptable[page].M == 'W')
		return 1;
	else
		return 0;
}

int VirtualToPhyAddrTranslate(int pid,int page_no)  // check if the translation is successful
{
	int f; 
	GetEntry(pid,page_no,&f);
	
	if(f != -1)
		return 1;
	else
		return 0;
}



