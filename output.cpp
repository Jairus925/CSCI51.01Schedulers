#include <iostream>
#include <iomanip>
#include "scheduler.h"

using namespace std;

void printHeader(int caseNum, string algo)
{
    cout << caseNum << " " << algo << "\n";
}

void printGantt(const vector<Block>& gantt)
{
    for (auto &b : gantt)
    {
        cout << b.time << " " << b.pid << " " << b.duration;
        if (b.finished) cout << "X";
        cout << "\n";
    }
}

void printStats(vector<Process>& p, int totalTime, int cpuBurst)
{
    int n = p.size();

    double totalWaiting = 0;
    double totalTurnaround = 0;
    double totalResponse = 0;

    cout << "Total time elapsed: " << totalTime << "ns\n";
    cout << "Total CPU burst time: " << cpuBurst << "ns\n";

    double util = (double)cpuBurst / totalTime * 100;
    cout << "CPU Utilization: " << util << "%\n";

    double throughput = (double)n / totalTime;
    cout << "Throughput: " << throughput << " processes/ns\n";

    cout << "Waiting times:\n";
    for (auto &proc : p)
    {
        int turnaround = proc.completion - proc.arrival;
        int waiting = turnaround - proc.burst;
        totalWaiting += waiting;

        cout << "Process " << proc.id << ": " << waiting << "ns\n";
    }

    cout << "Average waiting time: " << totalWaiting / n << "ns\n";

    cout << "Turnaround times:\n";
    for (auto &proc : p)
    {
        int turnaround = proc.completion - proc.arrival;
        totalTurnaround += turnaround;

        cout << "Process " << proc.id << ": " << turnaround << "ns\n";
    }

    cout << "Average turnaround time: " << totalTurnaround / n << "ns\n";

    cout << "Response times:\n";
    for (auto &proc : p)
    {
        int response = proc.start - proc.arrival;
        totalResponse += response;

        cout << "Process " << proc.id << ": " << response << "ns\n";
    }

    cout << "Average response time: " << totalResponse / n << "ns\n";
}