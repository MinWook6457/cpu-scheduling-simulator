#ifndef __Function_to_Sorting__
#define __Function_to_Sorting__

#include "Process.h"
#include <stdio.h>


int compare_return_time(const void* a, const void* b) // �������� �� �Լ� ����
{
	Process p1 = *(Process*)a;
	Process p2 = *(Process*)b;

	if (p1.return_time < p2.return_time)
		return -1;

	if (p1.return_time > p2.return_time)
		return 1;

	return 0;
}
// ��ȯ�ð� �������� (��)������ �Լ�
void qsort_return_time(Process* p, int n) {
	qsort(p, n, sizeof(Process), compare_return_time);
}

int compare_priority_time(const void* a, const void* b) // �������� �� �Լ� ����
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
// �켱������ �������� (��)������ �Լ�
void qsort_priority_time(Process* p, int n) {
	qsort(p, n, sizeof(Process), compare_priority_time);
}

int compare_run_time(const void* a, const void* b) // �������� �� �Լ� ����
{
	Process p1 = *(Process*)a;
	Process p2 = *(Process*)b;

	if (p1.run_time < p2.run_time)
		return -1;

	if (p1.run_time > p2.run_time)
		return 1;

	return 0;
}
// ����ð��� �������� (��)������ �Լ�
void qsort_run_time(Process* p, int n) {
	qsort(p, n, sizeof(Process), compare_run_time);
}

int compare_arrival_time(const void* a, const void* b) // �������� �� �Լ� ����
{
	Process p1 = *(Process*)a;
	Process p2 = *(Process*)b;

	if (p1.arrival_time < p2.arrival_time)
		return -1;

	if (p1.arrival_time > p2.arrival_time)
		return 1;

	return 0;
}
// �����ð��� �������� (��)������ �Լ�
void qsort_arrival_time(Process* p, int n) {
	qsort(p, n, sizeof(Process), compare_arrival_time);
}

#endif