#ifndef __PPS__
#define __PPS__

/*
	����� : PPS.h(Preemptive Priority Scheduling)
	���� : ���� �������� ���μ������� ���� �켱������ ���μ����� �����ϸ� �����ٷ��� ���� ������� ������ �ﰢ������ ������(������)
	�Է� : ���μ��� ������, ���μ��� ����
	��� : PPS �����층���� ����
	�� ���μ����� ���ð�, ��� ��� �ð�,
	�� ���μ����� ����ð�, ��� ����ð�,
	�� ���μ����� ��ȯ �ð�, ��� ��ȯ �ð�
*/

/*
if priority(current_process) > priority(prior_process) :- then execute the current process.
if priority(current_process) < priority(prior_process) :- then execute the prior process.
if priority(current_process) = priority(prior_process) :- then execute the process which arrives
*/

#include "Process.h"
#include <Windows.h>
#include "View_Table.h"
#include "Function_to_Sorting.h"

void PPS_print_gantt_chart(Process* p, int n) {
	printf("\tPreemptive Priority Scheduling\n");
	int current_time = 0, previous_time = 0; // ���� ���μ��� �ð��� ���� ���μ��� �ð� ����
	int total_run_time = 0; // �� ���� �ð��� ������ ���� 
	int k = 0, pre_k= 0;// ����� ���� ���μ��� ��ȣ

	int priority, distance; // �켱������ �� ���μ����� �Ÿ��� ��Ÿ�� ����

	int* remain_run_time = NULL;
	remain_run_time = (int*)malloc(sizeof(int) * n); // �����ð��� ������ �迭 ���� �Ҵ�

	if (remain_run_time == NULL) {      // �޸� �Ҵ� ����
		printf("Not enough memory!");     // ���� ��Ȳ �˸�
		return -1;                        // �Լ� ����
	}

	int* response = NULL;
	response = (int*)malloc(sizeof(int) * n); // ���� �ð��� Ȯ���� �迭 ���� �Ҵ� 

	if (response == NULL) {    // �޸� �Ҵ� ����
		printf("Not enough memory!");     // ���� ��Ȳ �˸�
		return -1;                        // �Լ� ����
	}

	for (int i = 0; i < n; i++) {
		response[i] = 0;
		remain_run_time[i] = p[i].run_time;
		total_run_time += p[i].run_time;
		p[i].completed = false; // �Ϸ���� �ʱ�ȭ
	}
	/* ��� �� ��� */
	printf("��");
	while (current_time < total_run_time) // ����ð��� �� ����ð����� ������ ���� �ݺ�
	{
		priority = INT_MAX; // �켱���� �ʱ�ȭ

		if (current_time <= p[n - 1].arrival_time){ // ��� ���μ����� ������ �� ���� ���
			for (int i = 0; i < n; i++){
				if ((p[i].completed == false) && (p[i].arrival_time <= current_time)) { // �Ϸ���� �ʾҰ� �����ð��� ����ð����� �������
					if (priority > p[i].priority){ // �켱���� ����
						priority = p[i].priority; 
						k = i; // �ش� �ε��� ����
					}
				}
			}
		}else{ // ��� ���μ��� ������ ���
			for (int i = 0; i < n; i++){
				if (p[i].completed == false){ // �Ϸ���� ���� ���μ����� ���Ͽ�
					if (priority > p[i].priority){ // �켱���� ����
						priority = p[i].priority;
						k = i;
					}
				}
			}
		}

		if (pre_k != k) { // ���� ���μ����� ���� ���μ����� ���� �������
			if (current_time == 0) {
				printf(" ");
			}
			else {
				printf("��");
			}
		}

		printf("����");

		remain_run_time[k]--; // ���� ����ð� ����
		current_time++; // ����ð� ����
		pre_k = k; // ���� ���μ����� ����(���Ḯ��Ʈ ó�� Ȱ��)

		if (remain_run_time[k] == 0) // ���� �ð��� ���°��
			p[k].completed = true; // �Ϸ�ǥ��
	}

	/* ����� ���� �ʱ�ȭ ���� ���� */
	for (int i = 0; i < n; i++){
		remain_run_time[i] = p[i].run_time;
		p[i].completed = false;
	}
	printf("��");
	printf("\n�� ");
	current_time = 0;

	/* ���μ��� ID ��� (��� ��� �˰���� ���� )*/
	while (current_time < total_run_time){
		priority = INT_MAX;
		if (current_time <= p[n - 1].arrival_time){
			for (int i = 0; i < n; i++){
				if ((p[i].completed == false) && (p[i].arrival_time <= current_time)){
					if (priority > p[i].priority){
						priority = p[i].priority;
						k = i;
					}
				}
			}
		}else{
			for (int i = 0; i < n; i++){
				if (p[i].completed == false){
					if (priority > p[i].priority){
						priority = p[i].priority;
						k = i;
					}
				}
			}
		}
		if (current_time == 0){
			response[k]++;
			printf("  ");
		}else{	
			if (pre_k != k){ // �ٸ� ���μ��� �� ���
				distance = response[pre_k] + 1; // �� ���μ��� �ð� ���� ����
				response[pre_k] = 0; // ���� ���μ��� ī��Ʈ �ʱ�ȭ
				response[k]++; // ���� ���μ��� ī��Ʈ ����

				for (int i = 0; i < distance ; i++) // ������ ���߾� ���� ��� 
						printf("\b");

				printf("%2s", p[pre_k].id); // ���� ���μ��� ID ��� 

				for (int i = 0; i < distance - 2; i++) // ������ ���߾� ���� ��� 
					printf(" ");

				printf("��  ");
			}else // ���� ���μ����� ��� 
			{		
				response[k]++; // ���� ���μ��� ����
				printf("  "); // ���� ���
				/* ������ ���μ��� ������ ��� */
				if (current_time == total_run_time - 1){
					distance = response[pre_k] + 1;
					response[pre_k] = 0;
					response[k]++;

					for (int i = 0; i < distance; i++) {
						printf("\b");
					}

					printf("%2s", p[pre_k].id);

					for (int i = 0; i < distance - 2; i++) {
						printf(" ");
					}
				}
			}
		}
		
		pre_k = k;
		remain_run_time[k]--;
		current_time++;

		if (remain_run_time[k] == 0)
			p[k].completed = true;
	}

	/* ����� ���� �ʱ�ȭ ���� ���� */
	for (int i = 0; i < n; i++){
		remain_run_time[i] = p[i].run_time;
		p[i].completed = false;
	}
	current_time = 0;
	printf("��");
	printf("\n");
	printf("��");

	/* �ϴ� ��� (��� ��� �˰���� ����)*/
	while (current_time < total_run_time){
		priority = INT_MAX;

		if (current_time <= p[n - 1].arrival_time){
			for (int i = 0; i < n; i++){
				if ((p[i].completed == false) && (p[i].arrival_time <= current_time)){
					if (priority > p[i].priority){
						priority = p[i].priority;
						k = i;
					}
				}
			}
		}else{
			for (int i = 0; i < n; i++){
				if (p[i].completed == false){
					if (priority > p[i].priority){
						priority = p[i].priority;
						k = i;
					}
				}
			}
		}

		if (pre_k != k) {
			if (current_time == 0) {
				printf(" ");
			}
			else {
				printf("��");
			}
		}
		printf("����");

		remain_run_time[k]--;
		current_time++;
		pre_k = k;

		if (remain_run_time[k] == 0)
			p[k].completed = true;
	}

	for (int i = 0; i < n; i++){
		remain_run_time[i] = p[i].run_time;
		p[i].completed = false;
	}

	current_time = 0;
	distance = 0;
	printf("��");
	printf("\n");

	/* ���μ��� ID ��°� ���� ������� �����ϸ� �ð� ��� */
	while (current_time <= total_run_time){
		if (total_run_time != current_time){
			priority = INT_MAX;
			if (current_time <= p[n - 1].arrival_time){
				for (int i = 0; i < n; i++){
					if ((p[i].completed == false) && (p[i].arrival_time <= current_time)){
						if (priority > p[i].priority){
							priority = p[i].priority;
							k = i;
						}
					}
				}
			}else{
				for (int i = 0; i < n; i++){
					if ((p[i].completed == false) && (priority > p[i].priority)){
						priority = p[i].priority;
						k = i;
					}
				}
			}

			if (pre_k != k){
				for (int i = 0; i < distance && current_time != 0; i++)
					printf("  ");

				if (current_time != 0)
					printf(" ");

				printf("%-2d", current_time);
				distance = 0;

				previous_time = current_time;
			}
			else {
				distance++;
			}
			remain_run_time[k]--;
			current_time++;
			pre_k = k;

			if (remain_run_time[k] == 0)
				p[k].completed = true;
		}
		else
		{
			for (int i = 0; i < current_time - previous_time - 1; i++)
				printf("  ");
			printf(" ");

			printf("%2d", current_time);
			
			break;
		}
	}

	printf("\n"); 
	if (response != NULL)
		free(response);
	
	if (remain_run_time != NULL)
		free(remain_run_time);
	
}

