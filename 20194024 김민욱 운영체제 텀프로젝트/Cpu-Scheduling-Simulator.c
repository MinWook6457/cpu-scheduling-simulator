/*
	Operating System Term Project 
	������Ʈ �� : CPU-Schuduling-Simulator
	�̸� : ��ο�
	�й� : 20194024
	��� ��� : C Language
	������Ʈ ���� : 7���� CPU �����ٸ� �ùķ����� ����
					(FCFS, SJF, ���� Priority, ���� Priority, RR, SRT, HRN)
					��Ʈ ��Ʈ, �� ���μ����� ���ð�, ��� ��� �ð�, �� ���μ����� ����ð�, 
					��� ����ð�, �� ���μ����� ��ȯ �ð�, ��� ��ȯ �ð� ���
	[Repository]
*/
/*
	Turnaround Time (��ȯ �ð�)
	Turnaround Time = Completion Time - Arrival Time

	Response Time (���� �ð�)
	Response Time = FirstRun Time - Arrival Time
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // true , false 
#pragma warning(disable:4996)
typedef struct Process { // ���μ��� ����ü ����
	char id[20]; // ���μ��� id - File
	int waiting_time; // ���μ��� ���ð�
	int arrival_time; // ���μ��� �����ð� - File
	int run_time; // ���μ��� ����ð� - File
	int priority; // ���μ��� �켱���� - File
	int response_time; // ���μ��� ����ð�
	int turn_around_time; // ���μ��� ��ȯ�ð�
	bool completed;
}Process;
void Process_init(Process *p, int n) // ���μ��� �ʱ�ȭ �Լ�
{
	for (int i = 0; i < n; i++){ // ���μ��� ���� ��ŭ �ݺ�
		p[i].waiting_time = 0; // ��� �ð� �ʱ�ȭ
		p[i].response_time = 0; // ���� �ð� �ʱ�ȭ
		p[i].turn_around_time = 0; // ��ȯ �ð� �ʱ�ȭ
		p[i].completed = false;
	}
}
void FCFS_Scheduling(Process *p,int pc); // FCFS Scheduling

int main() {
	printf("=======CPU Scheduling Simulator=======\n");

	int process_count = 0; // ���μ��� ������ ������ ����

	int quantum = 0; // RR �����층���� ���� ����

	FILE* fp = fopen("Process.txt", "r"); // ���� �б� ���� ����

	/* ���� ���⿡ ������ ��� */
	if (fp == NULL) { 
		fprintf(stderr, "File Open Fail\n");
		exit(1);
	}

	fscanf(fp, "%d", &process_count); // ���Ͽ��� ���� ���μ��� ���� ����

	Process* process = (Process*)malloc(sizeof(Process) * process_count); // ���μ��� ���� ��ŭ �����Ҵ�

	for (int i = 0; i < process_count; i++) { // ���Ͽ��� ���μ���id, �����ð�, ��ȯ�ð�, �켱������ �޾� ����ü�� ����
		fscanf(fp, "%s %d %d %d", process[i].id, &process[i].arrival_time, &process[i].run_time, &process[i].priority);
		printf("%s %d %d %d\n", process[i].id, process[i].arrival_time, process[i].run_time, process[i].priority);
	}

	fscanf(fp, "%d", &quantum); // ���Ͽ��� ���� ���� ���� ����
	printf("%d", quantum);


	return 0;
}
/*
	�Լ��� : FCFS_Scheduling
	���� : �غ� ť�� ������ ������� CPU�� �Ҵ��ϴ� ���������
	�Է� : ���μ��� ������, ���μ��� ����
	��� : FCFS �����층���� ����
	�� ���μ����� ���ð�, ��� ��� �ð�, 
	�� ���μ����� ����ð�, ��� ����ð�,
	�� ���μ����� ��ȯ �ð�, ��� ��ȯ �ð�
*/
void FCFS_Scheduling(Process* p,int pc) {
	int total_waiting_time = 0; // �� ���μ��� ��� �ð�
	int total_turnAround_time = 0; // �� ���μ��� ��ȯ �ð�
	int total_response_time = 0; // �� ���μ��� ���� �ð�

	Process_init(p, pc);

	
}