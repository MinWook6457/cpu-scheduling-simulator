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
	int return_time; // ���μ��� ��ȯ�ð�
	int turnAround_time; // ���μ��� �ҿ�ð�
	bool completed;
}Process;
void Process_init(Process *p, int n) // ���μ��� �ʱ�ȭ �Լ�
{
	for (int i = 0; i < n; i++){ // ���μ��� ���� ��ŭ �ݺ�
		p[i].waiting_time = 0; // ��� �ð� �ʱ�ȭ
		p[i].response_time = 0; // ���� �ð� �ʱ�ȭ
		p[i].turnAround_time = 0; // ��ȯ �ð� �ʱ�ȭ
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

	FCFS_Scheduling(process, process_count);

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
int compare(const void* a, const void* b) // �������� �� �Լ� ����
{
	Process p1 = *(Process*)a;
	Process p2 = *(Process*)b;

	if (p1.arrival_time < p2.arrival_time)
		return -1;

	if (p1.arrival_time > p2.arrival_time)
		return 1;

	return 0;
}
// �����ð��� �������� (��)������ �Լ�
void qsort_arrival_time(Process* p, int n) {
	qsort(p, n, sizeof(p[0]), compare);
}
void FCFS_Scheduling(Process* p,int pc) {
	int total_waiting_time = 0; // �� ���μ��� ��� �ð�
	int total_turnAround_time = 0; // �� ���μ��� �ҿ� �ð�
	int total_response_time = 0; // �� ���μ��� ���� �ð�
	int total_return_time = 0; // �� ���μ��� ��ȯ �ð�

	Process_init(p, pc);

	qsort_arrival_time(p, pc);

	for (int i = 0; i < pc; i++) {
		printf("%s : %d\n", p[i].id,p[i].arrival_time);
	}
	/* �� ó�� ���� ���μ��� ���� */
	p[0].return_time = p[0].run_time; // ���Ͽ��� ���� run_time�� return_time�� ����
	p[0].turnAround_time = p[0].return_time - p[0].arrival_time; // ��ȯ�ð� = ����ð� - ���ð�
	p[0].response_time = 0;
	p[0].waiting_time = 0;

	/* ����� ���μ��� ��ŭ ���� ���� */
	total_waiting_time += p[0].waiting_time;
	total_turnAround_time += p[0].turnAround_time;
	total_response_time += p[0].response_time;
	total_return_time += p[0].run_time;

	// ���� ���� ������ ������ ������� ���μ��� ���
	for (int i = 1; i < pc ; i++)
	{
		/* �� ���μ��� ��� */
		p[i].waiting_time = total_return_time - p[i].arrival_time; // �� ���μ��� ���ð� = �� ��ȯ�ð� - �����ð� 
		p[i].return_time = total_return_time + p[i].run_time; // �� ���μ��� ��ȯ�ð� = �� ��ȯ�ð� + ����ð�
		p[i].turnAround_time = p[i].return_time - p[i].arrival_time; // �� ���μ��� �ҿ�ð� = �� ���μ��� ��ȯ�ð� - �����ð�
		p[i].response_time = p[i].waiting_time; // �����ð� = ���ð�

		/* ����� ���μ��� ��ŭ ���� ���� */
		total_return_time += p[i].run_time;
		total_waiting_time += p[i].waiting_time;
		total_turnAround_time += p[i].turnAround_time;
		total_response_time += p[i].response_time;
	}

	printf("Average Total Waiting time = %lf\n", (double)total_waiting_time / (double)pc); // ��� ��� �ð�
	printf("Average Total turnAround time = %lf\n", (double)total_turnAround_time / (double)pc); // ��� ��ȯ �ð�
	printf("Average Total Response time = %lf\n", (double)total_response_time / (double)pc); // ��� ���� �ð�


}