#ifndef __SRT__
#define __SRT__

/*
	헤더명 : SRT.h(Shortest Remaining Time Scheduling)
	내용 : CPU를 할당받을 프로세스를 선택할 때 남아 있는 작업 시간이 가장 적은 프로세스를 선택
	입력 : 프로세스 포인터, 프로세스 갯수
	출력 : SJF 스케쥴링으로 인한
	각 프로세스별 대기시간, 평균 대기 시간,
	각 프로세스별 응답시간, 평균 응답시간,
	각 프로세스별 반환 시간, 평균 반환 시간
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
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}

	int* check_response = (int*)malloc(sizeof(int) * n);
	check_response = (int*)malloc(sizeof(int) * n);
	if (check_response == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}

	for (int i = 0; i < n; i++){
		check_response[i] = 0; // 
		remain_run_time[i] = p[i].run_time;
		total_run_time += p[i].run_time;
	}

	/* 현재 시간이 총 실행 시간이 되기 전까지 반복 */
	while (current_time < total_run_time)	{
		shortest_remain_time = INT_MAX; // 최소작업 인덱스를 INT_MAX로 초기화

		/* 가장 마지막에 들어온 프로세스의 도착시간 보다 작을 경우 */
		if (current_time <= p[n - 1].arrival_time) {
			for (int i = 0; i < n; i++) {
				/* 완료되지 않았으며 도착시간이 현재시간보다 작거나 같으며 현재 최소작업 시간보다 남은 실행시간이 작을 경우 */
				if ((p[i].completed == false) && (p[i].arrival_time <= current_time) && (shortest_remain_time > remain_run_time[i])){
					shortest_remain_time = remain_run_time[i]; // 최소 작업 시간 갱신
					k = i; // 최소 작업 프로세스 인덱스 갱신
				}
			}
		}
		else
		{
			for (int i = 0; i < n; i++){ // 완료되지 않았으며 현재 최소작업 시간보다  남은 실행시간이 작을 경우 
				if ((p[i].completed == false) && (shortest_remain_time > remain_run_time[i]))  {
					shortest_remain_time = remain_run_time[i]; // 최소 작업 시간 갱신b
					k = i; // 최소 작업 프로세스 인덱스 갱신
				}
			}
		}

		/* 선택된 프로세스가 처음 시작될 경우 */
		if (check_response[k] == 0){
			check_response[k] = 1; // 응답 표시
			p[k].response_time = current_time; // 실행중인 프로세스의 응답시간 저장
		}

		remain_run_time[k]--;
		// 실행된 프로세스의 남은 시간 감소
		current_time++;
		// 현재 시간 증가

		/* 프로세스의 남은 실행 시간이 0이될 경우 */
		if (remain_run_time[k] == 0){
			p[k].completed = true; // 완료 상태로 변경
			p[k].waiting_time = current_time - p[k].run_time - p[k].arrival_time; // 대기 시간 계산	
			p[k].return_time = current_time; // 반환 시간 계산
		}
	}

	/* 동적 할당한 배열의 메모리 할당 해제 */
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

	printf("┏");
	while (current_time < total_run_time) {
		shortest_remain_time = INT_MAX;
		if (current_time <= p[n - 1].arrival_time) { // if - a
			for (int i = 0; i < n; i++) {
				if ((p[i].completed == false) && (p[i].arrival_time <= current_time)){
					if (shortest_remain_time > remain_run_time[i]) {
						shortest_remain_time = remain_run_time[i]; // 최소 작업 시간 갱신
						k = i; // 최소 작업 프로세스 인덱스 갱신
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


		printf("━━");


		remain_run_time[k]--;
		current_time++;
		pre_k = k;

		if (remain_run_time[k] == 0) {
			for (int i = 0; i < n / 2; i++)
				printf("━━");
			p[k].completed == true;
		}
	}
	printf("┓");

	for (int i = 0; i < n; i++)
	{
		remain_run_time[i] = p[i].run_time;
		p[i].completed = false;
	}

	current_time = 0;
	printf("\n┃");
	while (current_time <= total_run_time){
		if (current_time != total_run_time){ // 현재 시간이 총 실행시간과 다를 경우 
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
				if (pre_k != k){ // 이전 프로세스와 다른 경우
					distance = check_response[pre_k] + 1; // 두 프로세스 시간 차이 저장					
					check_response[pre_k] = 0; // 이전 프로세스 카운트 초기화					
					check_response[k]++; // 현재 프로세스 카운트 증가
					
					for (int i = 0; i < distance; i++)
						printf("\b");

					printf("%s", p[pre_k].id);

					for (int i = 0; i < distance - 2; i++)
						printf(" ");

					printf("┃  ");
				}

				/* 같은 프로세스일 경우 */
				else
				{
					check_response[k]++; // 현재 프로세스 카운트 증가
					printf("  "); 
					
				}
			}

			pre_k = k;
			remain_run_time[k]--;
			current_time++;

			if (remain_run_time[k] == 0)
				p[k].completed = true;
		}
		else // 현재 실행시간이 총 실행시간과 같을 경우
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
	printf("┃\n");

	/* 동일 알고리즘을 사용하여 하단 바 출력 */
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

		printf("━━");

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
	printf("┛\n");

	/* 프로세스 ID 출력과 같은 알고리즘으로 실행하며 시간 출력 */
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

	/* 동적 할당한 배열 메모리 할당 해제 */
	free(check_response);
	free(remain_run_time);
}

void SRT_Scheduling(Process* p, int pc) {
	int total_waiting_time = 0; // 총 프로세스 대기 시간
	int total_turnAround_time = 0; // 총 프로세스 소요 시간
	int total_response_time = 0; // 총 프로세스 응답 시간

	Process_init(p, pc);

	qsort_arrival_time(p, pc);

	SRT_Process_System(p, pc);

	for (int i = 0; i < pc ; i++) {
		p[i].turnAround_time = p[i].return_time - p[i].arrival_time; // 각 프로세스 소요 시간 계산
		total_waiting_time += p[i].waiting_time; // 총 대기시간 저장
		total_turnAround_time += p[i].turnAround_time; // 총 소요시간 
		total_response_time += p[i].response_time;
	}
	printf("\tShortest Remaining Time Algorithm\n");
	SRT_print_gantt_chart(p, pc);

	printf("\n");
	view_table(p, pc);
	printf("\n");

	printf("Average Total Waiting time = %.2lf\n", (double)total_waiting_time / (double)pc); // 평균 대기 시간
	printf("Average Total turnAround time = %.2lf\n", (double)total_turnAround_time / (double)pc); // 평균 반환 시간
	printf("Average Total Response time = %.2lf\n", (double)total_response_time / (double)pc); // 평균 응답 시간
}

#endif __SRT__