void PPS_Process_Time(Process* p, int n) {
	int current_time = 0; // ������� ���� �ð��� ������ ����

	int priority; // �켱������ ������ ���� 
	int total_run_time = 0; // �� ���� �ð��� ������ ���� 
	int k = 0;// ���� ������ ���μ��� ��ȣ

	
	int* remain_run_time = NULL;
	remain_run_time = (int*)malloc(sizeof(int) * n); // �����ð��� ������ �迭 ���� �Ҵ�

	if (remain_run_time == NULL) {      // �޸� �Ҵ� ����
		printf("Not enough memory!");     // ���� ��Ȳ �˸�
		return -1;                        // �Լ� ����
	}

	int* response = NULL;
	response = (int*)malloc(sizeof(int) * n); // ���� �ð��� Ȯ���� �迭 ���� �Ҵ� 

	if (response == NULL) {      // �޸� �Ҵ� ����
		printf("Not enough memory!");     // ���� ��Ȳ �˸�
		return -1;                        // �Լ� ����
	}
	// qsort_arrival_time(p, n);

	for (int i = 0; i < n; i++){
		response[i] = 0;
		remain_run_time[i] = p[i].run_time;
		total_run_time += p[i].run_time;
	}

	/* ���� �ð��� �� ���� �ð��� �Ǳ� ������ �ݺ� */
	while (current_time < total_run_time){ // ���� �ð��� �� ����ð����� ���� ��� �ݺ�

		priority = INT_MAX; // �켱���� �ʱ�ȭ

		if (current_time < p[n - 1].arrival_time) { // ���μ��� ���� �˻�
			for (int i = 0; i < n; i++) {
				/* �Ϸ���� �ʾ����� �����ð��� ����ð����� �۰ų� ������ ���� �켱�������� �켱������ ���� ��� */
				if ((p[i].completed == false) && (p[i].arrival_time <= current_time) && (priority > p[i].priority)) {
					priority = p[i].priority; // �켱���� ����
					k = i;
				}
			}
		}else { // ��� ���μ����� ������ ���
			for (int i = 0; i < n; i++){
				/* �Ϸ���� �ʾ����� ���� �켱�������� �켱������ ���� ��� */
				if ((p[i].completed == false) && (priority > p[i].priority)){
					priority = p[i].priority;
					k = i;	
				}
			}
		}

		// k�� �˰����� ���� ���õ� ���μ���

		
		if (response[k] == 0){ // ���õ� ���μ����� ó�� ���۵� ��� 
			response[k]++; // �ʱ� ������ �ƴ��� ǥ��	
			p[k].response_time = current_time; // �������� ���μ����� ����ð� ����
		}

		remain_run_time[k]--; // k ���μ��� �����ð� ����
		current_time++; // ���� �ð� ����
		

		if (remain_run_time[k] == 0){ // k ���μ����� �Ϸ�� ���
			p[k].completed = true; // �Ϸ� ���·� ����			
			p[k].waiting_time = current_time - p[k].run_time - p[k].arrival_time; // ��� �ð� ���			 
			p[k].return_time = current_time; // ��ȯ �ð� ���
			
		}
	}

	/* ���� �Ҵ��� �迭�� �޸� �Ҵ� ���� */
	free(remain_run_time);
	free(response);
}


