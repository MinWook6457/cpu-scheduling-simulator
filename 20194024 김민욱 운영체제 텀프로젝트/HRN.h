#ifndef __HRN__
#define __HRN__
/*
	����� : HRN.h (Highest Response Ratio Next Scheduling)
	���� : �� �۾��� �켱������ �����층	
		   �켱���� = (���ð� + CPU ���ð�) / (CPU ���ð�)
		   SJF���� �߻��� �� �ִ� �ƻ� ���� �ذ�
	�Է� : ���μ��� ������, ���μ��� ����
	��� : HRN �����층���� ����
	�� ���μ����� ���ð�, ��� ��� �ð�,
	�� ���μ����� ����ð�, ��� ����ð�,
	�� ���μ����� ��ȯ �ð�, ��� ��ȯ �ð�
*/
#include "Process.h"
#include "View_Table.h"
#include "Function_to_Sorting.h"
#include <Windows.h>
#include <string.h>


void HRN_print_gantt_chart(Process* p, int n,char *check_id)
{	
	textcolor(5);
	printf("\Highest Response Ratio Next\n");

	int check_num = 0; // ó�� ����� PID�� �����ϱ� ���� ����

	for (int i = 0; i < n; i++)
	{
		if (strcmp(check_id, p[i].id) == 0) { // ó�� ����� ���μ��� id�� �޾� ���� ����ü�� �ִ� id �� ���� �ε��� ����
			break;
		}
		check_num++;
	}

	Process_init(tmp, check_num);

	for (int i = 0; i < check_num; i++) {
		tmp[i].arrival_time = 0;
		tmp[i].return_time = 0;
		tmp[i].run_time = 0;
		tmp[i].priority = 0;
		strcpy(tmp[i].id, "");
	}

	for (int i = 0; i < check_num; i++) {
		tmp[i] = p[i]; // ����ü ����
	}

	Process Temp = tmp[check_num]; // Temp�� ����� �ε����� �ش��ϴ� ���μ��� ����

	for (int i = 0; i < check_num; i++) { // ���� ���� ����� ���μ����� �� ������ ������ ���ؼ� ����ü �迭�� �ڷ� �δ�.
		p[i + 1] = tmp[i];
	}

	p[0] = Temp; // �����صξ��� ���μ����� �ٽ� ����ü ù ��° �ε����� ����


	printf("��");
	/* ��� �� ��� */
	for (int i = 0; i < n; i++){
		for (int j = 0; j < p[i].run_time; j++)
			printf("����");

		if (i == n - 1)
			printf("��");
		else
			printf("��");

	}

	printf("\n��");

	/* ���μ��� �̸� ��� */
	for (int i = 0; i < n; i++){
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
	for (int i = 0; i < n; i++){
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

	for (int i = 0; i < n; i++){
		for (int j = 0; j < p[i].run_time; j++)
			printf("  ");

		if (p[i].return_time > 9)
			printf("\b");

		printf("%d", p[i].return_time);

	}

	printf("\n");
}

void HRN_Scheduling(Process* p, int n) {
	float current_time = 0.0;
	int priority_index; // �켱������ ������ �ε���
	int total_waiting_time = 0; // �� ���μ��� ��� �ð�
	int total_turnAround_time = 0; // �� ���μ��� �ҿ� �ð�
	int total_response_time = 0; // �� ���μ��� ���� �ð�
	int total_run_time = 0; // �� ���μ��� ���� �ð�

	double hrr, temp; // �켱���� ���� ����, �Ҽ��� ����

	Process_init(p, n);

	for (int i = 0; i < n; i++)	{
		total_run_time += p[i].run_time; // �� ���� �ð��� ���
	}

	qsort_arrival_time(p, n);
	
	char check_id[10];
	strcpy(check_id, p[0].id); // ���� ó������ ���� PID ����

	current_time = p[0].arrival_time; // ���� �ð��� ù ���μ����� ������ �ð�

	while(current_time < total_run_time){ // ������ ���� �ð��� �� ���μ��� �ð����� ũ�ٸ� ��� ���μ����� ������.
		hrr = -9999.0;
		for (int i = 0; i < n; i++){
			if ((p[i].arrival_time <= current_time) && (p[i].completed == false)) {// ���� ó�� ���� ���μ��� ���� ����
				temp = (p[i].run_time + (current_time - p[i].arrival_time)) / p[i].run_time;
				// (����ð� + ���ð�) / ����ð� ���� �켱���� ���
				if (hrr < temp){ // �켱���� ����
					hrr = temp;
					priority_index = i; // �ش� �ε����� ����
				}
			}
		}

		current_time += p[priority_index].run_time; // ���� �ð� ����

		p[priority_index].waiting_time = current_time - p[priority_index].arrival_time - p[priority_index].run_time;
		p[priority_index].turnAround_time = current_time - p[priority_index].arrival_time;
		p[priority_index].return_time = p[priority_index].turnAround_time + p[priority_index].arrival_time;
		p[priority_index].response_time = p[priority_index].waiting_time;
		p[priority_index].completed = true;

		total_waiting_time += p[priority_index].waiting_time;
		total_turnAround_time += p[priority_index].turnAround_time;
		total_response_time += p[priority_index].response_time;

	}

	qsort_run_time(p, n);
	
	HRN_print_gantt_chart(p, n, check_id);

	view_table(p, n);
	/* ��� ���ð�, �Ͼ���� Ÿ��, ���� �ð� ��� */
	printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)n);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnAround_time / (double)n);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)n);
}

#endif __HRN__
