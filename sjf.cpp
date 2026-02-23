#include <algorithm>
#include <iostream>
#include "scheduler.h"
using namespace std;

int selectNextProcessSJF(const vector<Process>& processes, const vector<bool>& done, int time) 
{
    int idx = -1;
    for (int j = 0; j < processes.size(); j++) 
        if (!done[j] && processes[j].arrival <= time) 
            if (idx == -1 || processes[j].burst < processes[idx].burst) 
                idx = j;

    return idx;
}

void runSJF(vector<Process> processes, int caseNum, string algo) 
{
    int n = processes.size();
    vector<Block> gantt;
    vector<bool> done(n, false);
    int time = 0;
    int cpuBurst = 0;

    for (int i = 0; i < n; i++) 
    {
        int idx = selectNextProcessSJF(processes, done, time);

        if (idx == -1) {
            time++;
            i--;
            continue;
        }

        done[idx] = true;

        processes[idx].start = time;

        Block b;
        b.time = time;
        b.pid = processes[idx].id;
        b.duration = processes[idx].burst;
        b.finished = true;

        gantt.push_back(b);

        time += processes[idx].burst;
        cpuBurst += processes[idx].burst;

        processes[idx].completion = time;
    }

    printHeader(caseNum, algo);
    printGantt(gantt);
    printStats(processes, time, cpuBurst);
}