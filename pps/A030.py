n, first = map(int, input().split())

gg, gb, bg, bb = map(float, input().split()) # good + good, good + bad, bad + good, bad + bad

gp = [0] * n
bp = [0] * n

if not first :
    gp[0] = gg
    bp[0] = gb
else :
    gp[0] = bg
    bp[0] = bb

for i in range(1, n) :
    gp[i] = gp[i-1] * gg + bp[i-1] * bg
    bp[i] = gp[i-1] * gb + bp[i-1] * bb

print(round(gp[-1] * 1000))
print(round(bp[-1] * 1000))