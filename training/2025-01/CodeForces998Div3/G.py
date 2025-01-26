def solve():
    n = int(input())
    val = []
    first_vals = list(map(int, input().split()))
    second_vals = list(map(int, input().split()))
    for i in range(n):
        val.append((first_vals[i], second_vals[i]))
    val.sort(key=lambda x: min(x[0], x[1]))

    dp = [[False]*5 for _ in range(n)]
    dp[0][1] = True
    dp[0][4] = True
    for i in range(1, n):
        if val[i-1][0] < val[i][0] and val[i-1][1] < val[i][1]:
            dp[i][1] |= dp[i-1][1]
            dp[i][2] |= dp[i-1][4]
            dp[i][3] |= dp[i-1][3]
            dp[i][4] |= dp[i-1][2]
        if val[i-1][0] < val[i][1] and val[i-1][1] < val[i][0]:
            dp[i][1] |= dp[i-1][2]
            dp[i][2] |= dp[i-1][3]
            dp[i][3] |= dp[i-1][4]
            dp[i][4] |= dp[i-1][1]

    print("YES" if (dp[n-1][1] or dp[n-1][2]) else "NO")


if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        solve()
