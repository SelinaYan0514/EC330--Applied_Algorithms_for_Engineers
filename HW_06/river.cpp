#include "river.h"
#include <algorithm>
#include <queue>
#include <vector>

// Helper function to run Breadth-First Search (BFS) and fill distance vector
void runBFS(const river& r, int start, std::vector<int>& distances) {
    int n = r.size();
    std::queue<int> queue;
    distances[start] = 0;
    queue.push(start);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int adj = 0; adj < n; ++adj) {
            if (r[current][adj] && distances[adj] == -1) {
                distances[adj] = distances[current] + 1;
                queue.push(adj);
            }
        }
    }
}

// Part (a): Determine source nodes reachable from a starting node 't'
std::vector<int> start(const river& r, int t) {
    int n = r.size();
    std::vector<int> sources;
    std::vector<bool> visited(n, false);
    std::queue<int> queue;

    queue.push(t);
    visited[t] = true;

    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();
        bool isSource = true;

        for (int i = 0; i < n; ++i) {
            if (r[i][node] == 1) {
                isSource = false;
                if (!visited[i]) {
                    queue.push(i);
                    visited[i] = true;
                }
            }
        }

        if (isSource) {
            sources.push_back(node);
        }
    }

    std::sort(sources.begin(), sources.end());
    return sources;
}

// Part (b): Identify earliest possible meeting points for two nodes
std::vector<int> meet(const river& r, int ryan, int mira) {
    int n = r.size();
    std::vector<int> distRyan(n, -1), distMira(n, -1);

    runBFS(r, ryan, distRyan);
    runBFS(r, mira, distMira);

    std::vector<int> meetingPoints;
    for (int i = 0; i < n; ++i) {
        if (distMira[i] != -1 && distRyan[i] != -1) {
            bool isValidMeetingPoint = true;
            for (int j = 0; j < n; ++j) {
                if (r[j][i] && distMira[j] != -1 && distRyan[j] != -1) {
                    isValidMeetingPoint = false;
                    break;
                }
            }
            if (isValidMeetingPoint) {
                meetingPoints.push_back(i);
            }
        }
    }

    std::sort(meetingPoints.begin(), meetingPoints.end());
    return meetingPoints;
}
