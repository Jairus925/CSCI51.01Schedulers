#include <iostream>
#include <vector>
#include "scheduler.h"

using namespace std;

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++)
    {
        int X;
        string algo;

        cin >> X >> algo;

        int quantum = 0;
        if (algo == "RR")
            cin >> quantum;

        vector<Process> processes;

        for (int i = 0; i < X; i++)
        {
            Process p;
            p.id = i + 1;
            cin >> p.arrival >> p.burst >> p.nice;
            processes.push_back(p);
        }

        if (algo == "FCFS")
            runFCFS(processes, t, algo);
        /*
        else if (algo == "SJF")
            runSJF(processes, t, algo);
        else if (algo == "SRTF")
            runSRTF(processes, t, algo);
        else if (algo == "P")
            runPriority(processes, t, algo);
        else if (algo == "RR")
            runRR(processes, t, algo, quantum);
        */

        if (t != T)
            cout << "\n";
    }

    return 0;
}