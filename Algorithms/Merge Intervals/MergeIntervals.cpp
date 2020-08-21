/** Problem statement
  * Given a list of intervals, merge all the overlapping intervals to produce a list that has only mutually
  * exclusive intervals.
  *
  * Example 1:
  * Intervals: [[1,4], [2,5], [7,9]]
  * Output: [[1,5], [7,9]]
  * Explanation: Since the first two intervals [1,4] and [2,5] overlap, we merged them into one [1,5].
  *
  * Example 2:
  * Intervals: [[6,7], [2,4], [5,9]]
  * Output: [[2,4], [5,9]]
  * Explanation: Since the intervals [6,7] and [5,9] overlap, we merged them into one [5,9].
  *
  * Example 3:
  * Intervals: [[1,4], [2,6], [3,5]]
  * Output: [[1,6]]
  * Explanation: Since all the given intervals overlap, we merged them into one.
  */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
  int start, end;
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

bool comparator(const Interval& i1, const Interval& i2) {
  return i1.start < i2.start;
}

vector<Interval> mergeIntervals(vector<Interval>& arr) {
  int n = arr.size();
  if (n < 2) return arr;

  vector<Interval> result;
  sort(arr.begin(), arr.end(), comparator);

  vector<Interval>::iterator itr = arr.begin();
  Interval curr = *itr;
  itr++;
  int currStart = curr.start;
  int currEnd = curr.end;

  while (itr != arr.end()) {
    curr = *itr;
    itr++;
    if (curr.start <= currEnd) { // overlapping intervals
      currEnd = max(curr.end, currEnd); // merge
    } else { // non overlapping
      result.push_back({ currStart, currEnd });
      currStart = curr.start;
      currEnd = curr.end;
    }
  }

  result.push_back({ currStart, currEnd });
  return result;
}

int main() {
  vector<Interval> arr = {{1,4}, {2,5}, {7,9}};
  vector<Interval> result = mergeIntervals(arr);
  printResult(result);

  arr = {{6,7}, {2,4}, {5,9}};
  result = mergeIntervals(arr);
  printResult(result);

  arr = {{1,4}, {2,6}, {3,5}};
  result = mergeIntervals(arr);
  printResult(result);

  return 0;
}
