#ifndef __PPS__
#define __PPS__

/*
	헤더명 : PPS.h(Preemptive Priority Scheduling)
	내용 : 현재 실행중인 프로세스보다 높은 우선순위의 프로세스가 등장하면 스케줄러에 의한 실행순서 조정이 즉각적으로 가해짐(선점형)
	입력 : 프로세스 포인터, 프로세스 갯수
	출력 : PPS 스케쥴링으로 인한
	각 프로세스별 대기시간, 평균 대기 시간,
	각 프로세스별 응답시간, 평균 응답시간,
	각 프로세스별 반환 시간, 평균 반환 시간
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
	int current_time = 0, previous_time = 0; // 현재 프로세스 시간과 이전 프로세스 시간 변수
	int total_run_time = 0; // 총 실행 시간을 저장할 변수 
	int k = 0, pre_k= 0;// 현재와 이전 프로세스 번호

	int priority, distance; // 우선순위가 두 프로세스간 거리를 나타낼 변수

	int* remain_run_time = NULL;
	remain_run_time = (int*)malloc(sizeof(int) * n); // 남은시간을 저장할 배열 동적 할당

	if (remain_run_time == NULL) {      // 메모리 할당 실패
		printf("Not enough memory!");     // 오류 상황 알림
		return -1;                        // 함수 종료
	}

	int* response = NULL;
	response = (int*)malloc(sizeof(int) * n); // 응답 시간을 확인할 배열 동적 할당 

	if (response == NULL) {    // 메모리 할당 실패
		printf("Not enough memory!");     // 오류 상황 알림
		return -1;                        // 함수 종료
	}

	for (int i = 0; i < n; i++) {
		response[i] = 0;
		remain_run_time[i] = p[i].run_time;
		total_run_time += p[i].run_time;
		p[i].completed = false; // 완료상태 초기화
	}
	/* 상단 바 출력 */
	printf("┏");
	while (current_time < total_run_time) // 현재시간이 총 실행시간보다 작을때 까지 반복
	{
		priority = INT_MAX; // 우선순위 초기화

		if (current_time <= p[n - 1].arrival_time){ // 모든 프로세스가 도착할 때 까지 계산
			for (int i = 0; i < n; i++){
				if ((p[i].completed == false) && (p[i].arrival_time <= current_time)) { // 완료되지 않았고 도착시간이 현재시간보다 작은경우
					if (priority > p[i].priority){ // 우선순위 갱신
						priority = p[i].priority; 
						k = i; // 해당 인덱스 저장
					}
				}
			}
		}else{ // 모든 프로세스 도착한 경우
			for (int i = 0; i < n; i++){
				if (p[i].completed == false){ // 완료되지 않은 프로세스에 대하여
					if (priority > p[i].priority){ // 우선순위 갱신
						priority = p[i].priority;
						k = i;
					}
				}
			}
		}

		if (pre_k != k) { // 이전 프로세스와 현재 프로세스가 같지 않은경우
			if (current_time == 0) {
				printf(" ");
			}
			else {
				printf("┳");
			}
		}

		printf("━━");

		remain_run_time[k]--; // 남은 실행시간 감소
		current_time++; // 현재시간 증가
		pre_k = k; // 이전 프로세스로 저장(연결리스트 처럼 활용)

		if (remain_run_time[k] == 0) // 남은 시간이 없는경우
			p[k].completed = true; // 완료표시
	}

	/* 출력을 위한 초기화 과정 진행 */
	for (int i = 0; i < n; i++){
		remain_run_time[i] = p[i].run_time;
		p[i].completed = false;
	}
	printf("┓");
	printf("\n┃ ");
	current_time = 0;

	/* 프로세스 ID 출력 (상단 출력 알고리즘과 동일 )*/
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
			if (pre_k != k){ // 다른 프로세스 인 경우
				distance = response[pre_k] + 1; // 두 프로세스 시간 차이 저장
				response[pre_k] = 0; // 이전 프로세스 카운트 초기화
				response[k]++; // 현재 프로세스 카운트 증가

				for (int i = 0; i < distance ; i++) // 간격을 맞추어 공백 출력 
						printf("\b");

				printf("%2s", p[pre_k].id); // 이전 프로세스 ID 출력 

				for (int i = 0; i < distance - 2; i++) // 간격을 맞추어 공백 출력 
					printf(" ");

				printf("┃  ");
			}else // 같은 프로세스일 경우 
			{		
				response[k]++; // 현재 프로세스 증가
				printf("  "); // 공백 출력
				/* 마지막 프로세스 실행일 경우 */
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

	/* 출력을 위한 초기화 과정 진행 */
	for (int i = 0; i < n; i++){
		remain_run_time[i] = p[i].run_time;
		p[i].completed = false;
	}
	current_time = 0;
	printf("┃");
	printf("\n");
	printf("┗");

	/* 하단 출력 (상단 출력 알고리즘과 동일)*/
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
				printf("┻");
			}
		}
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
	distance = 0;
	printf("┛");
	printf("\n");

	/* 프로세스 ID 출력과 같은 방법으로 실행하며 시간 출력 */
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
	int current_time = 0; // 현재까지 누적 시간을 저장할 변수

	int priority; // 우선순위를 저장할 변수 
	int total_run_time = 0; // 총 실행 시간을 저장할 변수 
	int k = 0;// 현재 실행할 프로세스 번호

	
	int* remain_run_time = NULL;
	remain_run_time = (int*)malloc(sizeof(int) * n); // 남은시간을 저장할 배열 동적 할당

	if (remain_run_time == NULL) {      // 메모리 할당 실패
		printf("Not enough memory!");     // 오류 상황 알림
		return -1;                        // 함수 종료
	}

	int* response = NULL;
	response = (int*)malloc(sizeof(int) * n); // 응답 시간을 확인할 배열 동적 할당 

	if (response == NULL) {      // 메모리 할당 실패
		printf("Not enough memory!");     // 오류 상황 알림
		return -1;                        // 함수 종료
	}
	// qsort_arrival_time(p, n);

	for (int i = 0; i < n; i++){
		response[i] = 0;
		remain_run_time[i] = p[i].run_time;
		total_run_time += p[i].run_time;
	}

	/* 현재 시간이 총 실행 시간이 되기 전까지 반복 */
	while (current_time < total_run_time){ // 현재 시간이 총 실행시간보다 작은 경우 반복

		priority = INT_MAX; // 우선순위 초기화

		if (current_time < p[n - 1].arrival_time) { // 프로세스 도착 검사
			for (int i = 0; i < n; i++) {
				/* 완료되지 않았으며 도착시간이 현재시간보다 작거나 같으며 현재 우선순위보다 우선순위가 작을 경우 */
				if ((p[i].completed == false) && (p[i].arrival_time <= current_time) && (priority > p[i].priority)) {
					priority = p[i].priority; // 우선순위 갱신
					k = i;
				}
			}
		}else { // 모든 프로세스가 도착한 경우
			for (int i = 0; i < n; i++){
				/* 완료되지 않았으며 현재 우선순위보다 우선순위가 작을 경우 */
				if ((p[i].completed == false) && (priority > p[i].priority)){
					priority = p[i].priority;
					k = i;	
				}
			}
		}

		// k는 알고리즘을 거쳐 선택된 프로세스

		
		if (response[k] == 0){ // 선택된 프로세스가 처음 시작될 경우 
			response[k]++; // 초기 실행이 아님을 표시	
			p[k].response_time = current_time; // 실행중인 프로세스의 응답시간 저장
		}

		remain_run_time[k]--; // k 프로세스 남은시간 감소
		current_time++; // 현재 시간 증가
		

		if (remain_run_time[k] == 0){ // k 프로세스가 완료된 경우
			p[k].completed = true; // 완료 상태로 변경			
			p[k].waiting_time = current_time - p[k].run_time - p[k].arrival_time; // 대기 시간 계산			 
			p[k].return_time = current_time; // 반환 시간 계산
			
		}
	}

	/* 동적 할당한 배열의 메모리 할당 해제 */
	free(remain_run_time);
	free(response);
}


