#ifndef __SRT__
#define __SRT__

/*
	����� : SRT.h(Shortest Remaining Time Scheduling)
	���� : CPU�� �Ҵ���� ���μ����� ������ �� ���� �ִ� �۾� �ð��� ���� ���� ���μ����� ����
	�Է� : ���μ��� ������, ���μ��� ����
	��� : SJF �����층���� ����
	�� ���μ����� ���ð�, ��� ��� �ð�,
	�� ���μ����� ����ð�, ��� ����ð�,
	�� ���μ����� ��ȯ �ð�, ��� ��ȯ �ð�
*/

#include "Process.h"
#include "View_Table.h"
#include "Function_to_Sorting.h"

void SRT_Process_System(Process* p, int n) {
	textcolor(10);
	int current_time = 0;

	int total_run_time = 0;

	int shortest_remain_time;

	int k = 0;

	int* remain_run_time = NULL;
	remain_run_time = (int*)malloc(sizeof(int) * n);
	if (remain_run_time == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}

	int* check_response = (int*)malloc(sizeof(int) * n);
	check_response = (int*)malloc(sizeof(int) * n);
	if (check_response == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}

	for (int i = 0; i < n; i++){
		check_response[i] = 0; // 
		remain_run_time[i] = p[i].run_time;
		total_run_time += p[i].run_time;
	}

	/* ���� �ð��� �� ���� �ð��� �Ǳ� ������ �ݺ� */
	while (current_time < total_run_time)	{
		shortest_remain_time = INT_MAX; // �ּ��۾� �ε����� INT_MAX�� �ʱ�ȭ

		/* ���� �������� ���� ���μ����� �����ð� ���� ���� ��� */
		if (current_time <= p[n - 1].arrival_time) {
			for (int i = 0; i < n; i++) {
				/* �Ϸ���� �ʾ����� �����ð��� ����ð����� �۰ų� ������ ���� �ּ��۾� �ð����� ���� ����ð��� ���� ��� */
				if ((p[i].completed == false) && (p[i].arrival_time <= current_time) && (shortest_remain_time > remain_run_time[i])){
					shortest_remain_time = remain_run_time[i]; // �ּ� �۾� �ð� ����
					k = i; // �ּ� �۾� ���μ��� �ε��� ����
				}
			}
		}
		else
		{
			for (int i = 0; i < n; i++){ // �Ϸ���� �ʾ����� ���� �ּ��۾� �ð�����  ���� ����ð��� ���� ��� 
				if ((p[i].completed == false) && (shortest_remain_time > remain_run_time[i]))  {
					shortest_remain_time = remain_run_time[i]; // �ּ� �۾� �ð� ����b
					k = i; // �ּ� �۾� ���μ��� �ε��� ����
				}
			}
		}

		/* ���õ� ���μ����� ó�� ���۵� ��� */
		if (check_response[k] == 0){
			check_response[k] = 1; // ���� ǥ��
			p[k].response_time = current_time; // �������� ���μ����� ����ð� ����
		}

		remain_run_time[k]--;
		// ����� ���μ����� ���� �ð� ����
		current_time++;
		// ���� �ð� ����

		/* ���μ����� ���� ���� �ð��� 0�̵� ��� */
		if (remain_run_time[k] == 0){
			p[k].completed = true; // �Ϸ� ���·� ����
			p[k].waiting_time = current_time - p[k].run_time - p[k].arrival_time; // ��� �ð� ���	
			p[k].return_time = current_time; // ��ȯ �ð� ���
		}
	}

	/* ���� �Ҵ��� �迭�� �޸� �Ҵ� ���� */
	free(check_response);
	free(remain_run_time);
}

