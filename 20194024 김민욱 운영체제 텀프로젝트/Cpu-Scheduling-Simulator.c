/*
	Operating System Term Project 
	프로젝트 명 : CPU-Schuduling-Simulator
	이름 : 김민욱
	학번 : 20194024
	사용 언어 : C Language
	프로젝트 내용 : 7가지 CPU 스케줄링 시뮬레이터 개발
					(FCFS, SJF, 비선점 Priority, 선점 Priority, RR, SRT, HRN)
					간트 차트, 각 프로세스별 대기시간, 평균 대기 시간, 각 프로세스별 응답시간, 
					평균 응답시간, 각 프로세스별 반환 시간, 평균 반환 시간 출력
	[Repository]
*/
/*
	Turnaround Time (반환 시간)
	Turnaround Time = Completion Time - Arrival Time

	Response Time (응답 시간)
	Response Time = FirstRun Time - Arrival Time
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // true , false 
#pragma warning(disable:4996)
typedef struct Process { // 프로세스 구조체 선언
	char id[20]; // 프로세스 id - File
	int waiting_time; // 프로세스 대기시간
	int arrival_time; // 프로세스 도착시간 - File
	int run_time; // 프로세스 실행시간 - File
	int priority; // 프로세스 우선순위 - File
	int response_time; // 프로세스 응답시간
	int turn_around_time; // 프로세스 반환시간
	bool completed;
}Process;
void Process_init(Process *p, int n) // 프로세스 초기화 함수
{
	for (int i = 0; i < n; i++){ // 프로세스 갯수 만큼 반복
		p[i].waiting_time = 0; // 대기 시간 초기화
		p[i].response_time = 0; // 응답 시간 초기화
		p[i].turn_around_time = 0; // 반환 시간 초기화
		p[i].completed = false;
	}
}
void FCFS_Scheduling(Process *p,int pc); // FCFS Scheduling

int main() {
	printf("=======CPU Scheduling Simulator=======\n");

	int process_count = 0; // 프로세스 갯수를 저장할 변수

	int quantum = 0; // RR 스케쥴링에서 사용될 변수

	FILE* fp = fopen("Process.txt", "r"); // 파일 읽기 모드로 열기

	/* 파일 열기에 실패한 경우 */
	if (fp == NULL) { 
		fprintf(stderr, "File Open Fail\n");
		exit(1);
	}

	fscanf(fp, "%d", &process_count); // 파일에서 읽은 프로세스 갯수 저장

	Process* process = (Process*)malloc(sizeof(Process) * process_count); // 프로세스 개수 만큼 동적할당

	for (int i = 0; i < process_count; i++) { // 파일에서 프로세스id, 도착시간, 반환시간, 우선순위를 받아 구조체에 저장
		fscanf(fp, "%s %d %d %d", process[i].id, &process[i].arrival_time, &process[i].run_time, &process[i].priority);
		printf("%s %d %d %d\n", process[i].id, process[i].arrival_time, process[i].run_time, process[i].priority);
	}

	fscanf(fp, "%d", &quantum); // 파일에서 읽은 퀀텀 갯수 저장
	printf("%d", quantum);


	return 0;
}
/*
	함수명 : FCFS_Scheduling
	내용 : 준비 큐에 도착한 순서대로 CPU를 할당하는 비선점형방식
	입력 : 프로세스 포인터, 프로세스 갯수
	출력 : FCFS 스케쥴링으로 인한
	각 프로세스별 대기시간, 평균 대기 시간, 
	각 프로세스별 응답시간, 평균 응답시간,
	각 프로세스별 반환 시간, 평균 반환 시간
*/
void FCFS_Scheduling(Process* p,int pc) {
	int total_waiting_time = 0; // 총 프로세스 대기 시간
	int total_turnAround_time = 0; // 총 프로세스 반환 시간
	int total_response_time = 0; // 총 프로세스 응답 시간

	Process_init(p, pc);

	
}