/** Problem statement
  * We are given a list of Jobs. Each job has a Start time, an End time, and a CPU load when it is running.
  * Our goal is to find the maximum CPU load at any time if all the jobs are running on the same machine.
  *
  * Example 1:
  * Jobs: [[1,4,3], [2,5,4], [7,9,6]]
  * Output: 7
  * Explanation: Since [1,4,3] and [2,5,4] overlap, their maximum CPU load (3+4=7) will be when both the
  * jobs are running at the same time i.e., during the time interval (2,4).
  *
  * Example 2:
  * Jobs: [[6,7,10], [2,4,11], [8,12,15]]
  * Output: 15
  * Explanation: None of the jobs overlap, therefore we will take the maximum load of any job which is 15.
  *
  * Example 3:
  * Jobs: [[1,4,2], [2,4,1], [3,6,5]]
  * Output: 8
  * Explanation: Maximum CPU load will be 8 as all jobs overlap during the time interval [3,4].
  */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Job {
  int start, end, load;
};

bool comparator(const Job& j1, const Job& j2) {
  return j1.start < j2.start;
}

struct pqcomparator {
  bool operator()(const Job& j1, const Job& j2) {
    return j1.end > j2.end;
  }
};

int findMaxCPULoad(vector<Job>& jobs) {
  if (jobs.empty())
    return 0;

  sort(jobs.begin(), jobs.end(), comparator);

  int maxCpuLoad = 0, n = jobs.size(), result = 0;
  priority_queue<Job, vector<Job>, pqcomparator> minHeap;
  for (int i = 0; i < n; i++) {
    while (!minHeap.empty() && minHeap.top().end < jobs[i].start) {
      maxCpuLoad -= minHeap.top().load;
      minHeap.pop();
    }

    minHeap.push(jobs[i]);
    maxCpuLoad += jobs[i].load;
    result = max(result, maxCpuLoad);
  }

  return result;
}

int main() {
  vector<Job> arr = {{1,4,3}, {2,5,4}, {7,9,6}};
  cout << findMaxCPULoad(arr) << endl;

  arr = {{6,7,10}, {2,4,11}, {8,12,15}};
  cout << findMaxCPULoad(arr) << endl;

  arr = {{1,4,2}, {2,4,1}, {3,6,5}};
  cout << findMaxCPULoad(arr) << endl;

  return 0;
}