void SRT_print_gantt_chart(Process* p, int n) {
	int current_time = 0, previous_time = 0;

	int total_run_time = 0;

	int shortest_remain_time, distance;

	int k, pre_k = 0;

	int* remain_run_time = (int*)malloc(sizeof(int) * n);

	int* check_response = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		check_response[i] = 0;
		remain_run_time[i] = p[i].run_time;
		total_run_time += p[i].run_time;
		p[i].completed = false;
	}

	printf("��");
	while (current_time < total_run_time) {
		shortest_remain_time = INT_MAX;
		if (current_time <= p[n - 1].arrival_time) { // if - a
			for (int i = 0; i < n; i++) {
				if ((p[i].completed == false) && (p[i].arrival_time <= current_time)){
					if (shortest_remain_time > remain_run_time[i]) {
						shortest_remain_time = remain_run_time[i]; // �ּ� �۾� �ð� ����
						k = i; // �ּ� �۾� ���μ��� �ε��� ����
					}
				}
			}
		}
		else { // else - a
			for (int i = 0; i < n; i++) {
				if (p[i].completed == false){
					if (shortest_remain_time > remain_run_time[i]) {
						shortest_remain_time = remain_run_time[i];
						k = i;
					}
				}
			}
		}
		if (pre_k != k)
			printf(" ");


		printf("����");


		remain_run_time[k]--;
		current_time++;
		pre_k = k;

		if (remain_run_time[k] == 0) {
			for (int i = 0; i < n / 2; i++)
				printf("����");
			p[k].completed == true;
		}
	}
	printf("��");

	for (int i = 0; i < n; i++)
	{
		remain_run_time[i] = p[i].run_time;
		p[i].completed = false;
	}

	current_time = 0;
	printf("\n��");
	while (current_time <= total_run_time){
		if (current_time != total_run_time){ // ���� �ð��� �� ����ð��� �ٸ� ��� 
			shortest_remain_time = INT_MAX;
			if (current_time <= p[n - 1].arrival_time){ // if - a
				for (int i = 0; i < n; i++){
					if ((p[i].completed == false) && (p[i].arrival_time <= current_time )&& (shortest_remain_time > remain_run_time[i])){
						shortest_remain_time = remain_run_time[i];
						k = i;
					}
				}
			}
			else // end - a
			{
				for (int i = 0; i < n; i++){
					if ((p[i].completed == false) && (shortest_remain_time > remain_run_time[i])){
						shortest_remain_time = remain_run_time[i];
						k = i;
					}
				}
			}

			if (current_time == 0)
			{
				check_response[k]++;
				printf("  ");
			}
			else
			{
				if (pre_k != k){ // ���� ���μ����� �ٸ� ���
					distance = check_response[pre_k] + 1; // �� ���μ��� �ð� ���� ����					
					check_response[pre_k] = 0; // ���� ���μ��� ī��Ʈ �ʱ�ȭ					
					check_response[k]++; // ���� ���μ��� ī��Ʈ ����
					
					for (int i = 0; i < distance; i++)
						printf("\b");

					printf("%s", p[pre_k].id);

					for (int i = 0; i < distance - 2; i++)
						printf(" ");

					printf("��  ");
				}

				/* ���� ���μ����� ��� */
				else
				{
					check_response[k]++; // ���� ���μ��� ī��Ʈ ����
					printf("  "); 
					
				}
			}

			pre_k = k;
			remain_run_time[k]--;
			current_time++;

			if (remain_run_time[k] == 0)
				p[k].completed = true;
		}
		else // ���� ����ð��� �� ����ð��� ���� ���
		{
			for (int i = 0; i < check_response[pre_k] + 1; i++)
				printf("\b");
			printf("%s", p[k].id);
			for (int i = 0; i < check_response[pre_k] - 1; i++)
				printf(" ");

			break;
		}
	}
	for (int i = 0; i < check_response[pre_k] - (check_response[pre_k] / 2 ); i++)
		printf("\b");
	for (int i = 0; i < n - 1; i++)
		printf("\b");


	for (int i = 0; i < n; i++){
		remain_run_time[i] = p[i].run_time;
		p[i].completed = false;
	}

	current_time = 0;
	printf("��\n");

	/* ���� �˰����� ����Ͽ� �ϴ� �� ��� */
	while (current_time < total_run_time){
		shortest_remain_time = INT_MAX;
		if (current_time <= p[n - 1].arrival_time){
			for (int i = 0; i < n; i++){
				if ((p[i].completed == false) && (p[i].arrival_time <= current_time) && (shortest_remain_time > remain_run_time[i])){
					shortest_remain_time = remain_run_time[i];
					k = i;
				}
			}
		}
		else
		{
			for (int i = 0 ; i < n; i++){
				if ((p[i].completed == false) && (shortest_remain_time > remain_run_time[i])){
					shortest_remain_time = remain_run_time[i];
					k = i;
				}
			}
		}

		if (pre_k != k)
			printf(" ");

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
	printf("��\n");

	/* ���μ��� ID ��°� ���� �˰������� �����ϸ� �ð� ��� */
	while (current_time <= total_run_time){
		if (total_run_time != current_time){
			shortest_remain_time = INT_MAX;

			if (current_time <= p[n - 1].arrival_time){
				for (int i = 0; i < n; i++){
					if ((p[i].completed == false) && (p[i].arrival_time <= current_time) && (shortest_remain_time > remain_run_time[i])){
						shortest_remain_time = remain_run_time[i];
						k = i;
					}
				}
			}
			else
			{
				for (int i = 0; i < n; i++){
					if ((p[i].completed == false) && (shortest_remain_time > remain_run_time[i])){
						shortest_remain_time = remain_run_time[i];
						k = i;
					}
				}
			}


			if (pre_k != k)
			{
				for (int i = 0; i < distance && current_time != 0; i++)
					printf("  ");

				if (current_time != 0)
					printf(" ");

				printf("%-2d", current_time);
				distance = 0;

				previous_time = current_time;
			}

			else
				distance++;

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

			printf("%-2d", current_time);

			break;
		}
	}

	printf("\n");

	/* ���� �Ҵ��� �迭 �޸� �Ҵ� ���� */
	free(check_response);
	free(remain_run_time);
}

void SRT_Scheduling(Process* p, int pc) {
	int total_waiting_time = 0; // �� ���μ��� ��� �ð�
	int total_turnAround_time = 0; // �� ���μ��� �ҿ� �ð�
	int total_response_time = 0; // �� ���μ��� ���� �ð�

	Process_init(p, pc);

	qsort_arrival_time(p, pc);

	SRT_Process_System(p, pc);

	for (int i = 0; i < pc ; i++) {
		p[i].turnAround_time = p[i].return_time - p[i].arrival_time; // �� ���μ��� �ҿ� �ð� ���
		total_waiting_time += p[i].waiting_time; // �� ���ð� ����
		total_turnAround_time += p[i].turnAround_time; // �� �ҿ�ð� 
		total_response_time += p[i].response_time;
	}
	printf("\tShortest Remaining Time Algorithm\n");
	SRT_print_gantt_chart(p, pc);

	printf("\n");
	view_table(p, pc);
	printf("\n");

	printf("Average Total Waiting time = %.2lf\n", (double)total_waiting_time / (double)pc); // ��� ��� �ð�
	printf("Average Total turnAround time = %.2lf\n", (double)total_turnAround_time / (double)pc); // ��� ��ȯ �ð�
	printf("Average Total Response time = %.2lf\n", (double)total_response_time / (double)pc); // ��� ���� �ð�
}

#endif __SRT__


