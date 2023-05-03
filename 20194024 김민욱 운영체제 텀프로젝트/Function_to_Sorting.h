#ifndef __Function_to_Sorting__
#define __Function_to_Sorting__

#include "Process.h"
#include <stdio.h>


int compare_return_time(const void* a, const void* b) // 오름차순 비교 함수 구현
{
	Process p1 = *(Process*)a;
	Process p2 = *(Process*)b;

	if (p1.return_time < p2.return_time)
		return -1;

	if (p1.return_time > p2.return_time)
		return 1;

	return 0;
}
// 반환시간 기준으로 (퀵)정렬할 함수
void qsort_return_time(Process* p, int n) {
	qsort(p, n, sizeof(Process), compare_return_time);
}

int compare_priority_time(const void* a, const void* b) // 오름차순 비교 함수 구현
{
	Process p1 = *(Process*)a;
	Process p2 = *(Process*)b;

	if (p1.priority < p2.priority)
		return -1;

	if (p1.priority > p2.priority)
		return 1;

	if (p1.priority == p2.priority) {
		if (p1.arrival_time < p2.arrival_time)
			return -1;
		if (p1.arrival_time > p2.arrival_time)
			return 1;
	}
	else
		return 0;
}
// 우선순위를 기준으로 (퀵)정렬할 함수
void qsort_priority_time(Process* p, int n) {
	qsort(p, n, sizeof(Process), compare_priority_time);
}

int compare_run_time(const void* a, const void* b) // 오름차순 비교 함수 구현
{
	Process p1 = *(Process*)a;
	Process p2 = *(Process*)b;

	if (p1.run_time < p2.run_time)
		return -1;

	if (p1.run_time > p2.run_time)
		return 1;

	return 0;
}
// 실행시간을 기준으로 (퀵)정렬할 함수
void qsort_run_time(Process* p, int n) {
	qsort(p, n, sizeof(Process), compare_run_time);
}

int compare_arrival_time(const void* a, const void* b) // 오름차순 비교 함수 구현
{
	Process p1 = *(Process*)a;
	Process p2 = *(Process*)b;

	if (p1.arrival_time < p2.arrival_time)
		return -1;

	if (p1.arrival_time > p2.arrival_time)
		return 1;

	return 0;
}
// 도착시간을 기준으로 (퀵)정렬할 함수
void qsort_arrival_time(Process* p, int n) {
	qsort(p, n, sizeof(Process), compare_arrival_time);
}

#endif