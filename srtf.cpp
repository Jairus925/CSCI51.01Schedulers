#include <iostream>
#include <vector>
#include <climits>
#include "scheduler.h"

using namespace std;

int selectSRTF(const vector<Process>& processes,
               const vector<int>& remaining,
               int time)
{
    int idx = -1;

    for (int i = 0; i < processes.size(); i++) {
        if (processes[i].arrival <= time && remaining[i] > 0) {
            if (idx == -1 ||
                remaining[i] < remaining[idx] ||
                (remaining[i] == remaining[idx] &&
                 (processes[i].arrival < processes[idx].arrival ||
                  (processes[i].arrival == processes[idx].arrival &&
                   processes[i].id < processes[idx].id))))
            {
                idx = i;
            }
        }
    }

    return idx;
}

void runSRTF(vector<Process> processes, int caseNum, string algo)
{
    int n = processes.size();
    vector<int> remaining(n);
    vector<Block> gantt;

    int time = 0;
    int completed = 0;
    int cpuBurst = 0;

    for (int i = 0; i < n; i++)
        remaining[i] = processes[i].burst;

    int current = -1;
    int blockStart = 0;

    while (completed < n)
    {
        int idx = selectSRTF(processes, remaining, time);

        if (idx == -1) {
            time++;
            continue;
        }

        if (current != idx) {
            if (current != -1) {
                Block b;
                b.time = blockStart;
                b.pid = processes[current].id;
                b.duration = time - blockStart;
                b.finished = false;
                gantt.push_back(b);
            }
            blockStart = time;
            current = idx;
        }

        if (processes[idx].start == -1)
            processes[idx].start = time;

        remaining[idx]--;
        time++;
        cpuBurst++;

        if (remaining[idx] == 0) {
            processes[idx].completion = time;
            completed++;

            Block b;
            b.time = blockStart;
            b.pid = processes[idx].id;
            b.duration = time - blockStart;
            b.finished = true;
            gantt.push_back(b);

            current = -1;
        }
    }

    printHeader(caseNum, algo);
    printGantt(gantt);
    printStats(processes, time, cpuBurst);
}