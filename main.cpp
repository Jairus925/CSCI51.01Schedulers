#include <iostream>
#include <fstream>
#include <vector>
#include "scheduler.h"

using namespace std;

int main() {
    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: could not open input file " << filename << "\n";
        return 1;
    }

    int T;
    infile >> T;

    vector<TestCase> testCases;

    for (int t = 1; t <= T; t++) {
        int X;
        string algo;
        infile >> X >> algo;

        int quantum = 0;
        if (algo == "RR")
            infile >> quantum;

        vector<Process> processes;
        for (int i = 0; i < X; i++) {
            Process p;
            p.id = i + 1;
            infile >> p.arrival >> p.burst >> p.nice;
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
        // else if (tc.algo == "SRTF")
        //     runSRTF(tc.processes, tc.caseNum, tc.algo);
        else if (tc.algo == "P")
            runPriority(tc.processes, tc.caseNum, tc.algo);
        // else if (tc.algo == "RR")
        //     runRR(tc.processes, tc.caseNum, tc.algo, tc.quantum);
        cout << "\n";
    }

    return 0;
}