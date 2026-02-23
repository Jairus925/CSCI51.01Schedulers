#include <iostream>
#include <vector>
#include "scheduler.h"

using namespace std;

int main() {
    int T;
    cin >> T;

    vector<TestCase> testCases;

    for (int t = 1; t <= T; t++) {
        int X;
        string algo;
        cin >> X >> algo;

        int quantum = 0;
        if (algo == "RR")
            cin >> quantum;

        vector<Process> processes;
        for (int i = 0; i < X; i++) {
            Process p;
            p.id = i + 1;
            cin >> p.arrival >> p.burst >> p.nice;
            processes.push_back(p);
        }

        TestCase tc;
        tc.caseNum = t;
        tc.algo = algo;
        tc.quantum = quantum;
        tc.processes = processes;

        testCases.push_back(tc);
    }


    for (auto &tc : testCases) {
        if (tc.algo == "FCFS")
            runFCFS(tc.processes, tc.caseNum, tc.algo);
        else if (tc.algo == "SJF")
            runSJF(tc.processes, tc.caseNum, tc.algo);
        else if (tc.algo == "SRTF")
            runSRTF(tc.processes, tc.caseNum, tc.algo);
        /*
        else if (tc.algo == "P")
            runPriority(tc.processes, tc.caseNum, tc.algo);
        */
        else if (tc.algo == "RR")
            runRR(tc.processes, tc.caseNum, tc.algo, tc.quantum);
        
        cout << "\n";
    }

    return 0;
}