#include "job.h"
#include <queue>
#include <vector>

using namespace std;

// Helper function to perform depth-first search for detecting cycles
bool detectCycle(int job, const vector<vector<int>>& adjList, vector<bool>& visited, vector<bool>& onStack) {
    if (!visited[job]) {
        visited[job] = true;
        onStack[job] = true;

        for (int neighbor : adjList[job]) {
            if (!visited[neighbor] && detectCycle(neighbor, adjList, visited, onStack)) {
                return true;
            } else if (onStack[neighbor]) {
                return true;
            }
        }
    }

    onStack[job] = false;
    return false;
}

// Function to check if all jobs can be completed given their dependencies
bool canFinish(int n, vector<pair<int, int>> &dependencies) {
    vector<vector<int>> graph(n + 1);
    for (const auto& edge : dependencies) {
        graph[edge.first].push_back(edge.second);
    }

    vector<bool> visited(n + 1, false), onStack(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && detectCycle(i, graph, visited, onStack)) {
            return false;
        }
    }

    return true;
}

// Function to compute the earliest time slot for each job to start
vector<int> earliest_time_slot(int n, vector<pair<int, int>> &dependencies) {
    vector<vector<int>> graph(n + 1);
    vector<int> inDegree(n + 1, 0);
    vector<int> times(n + 1, 0);

    // Construct graph and compute in-degrees
    for (const auto& dep : dependencies) {
        graph[dep.first].push_back(dep.second);
        inDegree[dep.second]++;
    }

    queue<int> readyQueue;
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            readyQueue.push(i);
            times[i] = 1;
        }
    }

    // Process jobs in topological order
    while (!readyQueue.empty()) {
        int current = readyQueue.front();
        readyQueue.pop();

        for (int next : graph[current]) {
            times[next] = max(times[next], times[current] + 1);
            if (--inDegree[next] == 0) {
                readyQueue.push(next);
            }
        }
    }

    times.erase(times.begin()); // Adjust index to be 0-based
    return times;
}

// Check if a specific job can run at a given time
bool canRun(int n, vector<pair<int, int>> &dependencies, int j, int i) {
    vector<int> slots = earliest_time_slot(n, dependencies);
    return slots[j - 1] <= i;
}