void PPS_Scheduling(Process* p, int pc) {
	int total_waiting_time = 0; // �� ���μ��� ��� �ð�
	int total_turnAround_time = 0; // �� ���μ��� �ҿ� �ð�
	int total_response_time = 0; // �� ���μ��� ���� �ð�

	Process_init(p, pc);

	qsort_arrival_time(p, pc);

	PPS_Process_Time(p, pc);

	for (int i = 0; i < pc; i++) {
		p[i].turnAround_time = p[i].return_time - p[i].arrival_time; // �� ���μ��� �ҿ�ð� ���
		total_waiting_time += p[i].waiting_time; // �� ���ð� ����
		total_turnAround_time += p[i].turnAround_time; // �� �ҿ�ð� ����
		total_response_time += p[i].response_time; // �� ����ð� ����
	}

	qsort_return_time(p, pc);

	PPS_print_gantt_chart(p, pc);

	view_table(p, pc);

	printf("\n");
	printf("Average Total Waiting time = %.2lf\n", (double)total_waiting_time / (double)pc); // ��� ��� �ð�
	printf("Average Total turnAround time = %.2lf\n", (double)total_turnAround_time / (double)pc); // ��� ��ȯ �ð�
	printf("Average Total Response time = %.2lf\n", (double)total_response_time / (double)pc); // ��� ���� �ð�
}

#endif __PPS__