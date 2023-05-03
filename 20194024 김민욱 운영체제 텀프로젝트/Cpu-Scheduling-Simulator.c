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
	https://github.com/MinWook6457/cpu-scheduling-simulator
*/
/*
	Turnaround Time (반환 시간)
	Turnaround Time = Completion Time - Arrival Time (각 프로세스 완료 시간 - 각 프로세스 도착 시간)

	Response Time (응답 시간)
	Response Time = FirstRun Time - Arrival Time (첫 번째 실행 시간 - 첫 번째 도착 시간)
*/
#include <stdio.h>
#include <stdlib.h>
#include "FCFS.h"
#include "SJF.h"
#include "NPPS.h"
#include "HRN.h"
#include "PPS.h"
#pragma warning(disable:4996)


int main() {
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
		// printf("%s %d %d %d\n", process[i].id, process[i].arrival_time, process[i].run_time, process[i].priority);
	}

	fscanf(fp, "%d", &quantum); // 파일에서 읽은 퀀텀 갯수 저장
	// printf("%d", quantum);

	FCFS_Scheduling(process, process_count);

	SJF_Scheduling(process, process_count);

	NPPS_Scheduling(process, process_count);

	HRN_Scheduling(process, process_count);

	PPS_Scheduling(process, process_count);

	return 0;
}