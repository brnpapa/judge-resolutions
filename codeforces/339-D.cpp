/*
   searching | segment tree (ST)
   difficulty: easy
   problem: xenia and bit operations
   date: 07/Dec/2019
   author: @brnpapa
*/
#include <cmath>
#include <iostream>
#include <vector>
#define MAX_N 132000 // pow(2, 17)
using namespace std;

int arr[MAX_N];
int N;

vector<int> bt;
int l(int v) { return 2 * v + 1; };
int r(int v) { return 2 * v + 2; };

void build(int v, int start, int end, bool isExcl) {
   if (start == end) {
      bt[v] = arr[start];
      return;
   }
   int mid = (start + end) / 2;
   build(l(v), start, mid, !isExcl);
   build(r(v), mid + 1, end, !isExcl);

   bt[v] = isExcl ? (bt[l(v)] ^ bt[r(v)]) : (bt[l(v)] | bt[r(v)]);
}

void update(int v, int start, int end, bool isExcl, int idx, int value) {
   if (start == end) {
      bt[v] = value;
      return;
   }
   int mid = (start + end) / 2;
   if (idx <= mid)
      update(l(v), start, mid, !isExcl, idx, value);
   else
      update(r(v), mid + 1, end, !isExcl, idx, value);

   bt[v] = isExcl ? (bt[l(v)] ^ bt[r(v)]) : (bt[l(v)] | bt[r(v)]);
}

int main() {
   int M;
   cin >> N >> M;

   bool opRootIsExclusive = N % 2 == 0;
   N = pow(2, N);

   for (int i = 0; i < N; i++)
      cin >> arr[i];

   bt.assign(2 * N, 0);
   build(0, 0, N-1, opRootIsExclusive);

   int p, b;
   while (M--) {
      cin >> p >> b;
      update(0, 0, N-1, opRootIsExclusive, p-1, b);
      cout << bt[0] << endl;
   }

   return 0;
}