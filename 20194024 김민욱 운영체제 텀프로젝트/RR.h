#ifndef	__RR__
#define __RR__
/*
	����� : RR.h(Round Robin Scheduling)
	���� : �� ���μ����� �Ҵ���� �ð�(Ÿ�� �����̽�Time Slice/Time Quantum) 
	       �����۾��� �ϴٰ� �۾��� �Ϸ����� ���ϸ� �غ� ť�� �� �ڷ� ���� �ڱ� ���ʸ� ��ٸ��� ���
	�Է� : ���μ��� ������, ���μ��� ���� , Ÿ�� �����̽�(����)
	��� : RR �����층���� ����
	�� ���μ����� ���ð�, ��� ��� �ð�,
	�� ���μ����� ����ð�, ��� ����ð�,
	�� ���μ����� ��ȯ �ð�, ��� ��ȯ �ð�
*/

#include "Process.h"
#include <Windows.h>
#include "View_Table.h"
#include "Function_to_Sorting.h"

void RR_Process_Waiting_Time(Process* p, int n, Quantum quantum) { // ��� �ð� ��� �Լ�
	int current_time = 0; // ����ð� �ʱ�ȭ
	int total_run_time = 0; // �� ����ð� �ʱ�ȭ
	int* remain_run_time = NULL;
	remain_run_time = (int*)malloc(sizeof(int) * n); // ���� �ð� ���� �迭 �Ҵ�

	if (remain_run_time == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}
	
	bool* check_response_time = NULL;
	check_response_time = (bool*)malloc(sizeof(bool) * n); // ���� �ð� ó�� Ȯ�� �迭 �Ҵ�

	if (check_response_time == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}

	
	for (int i = 0; i < n;i++) {
		remain_run_time[i] = p[i].run_time; // �� ���μ����� �����ð� ����
		check_response_time[i] = false; // ���μ��� ���� �ʱ�ȭ
		total_run_time += p[i].run_time; // �� ����ð� ���
	}
	while (true) { // ��� ���μ����� �Ϸ�� �� ���� �ݺ�
		bool check = true;
		for (int i = 0; i < n; i++) {
			if (remain_run_time[i] > 0) { // ���� �ð��� ���� �ִ� ���
				check = false;

				if (check_response_time[i] == false) { // ���� �ð� ó�� ���� ���
					p[i].response_time = current_time - p[i].arrival_time; // ����ð� ���
					check_response_time[i] = true;
				}

				if (remain_run_time[i] > quantum) { // ���� �ð��� Ÿ�� �����̽� ���� Ŭ ���
					current_time += quantum; // ���� �ð� ����
					remain_run_time[i] -= quantum; // ���� �������� ���μ��� ���� �ð� ����
				}
				else { // ���� �ð��� Ÿ�� �����̽� ���� ���� ���
					current_time += remain_run_time[i]; // ����ð� ����
					p[i].waiting_time = current_time - p[i].run_time; // ���ð� ���
					remain_run_time[i] = 0; // �۾� ���� ���μ��� ���� �ð� 0���� �ʱ�ȭ
				}
			}
		}
		
		if (check == true) // ���� �ִ� ���μ����� ���� ���
			break;
	}
	/* �����Ҵ��� �޸� ���� */
	free(remain_run_time);
	free(check_response_time);
}

void RR_Process_TurnAround_Time(Process* p, int n) { // �ҿ� �ð� ��� �Լ�
	for (int i = 0; i < n; i++) {
		p[i].turnAround_time = p[i].run_time + p[i].waiting_time - p[i].arrival_time;
	}
}

	/* ���ð� ��� �Լ� �˰���� ���� */
