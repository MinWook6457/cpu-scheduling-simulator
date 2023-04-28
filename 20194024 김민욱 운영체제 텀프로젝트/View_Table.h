#ifndef __View_Table__
#define __View_Table__


#include "Process.h"
#include <stdio.h> // 표준 입출력 헤더 정의
void view_table(Process* p, int pc) {
	printf("┏");
	for (int i = 0; i < pc; i++)
	{
		for (int j = 0; j < p[i].run_time; j++)
			printf("━━");

		printf("┓");
	}

	printf("\n┃");
	printf("    Waiting Time    ┃");
	for (int i = 0; i < pc; i++){
		for (int j = 0; j < p[i].run_time - 2; j++) {
			printf(" ");
		}
		printf("%s %d┃  ", p[i].id, p[i].waiting_time);

	}


}


#endif __View_Table__



