#ifndef __NPPS__
#define __NPPS__

/*
	����� : NPPS.h(None Preemptive Priority Scheduling)
	���� : ������ ���μ����� �켱������ ���Ͽ� ������ ���� �۾� ������ ó���ϴ� ���
	�Է� : ���μ��� ������, ���μ��� ����
	��� : NPPS �����층���� ����
	�� ���μ����� ���ð�, ��� ��� �ð�,
	�� ���μ����� ����ð�, ��� ����ð�,
	�� ���μ����� ��ȯ �ð�, ��� ��ȯ �ð�

*/

#include "Process.h"
#include <Windows.h>
#include "View_Table.h"
#include "Function_to_Sorting.h"
#pragma warning(disable:4996)

void NPPS_Process_Time(Process* p, int n, char* check_id) {
	int current_time = 0; // ������� ���� �ð��� ������ ����

	/* ���� ���� ���� ���μ��� ���� �� �ð� ��� */
	p[0].return_time = p[0].run_time;
	p[0].turnAround_time = p[0].return_time - p[0].arrival_time;
	p[0].response_time = 0;
	p[0].completed = true;

	current_time = p[0].run_time;

	qsort_priority_time(p, n);

	for (int i = 0; i < n; i++) {
		if (strcmp(check_id, p[i].id) == 0) {
			i++;
		}

		p[i].response_time = current_time - p[i].arrival_time;
		p[i].return_time = current_time + p[i].run_time;
		p[i].turnAround_time = p[i].return_time - p[i].arrival_time;
		p[i].waiting_time = current_time - p[i].arrival_time;
		p[i].completed = true;

		current_time += p[i].run_time;
	}
}

void NPPS_print_gantt_chart(Process* p, int n, char* check_id)
{
	printf("\tNon Preemptive Priority Scheduling\n");

	printf("��");
	/* ��� ��� */
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < p[i].run_time; j++)
			printf("����");

		if (i == n - 1)
			printf("��");
		else
			printf("��");
	}

	printf("\n��");
	/* ���μ��� �̸� ��� */
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < p[i].run_time - 1; j++)
			printf(" ");

		printf("%s", p[i].id);

		for (int j = 0; j < p[i].run_time - 1; j++)
			printf(" ");

		printf("��");
	}

	printf("\n");
	printf("��");

	/* �ϴ� �� ��� */
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < p[i].run_time; j++)
			printf("����");


		if (i == n - 1)
			printf("��");
		else
			printf("��");
	}

	printf("\n");

	/* ���μ��� �ð� ��� */
	printf("0");
	// qsort_return_time(p, n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < p[i].run_time; j++)
			printf("  ");

		if (p[i].return_time > 9)
			printf("\b");
		printf("%d", p[i].return_time);

	}

	printf("\n");
}



void NPPS_Scheduling(Process* p, int pc) {
	int total_waiting_time = 0; // �� ���μ��� ��� �ð�
	int total_turnAround_time = 0; // �� ���μ��� �ҿ� �ð�
	int total_response_time = 0; // �� ���μ��� ���� �ð�

	Process_init(p, pc);

	qsort_arrival_time(p, pc);

	char check_id[10];
	strcpy(check_id, p[0].id); // ���� ó������ ���� PID ����

	
	NPPS_Process_Time(p, pc, check_id);

	for (int i = 0; i < pc; i++) {
		total_response_time += p[i].response_time;
		total_waiting_time += p[i].waiting_time;
		total_turnAround_time += p[i].turnAround_time;
	}
	qsort_return_time(p, pc);

	NPPS_print_gantt_chart(p, pc, check_id);

	view_table(p, pc);

	printf("\n");
	printf("Average Total Waiting time = %.2lf\n", (double)total_waiting_time / (double)pc); // ��� ��� �ð�
	printf("Average Total turnAround time = %.2lf\n", (double)total_turnAround_time / (double)pc); // ��� ��ȯ �ð�
	printf("Average Total Response time = %.2lf\n", (double)total_response_time / (double)pc); // ��� ���� �ð�
}

#endif __NPPS__