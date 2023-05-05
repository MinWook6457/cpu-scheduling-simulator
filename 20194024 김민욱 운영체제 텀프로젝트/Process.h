#ifndef _process_
#define _process_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <Windows.h>

typedef struct _process { // 프로세스 구조체 선언
	char id[20]; // 프로세스 id - File
	int waiting_time; // 프로세스 대기시간
	int arrival_time; // 프로세스 도착시간 - File
	int run_time; // 프로세스 실행시간 - File 
	int priority; // 프로세스 우선순위 - File
	int response_time; // 프로세스 응답시간
	int return_time; // 프로세스 반환시간
	int turnAround_time; // 프로세스 소요시간
	bool completed;
}Process;

typedef int Quantum; // 시간 할당량 Quantum 키워드 사용

void Process_init(Process p[], int n) // 프로세스 초기화 함수
{
	for (int i = 0; i < n; i++) { // 프로세스 갯수 만큼 반복
		p[i].waiting_time = 0; // 대기 시간 초기화
		p[i].response_time = 0; // 응답 시간 초기화
		p[i].turnAround_time = 0; // 반환 시간 초기화
		p[i].completed = false;
	}
}

#endif