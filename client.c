#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"file.h"

int main()
{
	FILE* f;
	FILE* g;
	FILE* h;
	int pid;
	char mode;
	char addr[4];
	char page_no[6];
	int i, j=0;
	int num_processes;
	int count = 0;
	int val = 0;
	int num = 0;
	int temp = -1;


	struct ready ready_queue[50];  			// ready queue

	struct queue input_process[50];

	
	printf("\nEnter the size of main memory in kb :: ");
		scanf("%d",&val);
	
	printf("\nEnter the number of processes :: ");
		scanf("%d",&num_processes);
	

	int no_of_frames = val/1;
		
	struct frame frame_table[no_of_frames];
	
	f = fopen("/home/akhila/OS_assignment/input1.txt","r");
	g = fopen("/home/akhila/OS_assignment/input1.txt","r");
	h = fopen("/home/akhila/OS_assignment/input1.txt","r");
	
	while(1)
	{
		int z;
		char m;
		char q[4];
		
		fscanf(h,"%d,%c,%c%c%c%c",&z,&m,&q[0],&q[1],&q[2],&q[3]);
			++count;

		if(feof(h))					
			break;
	}
	
	count -= 1;
	
	if(f == NULL)
	{
		printf("Error opening the file\n");
		exit(0);	
	}
	

	for(i = 0; i<val; ++i)				// initialise the frame table
	{	
		frame_table[i].pid = -1;				
	}

	printf("\nFrame table in the beginning \n");

	for(i = 0; i<val; ++i)
	{
		printf("| %d",frame_table[i].pid);	
	}
		
	
	//memory_mgmt_hardware_simulation() function
	
	while(1)
	{
		fscanf(f,"%d,%c,%c%c%c%c",&pid,&mode,&addr[0],&addr[1],&addr[2],&addr[3]);
		
		if(temp != pid)
			num = 0;
		
		fscanf(g,"%d,%c,%c%c%c%c",&input_process[pid].input_array[num].pid,&input_process[pid].input_array[num].mode,&input_process[pid].input_array[num].addr[0],&input_process[pid].input_array[num].addr[1],&input_process[pid].input_array[num].addr[2],&input_process[pid].input_array[num].addr[3]);
		
		// read all the accesses into memory into one array per process to simulate the incoming requests

		if(feof(g))			
			break;
		
		temp = pid;
		
		num++;
		
		for(i=0;i<63;i++)		// initialise the page table
		{
			Init_pagetable(pid,i,-1);		
		}

		
		extract(pid,addr,page_no);	// extract the first six bits for the page number

		int page = convert(page_no);	// convert the page number from binary to decimal
		
		Setmode(pid, page, mode);

		//put all the processes in the ready_queue as they are created

		ready_queue[j].pid = pid;
		ready_queue[j].page = page;
		++j;		
	}
	
	OS_Simulation(ready_queue,frame_table, val, count,addr);

	fclose(f);
	fclose(g);
	fclose(h);

	return 0;
}

void OS_Simulation(struct ready ready_queue[], struct frame frame_table[], int frames, int n,char addr[])
{
	int i = 0;
	int j = 0, random_pid;
	int page_no;

	for(i = 0; i<n; ++i)              // pick a process from the ready queue
	{
		random_pid = ready_queue[j].pid;
		page_no = ready_queue[j].page;
		++j;

		int flag = VirtualToPhyAddrTranslate(random_pid,page_no);        // check if the process is in main memory

		if(flag)		// translation successful
		{
			printf("\nTranslation successful\n");
			printf("Program %d with page number %d in frame %d\n",random_pid,page_no,random_pid);		
	
		}
		
		else		// translation failed
		{
			printf("\nTranslation of pid %d page %d failed",random_pid,page_no);
			OS_MemoryMgmt_SignalHandler(random_pid,page_no, frame_table, frames,addr);

		}
	}
}

//acts as the signal handler

void OS_MemoryMgmt_SignalHandler(int pid,int page, struct frame frame_table[], int frames,char addr[])
{
	int i = 0;
	int blocked_queue = 0;
	int k;

	blocked_queue = pid;
	
	printf("\nBlocked queue = %d\n",blocked_queue);

	//getswapcandidate
	
	int temp = frames;

	while(temp)           // check if any of the frames are free
	{
		if(frame_table[i].pid != -1)
		{
			--temp;
			++i;
		}
		else
		{
			break;
		}
	}
	
	
	// found a free frame

	if(i < frames)
	{
		frame_table[i].pid = pid;
		frame_table[i].page = page;

		for(k = 0; k<frames; ++k)
		{
			printf(" %d |",frame_table[k].pid);	
		}
		printf("\n");

		SetEntry(pid,page,i);

		blocked_queue = -1;
	}

	//if no frame is empty

	else
	{

		int random = rand()%frames;
		
		int temp_pid = frame_table[random].pid;		//get the pid of a randomly chosen frame
		
		int mode_val = GetEntry(pid, page, 0);		//check mode

		if(mode_val == 1)			// if it was a write access it is a dirty page
		{
			printf("\nSwapping out proc %d from frame %d\n", temp_pid, random);
			printf("\nSimulate disk write access\n");
			SwapProcess(temp_pid,frame_table[random].page);
			printf("\nLoading  process %d page %d into frame %d\n",pid,page,random);
			SetEntry(pid,page,random);
		}
		
		else					// swap the process out and put the new process in the frame
		{
			printf("\nSwapping out proc %d from frame %d\n", temp_pid, random);
			SwapProcess(temp_pid,frame_table[random].page);			
			printf("\nLoading page proc %d page %d into frame %d\n",pid,page,random);
			SetEntry(pid,page,random);
		}
		
		frame_table[random].pid = pid;
		frame_table[random].page = page;
		
		for(i=0;i<frames;i++)
		{
			printf(" %d |",frame_table[i].pid);	
		}
		printf("\n\n");
	}
}


