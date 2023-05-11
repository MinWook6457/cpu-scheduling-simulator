#ifndef	__RR__
#define __RR__
/*
	헤더명 : RR.h(Round Robin Scheduling)
	내용 : 한 프로세스가 할당받은 시간(타임 슬라이스Time Slice/Time Quantum) 
	       동안작업을 하다가 작업을 완료하지 못하면 준비 큐의 맨 뒤로 가서 자기 차례를 기다리는 방식
	입력 : 프로세스 포인터, 프로세스 갯수 , 타임 슬라이스(퀀텀)
	출력 : RR 스케쥴링으로 인한
	각 프로세스별 대기시간, 평균 대기 시간,
	각 프로세스별 응답시간, 평균 응답시간,
	각 프로세스별 반환 시간, 평균 반환 시간
*/

#include "Process.h"
#include <Windows.h>
#include "View_Table.h"
#include "Function_to_Sorting.h"

void RR_Process_Waiting_Time(Process* p, int n, Quantum quantum) { // 대기 시간 계산 함수
	int current_time = 0; // 현재시간 초기화
	int total_run_time = 0; // 총 실행시간 초기화
	int* remain_run_time = NULL;
	remain_run_time = (int*)malloc(sizeof(int) * n); // 남은 시간 저장 배열 할당

	if (remain_run_time == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}
	
	bool* check_response_time = NULL;
	check_response_time = (bool*)malloc(sizeof(bool) * n); // 응답 시간 처리 확인 배열 할당

	if (check_response_time == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}

	
	for (int i = 0; i < n;i++) {
		remain_run_time[i] = p[i].run_time; // 각 프로세스별 남은시간 저장
		check_response_time[i] = false; // 프로세스 응답 초기화
		total_run_time += p[i].run_time; // 총 실행시간 계산
	}
	while (true) { // 모든 프로세스가 완료될 때 까지 반복
		bool check = true;
		for (int i = 0; i < n; i++) {
			if (remain_run_time[i] > 0) { // 실행 시간이 남아 있는 경우
				check = false;

				if (check_response_time[i] == false) { // 응답 시간 처리 안한 경우
					p[i].response_time = current_time - p[i].arrival_time; // 응답시간 계산
					check_response_time[i] = true;
				}

				if (remain_run_time[i] > quantum) { // 남은 시간이 타임 슬라이스 보다 클 경우
					current_time += quantum; // 현재 시간 증가
					remain_run_time[i] -= quantum; // 현재 실행중인 프로세스 남은 시간 감소
				}
				else { // 남은 시간이 타임 슬라이스 보다 작은 경우
					current_time += remain_run_time[i]; // 현재시간 증가
					p[i].waiting_time = current_time - p[i].run_time; // 대기시간 계산
					remain_run_time[i] = 0; // 작업 끝난 프로세스 남은 시간 0으로 초기화
				}
			}
		}
		
		if (check == true) // 남아 있는 프로세스가 없는 경우
			break;
	}
	/* 동적할당한 메모리 해제 */
	free(remain_run_time);
	free(check_response_time);
}

void RR_Process_TurnAround_Time(Process* p, int n) { // 소요 시간 계산 함수
	for (int i = 0; i < n; i++) {
		p[i].turnAround_time = p[i].run_time + p[i].waiting_time - p[i].arrival_time;
	}
}

	/* 대기시간 계산 함수 알고리즘과 동일 */
void RR_print_gantt_chart(Process* p, int n, Quantum quantum) 
{
	textcolor(8);

	int current_time = 0, total_run_time = 0; // 현재 시간과 총 실행 시간을 저장할 변수

	int* remain_run_time = NULL;
	remain_run_time = (int*)malloc(sizeof(int) * n);

	if (remain_run_time == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}

	for (int i = 0; i < n; i++){
		remain_run_time[i] = p[i].run_time;
		total_run_time += p[i].run_time;
	}

	printf("┏");

	/* 상단 바 출력 */
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
						printf("━━");
				}
				
				if (remain_run_time[i] > quantum){
					current_time += quantum;
					remain_run_time[i] -= quantum;
					printf("━━");
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

	printf("┓\n");

	for (int i = 0; i < n; i++){
		remain_run_time[i] = p[i].run_time;
	}

	/* 프로세스 아이디 출력 */
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
					printf("┃");
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

	printf("┃\n");

	for (int i = 0; i < n; i++){
		remain_run_time[i] = p[i].run_time;
	}


	printf("┗");

	/* 하단 바 출력 */
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
						printf("━━");
					}
				}

				if (remain_run_time[i] > quantum){
					current_time += quantum;
					remain_run_time[i] -= quantum;
					printf("━━");
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

	printf("┛\n");
	for (int i = 0; i < n; i++)
		remain_run_time[i] = p[i].run_time;

	current_time = 0;

	/* 프로세스 시간 출력 */
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
	// 동적 할당한 배열의 메모리 할당 해제
}

void RR_Scheduling(Process* p, int pc, Quantum quantum) {
	
	int total_waiting_time = 0; // 총 프로세스 대기 시간
	int total_turnAround_time = 0; // 총 프로세스 소요 시간
	int total_response_time = 0; // 총 프로세스 응답 시간

	Process_init(p, pc);

	qsort_arrival_time(p, pc);

	RR_Process_Waiting_Time(p, pc, quantum);

	RR_Process_TurnAround_Time(p, pc);

	for (int i = 0; i < pc; i++){
		p[i].waiting_time = p[i].turnAround_time - p[i].run_time; // 대기 시간 계산 후 저장
		p[i].return_time = p[i].arrival_time + p[i].run_time + p[i].waiting_time; // 반환 시간 계산 후 저장

		total_waiting_time += p[i].waiting_time; // 총 대기 시간 증가
		total_turnAround_time += p[i].turnAround_time; // 총 소요 시간  증가
		total_response_time += p[i].response_time; // 총 응답 시간 증가
	}
	
	printf("Round Robin Scheduling\n");

	RR_print_gantt_chart(p, pc, quantum);

	view_table(p, pc);
	printf("\n");

	printf("Average Total Waiting time = %.2lf\n", (double)total_waiting_time / (double)pc); // 평균 대기 시간
	printf("Average Total turnAround time = %.2lf\n", (double)total_turnAround_time / (double)pc); // 평균 반환 시간
	printf("Average Total Response time = %.2lf\n", (double)total_response_time / (double)pc); // 평균 응답 시간

}
#endif