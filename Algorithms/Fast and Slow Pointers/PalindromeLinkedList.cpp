/** Problem statement
  * Given the head of a Singly LinkedList, write a method to check if the LinkedList is a palindrome or not.
  *
  * Your algorithm should use constant space and the input LinkedList should be in the original form once
  * the algorithm is finished. The algorithm should have O(N) time complexity where ‘N’ is the number of
  * nodes in the LinkedList.
  *
  * Example 1:
  * Input: 2 -> 4 -> 6 -> 4 -> 2 -> null
  * Output: true
  *
  * Example 2:
  * Input: 2 -> 4 -> 6 -> 4 -> 2 -> 2 -> null
  * Output: false
  */

#include <iostream>

using namespace std;

class ListNode {
public:
  int value;
  ListNode *next;

  ListNode(int val) {
    this->value = val;
    next = NULL;
  }
};

ListNode* reverse(ListNode *head) {
  ListNode *prev = NULL, *curr = head, *next;
  while (curr != NULL) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  return prev;
}

bool isPalindrome(ListNode *head) {
  if (head == NULL || head->next == NULL)
    return true;

  ListNode *slow = head, *fast = head;

  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
  }

  ListNode *secondHalfHead = reverse(slow);
  ListNode *secondHalfHeadCopy = secondHalfHead;

  while (head != NULL && secondHalfHead != NULL) {
    if (head->value != secondHalfHead->value) {
      break;
    }
    head = head->next;
    secondHalfHead = secondHalfHead->next;
  }

  reverse(secondHalfHeadCopy);
  if (head == NULL || secondHalfHead == NULL)
    return true;

  return false;
}

int main() {
  ListNode *head = new ListNode(2);
  head->next = new ListNode(4);
  head->next->next = new ListNode(6);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(2);
  cout << isPalindrome(head) << endl;

  head->next->next->next->next->next = new ListNode(2);
  cout << isPalindrome(head) << endl;

  return 0;
}
