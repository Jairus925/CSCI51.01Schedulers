#include <algorithm>
#include <iostream>
#include "scheduler.h"
using namespace std;

int selectNextProcessP(const vector<Process>& processes, const vector<bool>& done, int time) {
    int idx = -1;
    for (int j = 0; j < processes.size(); j++) 
    {
        if (!done[j] && processes[j].arrival <= time) 
        {
            if (idx == -1 ||
                processes[j].nice < processes[idx].nice ||
                (processes[j].nice == processes[idx].nice && processes[j].arrival < processes[idx].arrival) ||
                (processes[j].nice == processes[idx].nice && processes[j].arrival == processes[idx].arrival && processes[j].id < processes[idx].id))
                    idx = j;
        }
    }
    return idx;
}

void runPriority(vector<Process> processes, int caseNum, string algo) 
{
    int n = processes.size();
    vector<Block> gantt;
    vector<bool> done(n, false);
    int time = 0;
    int cpuBurst = 0;
    int completed = 0;

    for (auto &p : processes) 
    {
        p.remaining = p.burst;
        p.start = -1;
    }

    int currentIdx = -1;

    while (completed < n) 
    {
        int idx = selectNextProcessP(processes, done, time);

        if (idx == -1) 
        {
            time++;
            continue;
        }

        if (currentIdx != idx) 
        {
            Block b;
            b.time = time;
            b.pid = processes[idx].id;
            b.duration = 0;
            b.finished = false;
            gantt.push_back(b);
            currentIdx = idx;
        }

        if (processes[idx].start == -1)
            processes[idx].start = time;

        gantt.back().duration++;
        processes[idx].remaining--;
        time++;
        cpuBurst++;

        if (processes[idx].remaining == 0) 
        {
            done[idx] = true;
            completed++;
            processes[idx].completion = time;
            gantt.back().finished = true;
        }
    }

    printHeader(caseNum, algo);
    printGantt(gantt);
    printStats(processes, time, cpuBurst);
}