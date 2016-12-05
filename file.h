#ifndef FILE_H
#define FILE_H

struct frame			// frame table
{
	int pid;
	int page;
};

struct input			// input from the file is read into this structure
{
	int pid;
	char mode;
	char addr[4];
};

struct ready			// queue of ready processes
{
	int pid;
	int page;	
};


struct queue			// structure to read all the accesses into memory into one array per process to simulate the incoming requests
{
	struct input input_array[50];
};

struct page_table
{
	int P;
	int M;
	int frame_no;
};

struct process		
{	
	struct page_table Ptable[64];
}process_table[50];

void extract(int,char [],char []);
int convert(char []);
void SetEntry(int pid, int page, int frame);
int GetEntry(int pid,int page,int* frame);

void memory_mgmt_hardware_simulation(int pid);
void OS_MemoryMgmt_SignalHandler(int pid,int page,struct frame frame_table[], int frames,char addr[]);
void OS_Simulation(struct ready ready_queue[], struct frame frame_table[], int frames, int n,char addr[]);
void Init_pagetable(int pid, int page, int frame);
void Setmode(int pid, int page, char mode);
void SwapProcess(int pid, int page);
int VirtualToPhyAddrTranslate(int random_pid,int page_no);

#endif
