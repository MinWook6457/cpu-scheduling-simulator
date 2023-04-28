#ifndef _FCFS_
#define _FCFS_

#include "Process.h"
#include "View_Table.h"
#include <Windows.h>
void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
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
void fcfs_print_gantt_chart(Process* p, int len)
{	// �ݺ������� ����� ���� ����

	textcolor(2);
	printf("��");
	/* ��� �� ��� */
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < p[i].run_time; j++)
			printf("����");

		printf("��");
	}

	printf("\n��");

	/* ���μ��� �̸� ��� */
	for (int i = 0; i < len; i++)
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
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < p[i].run_time; j++)
			printf("����");

		printf("��");
	}

	printf("\n");

	/* ���μ��� �ð� ��� */
	printf("0");

	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < p[i].run_time; j++)
			printf("  ");

		if (p[i].return_time > 9)
			printf("\b");

		printf("%d", p[i].return_time);

	}

	printf("\n");
}

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
		p[i].response_time = p[i].waiting_time; // �����ð� = ���ð�

		/* ����� ���μ��� ��ŭ ���� ���� */
		total_return_time += p[i].run_time;
		total_waiting_time += p[i].waiting_time;
		total_turnAround_time += p[i].turnAround_time;
		total_response_time += p[i].response_time;
	}
	fcfs_print_gantt_chart(p, pc);

	printf("Average Total Waiting time = %lf\n", (double)total_waiting_time / (double)pc); // ��� ��� �ð�
	printf("Average Total turnAround time = %lf\n", (double)total_turnAround_time / (double)pc); // ��� ��ȯ �ð�
	printf("Average Total Response time = %lf\n", (double)total_response_time / (double)pc); // ��� ���� �ð�

	view_table(p, pc);
}

#endif