void RR_print_gantt_chart(Process* p, int n, Quantum quantum) 
{
	textcolor(8);

	int current_time = 0, total_run_time = 0; // ���� �ð��� �� ���� �ð��� ������ ����

	int* remain_run_time = NULL;
	remain_run_time = (int*)malloc(sizeof(int) * n);

	if (remain_run_time == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}

	for (int i = 0; i < n; i++){
		remain_run_time[i] = p[i].run_time;
		total_run_time += p[i].run_time;
	}

	printf("��");

	/* ��� �� ��� */
	while (true){
		bool check = true;
		for (int i = 0; i < n; i++){
			if (remain_run_time[i] > 0){
				check = false;
				if (remain_run_time[i] < quantum){
					for (int j = 0; j < remain_run_time[i]; j++)
						printf("");
				}else{
					for (int j = 0; j < quantum ; j++)
						printf("����");
				}
				
				if (remain_run_time[i] > quantum){
					current_time += quantum;
					remain_run_time[i] -= quantum;
					printf("����");
				}else{
					current_time += remain_run_time[i];
					p[i].waiting_time = current_time - p[i].run_time;
					remain_run_time[i] = 0;
				}
			}
		}
		if (check == true)
			break;
	}

	printf("��\n");

	for (int i = 0; i < n; i++){
		remain_run_time[i] = p[i].run_time;
	}

	/* ���μ��� ���̵� ��� */
	while (true){
		int check = true;
		for (int i = 0; i < n; i++){
			if (remain_run_time[i] > 0){
				check = false;
				if (remain_run_time[i] < quantum){
					printf(" | ");
					if (remain_run_time[i] != 1){
						printf(" %s ", p[i].id);
					}
					else {
						printf(" %s ", p[i].id);
					}
				}else{
					printf("��");
					printf(" %s ", p[i].id);
				}

				if (remain_run_time[i] > quantum){
					current_time += quantum;
					remain_run_time[i] -= quantum;
				}else
				{
					current_time += remain_run_time[i];
					p[i].waiting_time = current_time - p[i].run_time;
					remain_run_time[i] = 0;
				}
			}
		}

		if (check == true)
			break;
	}

	printf("��\n");

	for (int i = 0; i < n; i++){
		remain_run_time[i] = p[i].run_time;
	}


	printf("��");

	/* �ϴ� �� ��� */
	while (true){
		bool check = true;
		for (int i = 0; i < n; i++){
			if (remain_run_time[i] > 0){
				check = false;

				if (remain_run_time[i] < quantum){
					for (int j = 0; j < remain_run_time[i]; j++) {
						printf("1");
					}
				}else{
					for (int j = 0; j < quantum; j++) {
						printf("����");
					}
				}

				if (remain_run_time[i] > quantum){
					current_time += quantum;
					remain_run_time[i] -= quantum;
					printf("����");
				}else{
					current_time += remain_run_time[i];
					p[i].waiting_time = current_time - p[i].run_time;
					remain_run_time[i] = 0;
				}
			}
		}

		if (check == true)
			break;
	}

	printf("��\n");
	for (int i = 0; i < n; i++)
		remain_run_time[i] = p[i].run_time;

	current_time = 0;

	/* ���μ��� �ð� ��� */
	while (true){
		int check = true;

		for (int i = 0; i < n; i++){
			if (remain_run_time[i] > 0){
				check = false;

				if (remain_run_time[i] < quantum){
					printf("%2d", current_time);
				}else{
					printf("%2d", current_time);

					for (int j = 0; j < quantum / 2; j++) {
						printf("   ");
					}
				}
				if (remain_run_time[i] > quantum){
					current_time += quantum;
					remain_run_time[i] -= quantum;
				}else{
					current_time += remain_run_time[i];
					p[i].waiting_time = current_time - p[i].run_time;
					remain_run_time[i] = 0;
				}
			}
		}

		if (check == true)
			break;
	}

	printf("%d", total_run_time);

	printf("\n");

	free(remain_run_time);
	// ���� �Ҵ��� �迭�� �޸� �Ҵ� ����
}

void RR_Scheduling(Process* p, int pc, Quantum quantum) {
	
	int total_waiting_time = 0; // �� ���μ��� ��� �ð�
	int total_turnAround_time = 0; // �� ���μ��� �ҿ� �ð�
	int total_response_time = 0; // �� ���μ��� ���� �ð�

	Process_init(p, pc);

	qsort_arrival_time(p, pc);

	RR_Process_Waiting_Time(p, pc, quantum);

	RR_Process_TurnAround_Time(p, pc);

	for (int i = 0; i < pc; i++){
		p[i].waiting_time = p[i].turnAround_time - p[i].run_time; // ��� �ð� ��� �� ����
		p[i].return_time = p[i].arrival_time + p[i].run_time + p[i].waiting_time; // ��ȯ �ð� ��� �� ����

		total_waiting_time += p[i].waiting_time; // �� ��� �ð� ����
		total_turnAround_time += p[i].turnAround_time; // �� �ҿ� �ð�  ����
		total_response_time += p[i].response_time; // �� ���� �ð� ����
	}
	
	printf("Round Robin Scheduling\n");

	RR_print_gantt_chart(p, pc, quantum);

	view_table(p, pc);
	printf("\n");

	printf("Average Total Waiting time = %.2lf\n", (double)total_waiting_time / (double)pc); // ��� ��� �ð�
	printf("Average Total turnAround time = %.2lf\n", (double)total_turnAround_time / (double)pc); // ��� ��ȯ �ð�
	printf("Average Total Response time = %.2lf\n", (double)total_response_time / (double)pc); // ��� ���� �ð�

}
#endif