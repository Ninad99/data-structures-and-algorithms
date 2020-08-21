/** Problem statement
  * Given two lists of intervals, find the intersection of these two lists. Each list consists of disjoint
  * intervals sorted on their start time.
  *
  * Example 1:
  * Input: arr1=[[1, 3], [5, 6], [7, 9]], arr2=[[2, 3], [5, 7]]
  * Output: [2, 3], [5, 6], [7, 7]
  * Explanation: The output list contains the common intervals between the two lists.
  *
  * Example 2:
  * Input: arr1=[[1, 3], [5, 7], [9, 12]], arr2=[[5, 10]]
  * Output: [5, 7], [9, 10]
  * Explanation: The output list contains the common intervals between the two lists.
  */

#include <iostream>
#include <vector>

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

vector<Interval> getIntersection(vector<Interval> arr1, vector<Interval> arr2) {
  int i = 0, j = 0, m = arr1.size(), n = arr2.size();
  vector<Interval> result;
  while (i < m && j < n) {
    if ((arr1[i].start >= arr2[j].start && arr1[i].start <= arr2[j].end) ||
        (arr2[j].start >= arr1[i].start && arr2[j].start <= arr1[i].end)) {
      Interval c;
      c.start = max(arr1[i].start, arr2[j].start);
      c.end = min(arr1[i].end, arr2[j].end);
      result.push_back(c);
    }

    if (arr1[i].end < arr2[j].end) i++;
    else j++;
  }

  return result;
}

int main() {
  vector<Interval> arr1 = {{1, 3}, {5, 6}, {7, 9}};
  vector<Interval> arr2 = {{2, 3}, {5, 7}};
  vector<Interval> result = getIntersection(arr1, arr2);
  printResult(result);

  arr1 = {{1, 3}, {5, 7}, {9, 12}};
  arr2 = {{5, 10}};
  result = getIntersection(arr1, arr2);
  printResult(result);

  arr1 = {{1, 2}, {3, 4}, {5, 8}, {9, 12}, {15, 19}};
  arr2 = {{2, 5}, {7, 10}, {11, 14}, {16, 19}};
  result = getIntersection(arr1, arr2);
  printResult(result);

  return 0;
}
