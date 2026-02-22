#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>

struct Process {
    int id;
    int arrival;
    int burst;
    int nice;

    int start = -1;
    int completion = 0;
};

struct Block {
    int time;
    int pid;
    int duration;
    bool finished;
};

void printHeader(int caseNum, std::string algo);
void printGantt(const std::vector<Block>& gantt);
void printStats(std::vector<Process>& processes, int totalTime, int cpuBurst);

void runFCFS(std::vector<Process> processes, int caseNum, std::string algo);
void runSJF(std::vector<Process> processes, int caseNum, std::string algo);
void runSRTF(std::vector<Process> processes, int caseNum, std::string algo);
void runPriority(std::vector<Process> processes, int caseNum, std::string algo);
void runRR(std::vector<Process> processes, int caseNum, std::string algo, int quantum);

#endif