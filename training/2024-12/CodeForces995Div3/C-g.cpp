#include <stdio.h>
#define ll long long
int a[310000], q[310000], ans[310000];
long long int t, n, m, k, j;
int main() {
  scanf("%lld", &t);
  for (long long int i = 0; i < t; i++) {
    for (j = 0; j < 310000; j++) {
      ans[j] = 0;
      a[j] = 0;
      q[j] = 0;
    }
    scanf("%lld %lld %lld", &n, &m, &k);
    for (j = 0; j < m; j++) {
      scanf("%d", &a[j]);
    }
    for (j = 0; j < k; j++) {
      scanf("%d", &q[j]);
    }
    if (n - 1 > k) {
      for (j = 0; j < m; j++) {
        printf("%d", ans[j]);
      }
      printf("\n");
    }
    if (n - 1 < k) {
      for (j = 0; j < m; j++) {
        printf("%d", ans[j] + 1);
      }
      printf("\n");
    }
    if (n - 1 == k) {
      int sum1 = 0;
      int sum2 = 0;
      for (int p = 0; p < m; p++) {
        sum2 += q[p];
      }
      sum1 = (1 + n) * n / 2;
      int ren = sum1 - sum2;
      ans[ren - 1] = 1;
      for (j = 0; j < m; j++) {
        printf("%d", ans[j]);
      }
      printf("\n");
    }
  }
  return 0;
}