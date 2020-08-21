/** Problem statement
  * Given a list of non-overlapping intervals sorted by their start time, insert a given interval at the correct
  * position and merge all necessary intervals to produce a list that has only mutually exclusive intervals.
  *
  * Example 1:
  * Input: Intervals=[[1,3], [5,7], [8,12]], New Interval=[4,6]
  * Output: [[1,3], [4,7], [8,12]]
  * Explanation: After insertion, since [4,6] overlaps with [5,7], we merged them into one [4,7].
  *
  * Example 2:
  * Input: Intervals=[[1,3], [5,7], [8,12]], New Interval=[4,10]
  * Output: [[1,3], [4,12]]
  * Explanation: After insertion, since [4,10] overlaps with [5,7] & [8,12], we merged them into [4,12].
  *
  * Example 3:
  * Input: Intervals=[[2,3],[5,7]], New Interval=[1,4]
  * Output: [[1,4], [5,7]]
  * Explanation: After insertion, since [1,4] overlaps with [2,3], we merged them into one [1,4].
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

vector<Interval> insertInterval(vector<Interval> arr, Interval newInterval) {
  int n = arr.size();

  if (n == 0)
    return vector<Interval>{newInterval};

  vector<Interval> result;

  int i = 0;
  while (i < n && arr[i].end < newInterval.start) { // non overlapping
    result.push_back(arr[i++]);
  }

  // check for overlapping intervals and merge them
  while (i < n && arr[i].start <= newInterval.end) {
    newInterval.start = min(arr[i].start, newInterval.start);
    newInterval.end = max(arr[i].end, newInterval.end);
    i++;
  }

  // push the new interval in the resultant array
  result.push_back(newInterval);

  // push the remaining non overlapping intervals
  while (i < n) {
    result.push_back(arr[i++]);
  }

  return result;
}

int main() {
  vector<Interval> arr = {{1,3}, {5,7}, {8,12}};
  vector<Interval> result = insertInterval(arr, (Interval){4,6});
  printResult(result);

  arr = {{1,3}, {5,7}, {8,12}};
  result = insertInterval(arr, (Interval){4,10});
  printResult(result);

  arr = {{2,3}, {5,7}};
  result = insertInterval(arr, (Interval){1,4});
  printResult(result);

  return 0;
}
