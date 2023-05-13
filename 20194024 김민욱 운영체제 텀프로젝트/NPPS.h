#ifndef __NPPS__
#define __NPPS__

/*
	헤더명 : NPPS.h(None Preemptive Priority Scheduling)
	내용 : 각각의 프로세스의 우선순위를 정하여 순위가 높은 작업 순으로 처리하는 방식
	입력 : 프로세스 포인터, 프로세스 갯수
	출력 : NPPS 스케쥴링으로 인한
	각 프로세스별 대기시간, 평균 대기 시간,
	각 프로세스별 응답시간, 평균 응답시간,
	각 프로세스별 반환 시간, 평균 반환 시간

*/

#include "Process.h"
#include <Windows.h>
#include "View_Table.h"
#include "Function_to_Sorting.h"
#pragma warning(disable:4996)

void NPPS_Process_Time(Process* p, int n, char* check_id) {
	int current_time = 0; // 현재까지 누적 시간을 저장할 변수

	/* 가장 먼저 들어온 프로세스 실행 및 시간 계산 */
	p[0].return_time = p[0].run_time;
	p[0].turnAround_time = p[0].return_time - p[0].arrival_time;
	p[0].response_time = 0;
	p[0].completed = true;

	current_time = p[0].run_time;

	qsort_priority_time(p, n);

	for (int i = 0; i < n; i++) {
		if (strcmp(check_id, p[i].id) == 0) {
			i++;
		}

		p[i].response_time = current_time - p[i].arrival_time;
		p[i].return_time = current_time + p[i].run_time;
		p[i].turnAround_time = p[i].return_time - p[i].arrival_time;
		p[i].waiting_time = current_time - p[i].arrival_time;
		p[i].completed = true;

		current_time += p[i].run_time;
	}
}

void NPPS_print_gantt_chart(Process* p, int n, char* check_id)
{
	printf("\tNon Preemptive Priority Scheduling\n");

	printf("┏");
	/* 상단 출력 */
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < p[i].run_time; j++)
			printf("━━");

		if (i == n - 1)
			printf("┓");
		else
			printf("┳");
	}

	printf("\n┃");
	/* 프로세스 이름 출력 */
	for (int i = 0; i < n; i++)
	{
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
	for (int i = 0; i < n; i++)
	{
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
	// qsort_return_time(p, n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < p[i].run_time; j++)
			printf("  ");

		if (p[i].return_time > 9)
			printf("\b");
		printf("%d", p[i].return_time);

	}

	printf("\n");
}



void NPPS_Scheduling(Process* p, int pc) {
	int total_waiting_time = 0; // 총 프로세스 대기 시간
	int total_turnAround_time = 0; // 총 프로세스 소요 시간
	int total_response_time = 0; // 총 프로세스 응답 시간

	Process_init(p, pc);

	qsort_arrival_time(p, pc);

	char check_id[10];
	strcpy(check_id, p[0].id); // 가장 처음으로 들어온 PID 저장

	
	NPPS_Process_Time(p, pc, check_id);

	for (int i = 0; i < pc; i++) {
		total_response_time += p[i].response_time;
		total_waiting_time += p[i].waiting_time;
		total_turnAround_time += p[i].turnAround_time;
	}
	qsort_return_time(p, pc);

	NPPS_print_gantt_chart(p, pc, check_id);

	view_table(p, pc);

	printf("\n");
	printf("Average Total Waiting time = %.2lf\n", (double)total_waiting_time / (double)pc); // 평균 대기 시간
	printf("Average Total turnAround time = %.2lf\n", (double)total_turnAround_time / (double)pc); // 평균 반환 시간
	printf("Average Total Response time = %.2lf\n", (double)total_response_time / (double)pc); // 평균 응답 시간
}

#endif __NPPS__