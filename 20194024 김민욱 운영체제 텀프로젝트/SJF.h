#ifndef __SJF__
#define __SJF__

/*
	����� : SJF.h(Shortest Job First Scheduling)
	���� : �غ� ť�� �ִ� ���μ��� �߿��� ���� �ð��� ���� ª�� �۾����� CPU�� �Ҵ��ϴ� ������ ���
	�Է� : ���μ��� ������, ���μ��� ����
	��� : SJF �����층���� ����
	�� ���μ����� ���ð�, ��� ��� �ð�,
	�� ���μ����� ����ð�, ��� ����ð�,
	�� ���μ����� ��ȯ �ð�, ��� ��ȯ �ð�
*/
#pragma warning(disable:4996)
#include "Process.h"
#include "View_Table.h"
#include "Function_to_Sorting.h"
#include <string.h>

Process tmp[100];
void SJF_print_gantt_chart(Process* p, int n, char* check_id)
{
	textcolor(3);
	printf("\tShortest Job First Scheduling\n");
	int check_num = 0; // ó�� ����� PID�� �����ϱ� ���� ����

	for (int i = 0; i < n; i++){
		if (strcmp(check_id, p[i].id) == 0) { // ó�� ����� ���μ��� id�� �޾� ���� ����ü�� �ִ� id �� ���� �ε��� ����
			break;
		}
		check_num++;
	}
	// Process* tmp = (Process*)malloc(sizeof(Process) * (check_num)); // ����ü ��ȯ�� ���� �����Ҵ�)
	Process_init(tmp, check_num);
	/*
	for (int i = 0; i < check_num ; i++) {
		tmp[i].arrival_time = 0;
		tmp[i].return_time = 0;
		tmp[i].run_time = 0;
		tmp[i].priority = 0;
		strcpy(tmp[i].id, "");
	}
	*/
	for (int i = 0; i <= check_num; i++) {
		tmp[i] = p[i]; // ����ü ����
	}

	Process Temp = tmp[check_num]; // Temp�� ����� �ε����� �ش��ϴ� ���μ��� ����
	for (int i = 0; i < check_num; i++) { // ���� ���� ����� ���μ����� �� ������ ������ ���ؼ� ����ü �迭�� �ڷ� �δ�.
		p[i + 1] = tmp[i];
	}

	p[0] = Temp; // �����صξ��� ���μ����� �ٽ� ����ü ù ��° �ε����� ����

	// free(tmp);


	printf("��");
	/* ��� ��� */
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

void SJF_Process_Time(Process* p, int n) { // ���μ��� �� �ð� ��� �Լ�
	int current_time = 0; // ������� ���� �ð��� ������ ����

	int min_index = 0; // �ּ� �ð��� ������ �ε��� ����

	/* �����ð��� ���� ���� ���μ��� ���� ���� */
	p[0].return_time = p[0].run_time; // ��ȯ�ð� ����
	p[0].turnAround_time = p[0].run_time - p[0].arrival_time; // �ҿ�ð� = ����ð� - �����ð�
	p[0].waiting_time = 0; // ���ð� 0
	p[0].completed = true; // �Ϸ� ǥ��

	current_time = p[0].run_time; // ���� �ð� ����

	/* p[0]�� �����Ͽ����Ƿ� �ε��� 1���� ���� */
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			if (p[j].completed == true) // �̹� �Ϸ�� ���μ���
				continue;
			else {
				min_index = j; // ���� �������� ���� ���μ���
				break;
			}
		}

		for (int k = 1; k < n; k++) {
			/* �Ϸ���� ���� ���μ����̰� �����ð��� ���� ������ �ð����� ����� �Ѵ�.(���μ��� ���� �Ǵ� ���� �ذ�) ���� �ش� �ε����� �ּ� �ε��� �ٽ� �˻� */
			if (p[k].completed == false && p[k].arrival_time < current_time && p[k].run_time < p[min_index].run_time) { // �ּ� �۾� �ð� ���ǿ� �´� ���μ��� ã��
				min_index = k;
			}
		}

		p[min_index].waiting_time = current_time - p[min_index].arrival_time; // ��� �ð� ���(=����ð�) : FCFS ������ �̷�� �����Ƿ� ���ð� = ����ð�
		p[min_index].completed = true; // �Ϸ� ���� ����

		current_time += p[min_index].run_time; // ���� �ð� ����
		p[min_index].return_time = current_time; // ��ȯ �ð� ����
		p[min_index].turnAround_time = p[min_index].return_time - p[min_index].arrival_time; // �ҿ� �ð� ����
	}
}

void SJF_Scheduling(Process* p, int pc) {
	int total_waiting_time = 0; // �� ���μ��� ��� �ð�
	int total_turnAround_time = 0; // �� ���μ��� �ҿ� �ð�
	int total_response_time = 0; // �� ���μ��� ���� �ð�

	Process_init(p, pc);

	qsort_arrival_time(p, pc); // �����ð� �������� ����

	SJF_Process_Time(p, pc); // �����ð� �������� ���μ��� ���

	char check_id[10];
	strcpy(check_id, p[0].id); // ���� ó������ ���� PID ����

	for (int i = 0; i < pc; i++){
		p[i].return_time = p[i].turnAround_time + p[i].arrival_time;
		p[i].response_time = p[i].waiting_time;

		total_waiting_time += p[i].waiting_time;
		total_turnAround_time += p[i].turnAround_time;
		total_response_time += p[i].response_time;
	}

	qsort_run_time(p, pc); // ���� �ð� ���� ����

	SJF_print_gantt_chart(p, pc, check_id); // ���� �ð� �������� ���

	view_table(p, pc);

	printf("\n");
	printf("Average Total Waiting time = %.2lf\n", (double)total_waiting_time / (double)pc); // ��� ��� �ð�
	printf("Average Total turnAround time = %.2lf\n", (double)total_turnAround_time / (double)pc); // ��� ��ȯ �ð�
	printf("Average Total Response time = %.2lf\n", (double)total_response_time / (double)pc); // ��� ���� �ð�

}

#endif __SJF__