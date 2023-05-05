#ifndef _FCFS_
#define _FCFS_

#include "Process.h"
#include "Function_to_Sorting.h"
#include "View_Table.h"
#include <Windows.h>
#include <stdbool.h>

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}
/*
	함수명 : FCFS_Scheduling(First Come First Served)
	내용 : 준비 큐에 도착한 순서대로 CPU를 할당하는 비선점형방식
	입력 : 프로세스 포인터, 프로세스 갯수
	출력 : FCFS 스케쥴링으로 인한
	각 프로세스별 대기시간, 평균 대기 시간,
	각 프로세스별 응답시간, 평균 응답시간,
	각 프로세스별 반환 시간, 평균 반환 시간
*/
void FCFS_print_gantt_chart(Process* p, int n)
{	// 반복문에서 사용할 변수 선언

	textcolor(2);
	printf("\tFirst Come First Served Scheduling\n");
	printf("┏");
	/* 상단 바 출력 */
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

void FCFS_Scheduling(Process* p, int pc) {
	int total_waiting_time = 0; // 총 프로세스 대기 시간
	int total_turnAround_time = 0; // 총 프로세스 소요 시간
	int total_response_time = 0; // 총 프로세스 응답 시간
	int total_return_time = 0; // 총 프로세스 반환 시간

	Process_init(p, pc);

	qsort_arrival_time(p, pc);
	/*
	for (int i = 0; i < pc; i++) {
		printf("%s : %d\n", p[i].id,p[i].arrival_time);
	}
	*/
	/* 맨 처음 들어온 프로세스 실행 */
	p[0].return_time = p[0].run_time; // 파일에서 받은 run_time을 return_time에 대입
	p[0].turnAround_time = p[0].return_time - p[0].arrival_time; // 반환시간 = 실행시간 - 대기시간
	p[0].response_time = 0;
	p[0].waiting_time = 0;

	/* 실행된 프로세스 만큼 사용률 증가 */
	total_waiting_time += p[0].waiting_time;
	total_turnAround_time += p[0].turnAround_time;
	total_response_time += p[0].response_time;
	total_return_time += p[0].run_time;

	// 선입 선출 구조로 들어오는 순서대로 프로세스 계산
	for (int i = 1; i < pc; i++)
	{
		/* 각 프로세스 계산 */
		p[i].waiting_time = total_return_time - p[i].arrival_time; // 각 프로세스 대기시간 = 총 반환시간 - 도착시간 
		p[i].return_time = total_return_time + p[i].run_time; // 각 프로세스 반환시간 = 총 반환시간 + 실행시간
		p[i].turnAround_time = p[i].return_time - p[i].arrival_time; // 각 프로세스 소요시간 = 각 프로세스 반환시간 - 도착시간
		p[i].response_time += p[i].waiting_time; // 반응시간 += 대기시간

		/* 실행된 프로세스 만큼 사용률 증가 */
		total_return_time += p[i].run_time;
		total_waiting_time += p[i].waiting_time;
		total_turnAround_time += p[i].turnAround_time;
		total_response_time += p[i].response_time;
	}
	FCFS_print_gantt_chart(p, pc);
	view_table(p, pc);
	printf("\n");
	printf("Average Total Waiting time = %.2lf\n", (double)total_waiting_time / (double)pc); // 평균 대기 시간
	printf("Average Total turnAround time = %.2lf\n", (double)total_turnAround_time / (double)pc); // 평균 반환 시간
	printf("Average Total Response time = %.2lf\n", (double)total_response_time / (double)pc); // 평균 응답 시간


}

#endif