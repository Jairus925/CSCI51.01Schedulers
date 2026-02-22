#include <algorithm>
#include <iostream>
#include "scheduler.h"

using namespace std;

bool arrivalOrder(const Process &a, const Process &b)
{
    if (a.arrival != b.arrival)
        return a.arrival < b.arrival;

    return a.id < b.id;
}

void runFCFS(vector<Process> processes, int caseNum, string algo)
{
    sort(processes.begin(), processes.end(), arrivalOrder);

    vector<Block> gantt;

    int time = 0;
    int cpuBurst = 0;

    for (auto &p : processes)
    {
        if (time < p.arrival)
            time = p.arrival;

        p.start = time;

        Block b;
        b.time = time;
        b.pid = p.id;
        b.duration = p.burst;
        b.finished = true;

        gantt.push_back(b);

        time += p.burst;
        cpuBurst += p.burst;

        p.completion = time;
    }

    printHeader(caseNum, algo);
    printGantt(gantt);
    printStats(processes, time, cpuBurst);
}