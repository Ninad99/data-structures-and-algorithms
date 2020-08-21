/** Problem statement
  * For ‘K’ employees, we are given a list of intervals representing the working hours of each employee.
  * Our goal is to find out if there is a free interval that is common to all employees. You can assume
  * that each list of employee working hours is sorted on the start time.
  *
  * Example 1:
  * Input: Employee Working Hours=[[[1,3], [5,6]], [[2,3], [6,8]]]
  * Output: [3,5]
  * Explanation: Both the employess are free between [3,5].
  *
  * Example 2:
  * Input: Employee Working Hours=[[[1,3], [9,12]], [[2,4]], [[6,8]]]
  * Output: [4,6], [8,9]
  * Explanation: All employess are free between [4,6] and [8,9].
  *
  * Example 3:
  * Input: Employee Working Hours=[[[1,3]], [[2,4]], [[3,5], [7,9]]]
  * Output: [5,7]
  * Explanation: All employess are free between [5,7].
  */

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

struct Interval {
  int start, end;
};

struct pqcomparator {
  bool operator()(const pair<Interval, pair<int, int>>& p1,
                  const pair<Interval, pair<int, int>>& p2) {
                    return p1.first.start > p2.first.start;
                  }
};

void printResult(vector<Interval>& result) {
  cout << "[";
  for (int i = 0; i < result.size(); i++)
    if (i != result.size() - 1)
      cout << "{" << result[i].start << "," << result[i].end << "}, ";
    else
      cout << "{" << result[i].start << "," << result[i].end << "}";
  cout << "]\n";
}

vector<Interval> findEmployeeFreeTime(vector<vector<Interval>>& schedules) {
  vector<Interval> result;
  if (schedules.empty())
    return result;

  int K = schedules.size();
  priority_queue<pair<Interval, pair<int, int>>, vector<pair<Interval, pair<int, int>>>, pqcomparator> minHeap;

  for (int i = 0; i < K; i++) {
    minHeap.push(make_pair(schedules[i][0], make_pair(i, 0)));
  }

  Interval prevInterval = minHeap.top().first;
  while (!minHeap.empty()) {
    pair<Interval, pair<int, int>> queueTop = minHeap.top(); minHeap.pop();

    if (prevInterval.end < queueTop.first.start) {
      result.push_back({ prevInterval.end, queueTop.first.start });
      prevInterval = queueTop.first;
    } else {
      if (prevInterval.end < queueTop.first.end) {
        prevInterval = queueTop.first;
      }
    }

    vector<Interval> employeeIntervals = schedules[queueTop.second.first];
    if (employeeIntervals.size() >= queueTop.second.second + 1) {
      minHeap.push(
        make_pair(
          employeeIntervals[queueTop.second.second + 1],
          make_pair(queueTop.second.first, queueTop.second.second + 1)
        )
      );
    }
  }

  return result;
}

int main() {
  vector<vector<Interval>> schedules = {{{1,3}, {5,6}}, {{2,3}, {6,8}}};
  vector<Interval> result = findEmployeeFreeTime(schedules);
  printResult(result);

  schedules = {{{1,3}, {9,12}}, {{2,4}}, {{6,8}}};
  result = findEmployeeFreeTime(schedules);
  printResult(result);

  schedules = {{{1,3}}, {{2,4}}, {{3,5}, {7,9}}};
  result = findEmployeeFreeTime(schedules);
  printResult(result);

  return 0;
}
