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
#include "FCFS.h"
#pragma warning(disable:4996)
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
		// printf("%s %d %d %d\n", process[i].id, process[i].arrival_time, process[i].run_time, process[i].priority);
	}

	fscanf(fp, "%d", &quantum); // ���Ͽ��� ���� ���� ���� ����
	// printf("%d", quantum);
	FCFS_Scheduling(process, process_count);

	return 0;
}
