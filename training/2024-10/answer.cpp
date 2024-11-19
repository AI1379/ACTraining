#include <stdio.h>
int main() {
  int l = 1, r, mid;
  char ch;
  scanf("%d", &r);
  while (l < r) {
    mid = (l + r) / 2;
    printf("%d\n", mid);
    fflush(stdout);
    scanf("%c", &ch);
    if (ch == '<')
      r = mid - 1;
    else if (ch == '>')
      l = mid + 1;
    else
      break;
  }
  return 0;
}