#ifndef _FCFS_
#define _FCFS_

#include "Process.h"
#include "Function_to_Sorting.h"
#include "View_Table.h"
#include <Windows.h>
#include <stdbool.h>

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}
/*
	�Լ��� : FCFS_Scheduling(First Come First Served)
	���� : �غ� ť�� ������ ������� CPU�� �Ҵ��ϴ� ���������
	�Է� : ���μ��� ������, ���μ��� ����
	��� : FCFS �����층���� ����
	�� ���μ����� ���ð�, ��� ��� �ð�,
	�� ���μ����� ����ð�, ��� ����ð�,
	�� ���μ����� ��ȯ �ð�, ��� ��ȯ �ð�
*/
void FCFS_print_gantt_chart(Process* p, int n)
{	// �ݺ������� ����� ���� ����

	textcolor(2);
	printf("\tFirst Come First Served Scheduling\n");
	printf("��");
	/* ��� �� ��� */
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

void FCFS_Scheduling(Process* p, int pc) {
	int total_waiting_time = 0; // �� ���μ��� ��� �ð�
	int total_turnAround_time = 0; // �� ���μ��� �ҿ� �ð�
	int total_response_time = 0; // �� ���μ��� ���� �ð�
	int total_return_time = 0; // �� ���μ��� ��ȯ �ð�

	Process_init(p, pc);

	qsort_arrival_time(p, pc);
	/*
	for (int i = 0; i < pc; i++) {
		printf("%s : %d\n", p[i].id,p[i].arrival_time);
	}
	*/
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
	for (int i = 1; i < pc; i++)
	{
		/* �� ���μ��� ��� */
		p[i].waiting_time = total_return_time - p[i].arrival_time; // �� ���μ��� ���ð� = �� ��ȯ�ð� - �����ð� 
		p[i].return_time = total_return_time + p[i].run_time; // �� ���μ��� ��ȯ�ð� = �� ��ȯ�ð� + ����ð�
		p[i].turnAround_time = p[i].return_time - p[i].arrival_time; // �� ���μ��� �ҿ�ð� = �� ���μ��� ��ȯ�ð� - �����ð�
		p[i].response_time += p[i].waiting_time; // �����ð� += ���ð�

		/* ����� ���μ��� ��ŭ ���� ���� */
		total_return_time += p[i].run_time;
		total_waiting_time += p[i].waiting_time;
		total_turnAround_time += p[i].turnAround_time;
		total_response_time += p[i].response_time;
	}
	FCFS_print_gantt_chart(p, pc);
	view_table(p, pc);
	printf("\n");
	printf("Average Total Waiting time = %.2lf\n", (double)total_waiting_time / (double)pc); // ��� ��� �ð�
	printf("Average Total turnAround time = %.2lf\n", (double)total_turnAround_time / (double)pc); // ��� ��ȯ �ð�
	printf("Average Total Response time = %.2lf\n", (double)total_response_time / (double)pc); // ��� ���� �ð�


}

#endif