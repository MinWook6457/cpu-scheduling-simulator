## Operating System Term Project

*Cpu Scheduling Simulator*

## [김민욱] https://github.com/MinWook6457


## 구성 요소
| 소스 파일 | 설명 |
|:---:|:---|
| **Cpu-Scheduling-Simulator.c** | 프로그램 실행 시작지점인 main 함수 |
| Process.h | 프로세스 정보가 입력된 헤더 |
| Function_to_Sorting.h | 실행시간, 도착시간, 반환시간, 우선순위를 기준으로 정렬한 함수가 저장된 헤더 |
| View_Table.h | 각 프로세스의 정보를 출력할 헤더 |
| **FCFS.h** | First Come First Service Scheduling |
| **SJF.h** | Shortest Job First Scheduling |
| **NPPS.h** | None Preemptive Priority Scheduling |
| **HRN.h** | Highest Response Ratio Next Scheduling |
| **PPS.h** | Preemptive Priority Scheduling |
| **RR.h** | Round Robin Scheduling |
| **SRT.h** | Shortest Remaining Time Scheduling |

## Ex
Quantum = 2

|PID|Arrival Time|Run Time|Priority|
|:-:|:-:|:-:|:-:|
|P1|0|10|3|
|P2|1|28|2|
|P3|2|6|4|
|P4|3|4|1|
|P5|4|14|2|


## Scheduling

## FCFS
[[CODE]](https://github.com/MinWook6457/cpu-scheduling-simulator/blob/master/20194024%20%EA%B9%80%EB%AF%BC%EC%9A%B1%20%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C%20%ED%85%80%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8/FCFS.h)


## Test Image
![FCFS](https://user-images.githubusercontent.com/103114126/237011748-4e807122-1b16-4560-a591-48848308c260.PNG)

## SJF
[[CODE]](https://github.com/MinWook6457/cpu-scheduling-simulator/blob/master/20194024%20%EA%B9%80%EB%AF%BC%EC%9A%B1%20%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C%20%ED%85%80%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8/SJF.h)


## Test Image
![SJF](https://github.com/MinWook6457/cpu-scheduling-simulator/assets/103114126/2dfd5916-c6fe-4e65-96df-ee146c68a4f5)

## NPPS
[[CODE]](https://github.com/MinWook6457/cpu-scheduling-simulator/blob/master/20194024%20%EA%B9%80%EB%AF%BC%EC%9A%B1%20%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C%20%ED%85%80%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8/NPPS.h)


## Test Image
![NPPS](https://github.com/MinWook6457/cpu-scheduling-simulator/assets/103114126/75f34af7-74b2-4093-a7ee-995f73a9d298)

## HRN
[[CODE]](https://github.com/MinWook6457/cpu-scheduling-simulator/blob/master/20194024%20%EA%B9%80%EB%AF%BC%EC%9A%B1%20%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C%20%ED%85%80%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8/HRN.h)


## Test Image
![HRN](https://github.com/MinWook6457/cpu-scheduling-simulator/assets/103114126/88efccac-89b2-4910-93aa-d29b7fbfc9fa)

## PPS
[[CODE]](https://github.com/MinWook6457/cpu-scheduling-simulator/blob/master/20194024%20%EA%B9%80%EB%AF%BC%EC%9A%B1%20%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C%20%ED%85%80%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8/PPS.h)


## Test Image
![PPS](https://github.com/MinWook6457/cpu-scheduling-simulator/assets/103114126/d5150c3a-8dbb-4807-9b5f-9f47649e84be)

## RR
[[CODE]](https://github.com/MinWook6457/cpu-scheduling-simulator/blob/master/20194024%20%EA%B9%80%EB%AF%BC%EC%9A%B1%20%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C%20%ED%85%80%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8/RR.h)


## Test Image
![RR](https://github.com/MinWook6457/cpu-scheduling-simulator/assets/103114126/26346f73-66d6-4f24-9364-19393ecb189d)

## SRT
[[CODE]](https://github.com/MinWook6457/cpu-scheduling-simulator/blob/master/20194024%20%EA%B9%80%EB%AF%BC%EC%9A%B1%20%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C%20%ED%85%80%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8/SRT.h)

## Test Image
![SRT](https://github.com/MinWook6457/cpu-scheduling-simulator/assets/103114126/2a403e64-283a-4731-8be5-834314be0ce1)





## Refer To
[github] https://github.com/tapaswenipathak/Visualization-of-CPU-Scheduling-Algorithms

[github] https://github.com/AugustineAykara/CPU-Scheduling-Algorithm-In-C 
