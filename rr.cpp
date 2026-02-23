#include "scheduler.h"
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

// "Wraps" the process so its progress can be tracked 
struct RRProcess {
    Process* orig;
    int remaining_burst;
    bool has_started;
};

// Compares the arrival times
bool compareArrival(const RRProcess& a, const RRProcess& b) {
    if (a.orig->arrival != b.orig->arrival)
        return a.orig->arrival < b.orig->arrival;
    return a.orig->id < b.orig->id;
}

void runRR(std::vector<Process> processes, int caseNum, std::string algo, int quantum) {
    int n = processes.size();
    vector<RRProcess> rrp(n);
    
    // Initialize wrapper objects
    for (int i = 0; i < n; i++) {
        rrp[i].orig = &processes[i];
        rrp[i].remaining_burst = processes[i].burst;
        rrp[i].has_started = false;
    }

    sort(rrp.begin(), rrp.end(), compareArrival);

    int time = 0;
    int completed_count = 0;
    int next_arrival_idx = 0;
    int total_cpu_burst = 0;

    // Use 2 queues so new arrivals can be prioritized
    queue<RRProcess*> new_arrivals;
    queue<RRProcess*> preempted;
    vector<Block> gantt;

    while (completed_count < n) {
        // Add newly arrived processes up to the current 'time'
        while (next_arrival_idx < n && rrp[next_arrival_idx].orig->arrival <= time) {
            new_arrivals.push(&rrp[next_arrival_idx]);
            next_arrival_idx++;
        }

        if (new_arrivals.empty() && preempted.empty()) {
            if (next_arrival_idx < n) {
                // Jump time forward to the next arrival
                time = rrp[next_arrival_idx].orig->arrival;
                while (next_arrival_idx < n && rrp[next_arrival_idx].orig->arrival <= time) {
                    new_arrivals.push(&rrp[next_arrival_idx]);
                    next_arrival_idx++;
                }
            } else {
                break; 
            }
        }

        // Pick next process
        RRProcess* current = nullptr;
        if (!new_arrivals.empty()) {
            current = new_arrivals.front();
            new_arrivals.pop();
        } else if (!preempted.empty()) {
            current = preempted.front();
            preempted.pop();
        }

        if (current != nullptr) {
            int duration = min(quantum, current->remaining_burst);

            // Record start time on first execution
            if (!current->has_started) {
                current->orig->start = time;
                current->has_started = true;
            }

            // Gantt block
            Block b;
            b.time = time;
            b.pid = current->orig->id;
            b.duration = duration;

            time += duration;
            current->remaining_burst -= duration;
            total_cpu_burst += duration;

            if (current->remaining_burst == 0) {
                b.finished = true;
                current->orig->completion = time;
                completed_count++;
            } else {
                b.finished = false;
            }
            
            gantt.push_back(b);

            // Check for any new arrivals again so they can go in the front of the queue
            while (next_arrival_idx < n && rrp[next_arrival_idx].orig->arrival <= time) {
                new_arrivals.push(&rrp[next_arrival_idx]);
                next_arrival_idx++;
            }

            // If preempted but not finished, add to preempted queue
            if (!b.finished) {
                preempted.push(current);
            }
        }
    }

    printHeader(caseNum, algo);
    printGantt(gantt);
    printStats(processes, time, total_cpu_burst);
}