# Operating System Term Project


# Cpu Scheduling Simulator


## [김민욱] https://github.com/MinWook6457

## Ex
Quantum = 2

|PID|Arrival Time|Run Time|Priority|
|:-:|:-:|:-:|:-:|
|P1|0|10|3|
|P2|1|28|2|
|P3|2|6|4|
|P4|3|4|1|
|P5|4|14|2|


## Code

## FCFS
```C
	/* 맨 처음 들어온 프로세스 실행 */
	p[0].return_time = p[0].run_time; // 파일에서 받은 run_time을 return_time에 대입
	p[0].turnAround_time = p[0].return_time - p[0].arrival_time; // 반환시간 = 실행시간 - 대기시간
	p[0].response_time = 0; // 응답시간 초기화
	p[0].waiting_time = 0; // 대기시간 초기화

	/* 실행된 프로세스 만큼 사용률 증가 */
	total_waiting_time += p[0].waiting_time; // 총 대기시간 증가
	total_turnAround_time += p[0].turnAround_time; // 총 소요시간 증가
	total_response_time += p[0].response_time; // 총 응답시간 증가
	total_return_time += p[0].run_time; // 총 실행시간 증가

	// 선입 선출 구조로 들어오는 순서대로 프로세스 계산
	for (int i = 1; i < pc; i++)
	{
		/* 각 프로세스 계산 */
		p[i].waiting_time = total_return_time - p[i].arrival_time; // 각 프로세스 대기시간 = 총 반환시간 - 도착시간 
		p[i].return_time = total_return_time + p[i].run_time; // 각 프로세스 반환시간 = 총 반환시간 + 실행시간
		p[i].turnAround_time = p[i].return_time - p[i].arrival_time; // 각 프로세스 소요시간 = 각 프로세스 반환시간 - 도착시간
		p[i].response_time += p[i].waiting_time; // 반응시간 += 대기시간

		/* 실행된 프로세스 만큼 사용률 증가 */
		total_return_time += p[i].run_time; // 총 반환시간 증가
		total_waiting_time += p[i].waiting_time; // 총 대기시간 증가
		total_turnAround_time += p[i].turnAround_time; // 총 소요시간 증가
		total_response_time += p[i].response_time; // 총 응답시간 증가
	}
```


## Help
[github] https://github.com/alstn2468/cpu-scheduling-simulator

[github] https://github.com/tapaswenipathak/Visualization-of-CPU-Scheduling-Algorithms

[github] https://github.com/AugustineAykara/CPU-Scheduling-Algorithm-In-C 
