#ifndef __SJF__
#define __SJF__

/*
	헤더명 : SJF.h(Shortest Job First Scheduling)
	내용 : 준비 큐에 있는 프로세스 중에서 실행 시간이 가장 짧은 작업부터 CPU를 할당하는 비선점형 방식
	입력 : 프로세스 포인터, 프로세스 갯수
	출력 : SJF 스케쥴링으로 인한
	각 프로세스별 대기시간, 평균 대기 시간,
	각 프로세스별 응답시간, 평균 응답시간,
	각 프로세스별 반환 시간, 평균 반환 시간
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
	int check_num = 0; // 처음 실행된 PID를 추출하기 위한 변수

	for (int i = 0; i < n; i++){
		if (strcmp(check_id, p[i].id) == 0) { // 처음 실행된 프로세스 id를 받아 현재 구조체에 있는 id 와 같은 인덱스 추출
			break;
		}
		check_num++;
	}
	// Process* tmp = (Process*)malloc(sizeof(Process) * (check_num)); // 구조체 교환을 위한 동적할당)
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
		tmp[i] = p[i]; // 구조체 복사
	}

	Process Temp = tmp[check_num]; // Temp에 추출된 인덱스가 해당하는 프로세스 저장
	for (int i = 0; i < check_num; i++) { // 가장 먼저 실행된 프로세스를 맨 앞으로 보내기 위해서 구조체 배열을 뒤로 민다.
		p[i + 1] = tmp[i];
	}

	p[0] = Temp; // 저장해두었던 프로세스를 다시 구조체 첫 번째 인덱스로 저장

	// free(tmp);


	printf("┏");
	/* 상단 출력 */
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

void SJF_Process_Time(Process* p, int n) { // 프로세스 별 시간 계산 함수
	int current_time = 0; // 현재까지 누적 시간을 저장할 변수

	int min_index = 0; // 최소 시간을 가지는 인덱스 변수

	/* 도착시간이 가장 빠른 프로세스 먼저 실행 */
	p[0].return_time = p[0].run_time; // 반환시간 저장
	p[0].turnAround_time = p[0].run_time - p[0].arrival_time; // 소요시간 = 실행시간 - 도착시간
	p[0].waiting_time = 0; // 대기시간 0
	p[0].completed = true; // 완료 표시

	current_time = p[0].run_time; // 현재 시간 증가

	/* p[0]는 진행하였으므로 인덱스 1부터 시작 */
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			if (p[j].completed == true) // 이미 완료된 프로세스
				continue;
			else {
				min_index = j; // 아직 실행하지 않은 프로세스
				break;
			}
		}

		for (int k = 1; k < n; k++) {
			/* 완료되지 않은 프로세스이고 도착시간이 현재 누적된 시간보다 적어야 한다.(프로세스 연기 되는 현상 해결) 또한 해당 인덱스의 최소 인덱스 다시 검색 */
			if (p[k].completed == false && p[k].arrival_time < current_time && p[k].run_time < p[min_index].run_time) { // 최소 작업 시간 조건에 맞는 프로세스 찾기
				min_index = k;
			}
		}

		p[min_index].waiting_time = current_time - p[min_index].arrival_time; // 대기 시간 계산(=응답시간) : FCFS 형식을 이루고 있으므로 대기시간 = 응답시간
		p[min_index].completed = true; // 완료 상태 갱신

		current_time += p[min_index].run_time; // 누적 시간 갱신
		p[min_index].return_time = current_time; // 반환 시간 갱신
		p[min_index].turnAround_time = p[min_index].return_time - p[min_index].arrival_time; // 소요 시간 갱신
	}
}

void SJF_Scheduling(Process* p, int pc) {
	int total_waiting_time = 0; // 총 프로세스 대기 시간
	int total_turnAround_time = 0; // 총 프로세스 소요 시간
	int total_response_time = 0; // 총 프로세스 응답 시간

	Process_init(p, pc);

	qsort_arrival_time(p, pc); // 도착시간 기준으로 정렬

	SJF_Process_Time(p, pc); // 도착시간 기준으로 프로세스 계산

	char check_id[10];
	strcpy(check_id, p[0].id); // 가장 처음으로 들어온 PID 저장

	for (int i = 0; i < pc; i++){
		p[i].return_time = p[i].turnAround_time + p[i].arrival_time;
		p[i].response_time = p[i].waiting_time;

		total_waiting_time += p[i].waiting_time;
		total_turnAround_time += p[i].turnAround_time;
		total_response_time += p[i].response_time;
	}

	qsort_run_time(p, pc); // 실행 시간 기준 정렬

	SJF_print_gantt_chart(p, pc, check_id); // 실행 시간 기준으로 출력

	view_table(p, pc);

	printf("\n");
	printf("Average Total Waiting time = %.2lf\n", (double)total_waiting_time / (double)pc); // 평균 대기 시간
	printf("Average Total turnAround time = %.2lf\n", (double)total_turnAround_time / (double)pc); // 평균 반환 시간
	printf("Average Total Response time = %.2lf\n", (double)total_response_time / (double)pc); // 평균 응답 시간

}

#endif __SJF__