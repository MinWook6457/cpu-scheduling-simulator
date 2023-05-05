#ifndef _process_
#define _process_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <Windows.h>

typedef struct _process { // ���μ��� ����ü ����
	char id[20]; // ���μ��� id - File
	int waiting_time; // ���μ��� ���ð�
	int arrival_time; // ���μ��� �����ð� - File
	int run_time; // ���μ��� ����ð� - File 
	int priority; // ���μ��� �켱���� - File
	int response_time; // ���μ��� ����ð�
	int return_time; // ���μ��� ��ȯ�ð�
	int turnAround_time; // ���μ��� �ҿ�ð�
	bool completed;
}Process;

typedef int Quantum; // �ð� �Ҵ緮 Quantum Ű���� ���

void Process_init(Process p[], int n) // ���μ��� �ʱ�ȭ �Լ�
{
	for (int i = 0; i < n; i++) { // ���μ��� ���� ��ŭ �ݺ�
		p[i].waiting_time = 0; // ��� �ð� �ʱ�ȭ
		p[i].response_time = 0; // ���� �ð� �ʱ�ȭ
		p[i].turnAround_time = 0; // ��ȯ �ð� �ʱ�ȭ
		p[i].completed = false;
	}
}

#endif