ans = {1,8}
sum = 0
ans = sorted(ans)
for ind, val in enumerate(ans):
    sum = (sum + ind * val) % (1000000007)

print(sum)