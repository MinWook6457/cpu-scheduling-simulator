#ifndef __HRN__
#define __HRN__
/*
	헤더명 : HRN.h (Highest Response Ratio Next Scheduling)
	내용 : 각 작업의 우선순위로 스케쥴링	
		   우선순위 = (대기시간 + CPU 사용시간) / (CPU 사용시간)
		   SJF에서 발생할 수 있는 아사 현상 해결
	입력 : 프로세스 포인터, 프로세스 갯수
	출력 : HRN 스케쥴링으로 인한
	각 프로세스별 대기시간, 평균 대기 시간,
	각 프로세스별 응답시간, 평균 응답시간,
	각 프로세스별 반환 시간, 평균 반환 시간
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

	int check_num = 0; // 처음 실행된 PID를 추출하기 위한 변수

	for (int i = 0; i < n; i++)
	{
		if (strcmp(check_id, p[i].id) == 0) { // 처음 실행된 프로세스 id를 받아 현재 구조체에 있는 id 와 같은 인덱스 추출
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
		tmp[i] = p[i]; // 구조체 복사
	}

	Process Temp = tmp[check_num]; // Temp에 추출된 인덱스가 해당하는 프로세스 저장

	for (int i = 0; i < check_num; i++) { // 가장 먼저 실행된 프로세스를 맨 앞으로 보내기 위해서 구조체 배열을 뒤로 민다.
		p[i + 1] = tmp[i];
	}

	p[0] = Temp; // 저장해두었던 프로세스를 다시 구조체 첫 번째 인덱스로 저장


	printf("┏");
	/* 상단 바 출력 */
	for (int i = 0; i < n; i++){
		for (int j = 0; j < p[i].run_time; j++)
			printf("━━");

		if (i == n - 1)
			printf("┓");
		else
			printf("┳");

	}

	printf("\n┃");

	/* 프로세스 이름 출력 */
	for (int i = 0; i < n; i++){
		for (int j = 0; j < p[i].run_time - 1; j++)
			printf(" ");

		printf("%s", p[i].id);

		for (int j = 0; j < p[i].run_time - 1; j++)
			printf(" ");

		printf("┃");
	}

	printf("\n");
	printf("┗");
	/* 하단 바 출력 */
	for (int i = 0; i < n; i++){
		for (int j = 0; j < p[i].run_time; j++)
			printf("━━");

		if (i == n - 1)
			printf("┛");
		else
			printf("┻");
	}

	printf("\n");

	/* 프로세스 시간 출력 */
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
	int priority_index; // 우선순위를 가지는 인덱스
	int total_waiting_time = 0; // 총 프로세스 대기 시간
	int total_turnAround_time = 0; // 총 프로세스 소요 시간
	int total_response_time = 0; // 총 프로세스 응답 시간
	int total_run_time = 0; // 총 프로세스 실행 시간

	double hrr, temp; // 우선순위 저장 변수, 소숫점 가능

	Process_init(p, n);

	for (int i = 0; i < n; i++)	{
		total_run_time += p[i].run_time; // 총 실행 시간을 계산
	}

	qsort_arrival_time(p, n);
	
	char check_id[10];
	strcpy(check_id, p[0].id); // 가장 처음으로 들어온 PID 저장

	current_time = p[0].arrival_time; // 현재 시간은 첫 프로세스가 도착한 시간

	while(current_time < total_run_time){ // 증가된 현재 시간이 총 프로세스 시간보다 크다면 모든 프로세스를 돌았음.
		hrr = -9999.0;
		for (int i = 0; i < n; i++){
			if ((p[i].arrival_time <= current_time) && (p[i].completed == false)) {// 가장 처음 들어온 프로세스 부터 실행
				temp = (p[i].run_time + (current_time - p[i].arrival_time)) / p[i].run_time;
				// (실행시간 + 대기시간) / 실행시간 으로 우선순위 계산
				if (hrr < temp){ // 우선순위 갱신
					hrr = temp;
					priority_index = i; // 해당 인덱스로 갱신
				}
			}
		}

		current_time += p[priority_index].run_time; // 서비스 시간 증가

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
	/* 평균 대기시간, 턴어라운드 타임, 응답 시간 출력 */
	printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)n);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnAround_time / (double)n);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)n);
}

#endif __HRN__
