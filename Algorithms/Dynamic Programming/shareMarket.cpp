/** Problem statement:
  * You are given an array in which the i'th element is the price of a given stock
  * on day 'i'. If you are permitted to complete at most 1 transaction (i.e. buy once
  * and sell once), what is the maximum profit you can gain?
  * It is to be noted that you cannot sell a stock before you buy one
  */

#include <iostream>
#include <vector>

using namespace std;

int maxProfit(vector<int>& price) {
  int n = price.size();
  vector<int> min_uptil(n);
  vector<int> max_profit(n);
  int result = INT32_MIN;

  min_uptil[0] = price[0];
  for (int i = 1; i < n; i++) {
    min_uptil[i] = min(min_uptil[i - 1], price[i]);
  }

  for (int i = 0; i < n; i++) {
    max_profit[i] = price[i] - min_uptil[i];
    if (result < max_profit[i])
      result = max_profit[i];
  }

  return result;
}

int main() {
  vector<int> price = { 8, 1, 2, 4, 6, 3 };
  cout << maxProfit(price) << endl;
  return 0;
}
