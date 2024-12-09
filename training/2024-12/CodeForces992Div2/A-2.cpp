#include <stdio.h>
int main() {
  int n, i, j, t, k, a, flag;
  int num[30], ka[101];
  scanf("%d", &t);
  for (i = 0; i < t; i++) {
    scanf("%d", &n);
    scanf("%d", &k);
    for (j = 0; j < n; j++) {
      scanf("%d", &num[j]);
    }
    for (j = 0; j < n; j++) {
      num[j] = num[j] % k;
    }
    for (j = 0; j < 102; j++) {
      ka[j] = 0;
    }
    for (j = 0; j < n; j++) {
      ka[num[j]]++;
    }
    int check = 0;
    for (j = 0; j < 102; j++) {
      if (ka[j] == 1) {
        flag = j;
        for (a = 0; a < n; a++) {
          if (num[a] == flag) {
            printf("YES\n");
            printf("%d\n", a + 1);
            check = 1;
            break;
          }
        }
        if (check)
          break;
      }
    }
    if (check == 0) {
      printf("NO\n");
    }
  }
  return 0;
}