void PPS_Scheduling(Process* p, int pc) {
	int total_waiting_time = 0; // 총 프로세스 대기 시간
	int total_turnAround_time = 0; // 총 프로세스 소요 시간
	int total_response_time = 0; // 총 프로세스 응답 시간

	Process_init(p, pc);

	qsort_arrival_time(p, pc);

	PPS_Process_Time(p, pc);

	for (int i = 0; i < pc; i++) {
		p[i].turnAround_time = p[i].return_time - p[i].arrival_time; // 각 프로세스 소요시간 계산
		total_waiting_time += p[i].waiting_time; // 총 대기시간 저장
		total_turnAround_time += p[i].turnAround_time; // 총 소요시간 저장
		total_response_time += p[i].response_time; // 총 응답시간 저장
	}

	qsort_return_time(p, pc);

	PPS_print_gantt_chart(p, pc);

	view_table(p, pc);

	printf("\n");
	printf("Average Total Waiting time = %.2lf\n", (double)total_waiting_time / (double)pc); // 평균 대기 시간
	printf("Average Total turnAround time = %.2lf\n", (double)total_turnAround_time / (double)pc); // 평균 반환 시간
	printf("Average Total Response time = %.2lf\n", (double)total_response_time / (double)pc); // 평균 응답 시간
}

#endif __PPS__