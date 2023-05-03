#ifndef __View_Table__
#define __View_Table__


#include "Process.h"
#include <stdio.h> 
void view_table(Process p[], int n) {
	printf("┏━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━┓\n");
	printf("┃ PID ┃ Run Time ┃ Arrival Time ┃ Priority ┃ Return Time ┃ Reseponse Time ┃ Waiting Time ┃ TurnAround Time ┃");
	printf("\n┣━━━━━╋━━━━━━━━━━╋━━━━━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━┫");
	printf("\n");
	for (int i = 0; i < n - 1; i++) {
		printf("┃ %s  ┃    %3d   ┃     %3d      ┃    %3d   ┃     %3d     ┃      %3d       ┃     %3d      ┃        %3d      ┃\n",
				p[i].id, p[i].run_time, p[i].arrival_time, p[i].priority, p[i].return_time, p[i].response_time, p[i].waiting_time, p[i].turnAround_time);
		printf("┃━━━━━╋━━━━━━━━━━╋━━━━━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━┫\n");
	}
	printf("┃ %s  ┃    %3d   ┃     %3d      ┃    %3d   ┃     %3d     ┃      %3d       ┃     %3d      ┃        %3d      ┃\n",
		p[n - 1].id, p[n - 1].run_time, p[n - 1].arrival_time, p[n - 1].priority, p[n - 1].return_time, p[n - 1].response_time, p[n - 1].waiting_time, p[n - 1].turnAround_time);
	printf("┗━━━━━┻━━━━━━━━━━┻━━━━━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━┛");
}


#endif __View_Table__