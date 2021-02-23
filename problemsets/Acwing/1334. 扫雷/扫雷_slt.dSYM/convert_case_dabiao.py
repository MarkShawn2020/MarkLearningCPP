with open("/problemsets/Acwing/1334. 扫雷/case-n1m1000.txt", "r") as f:
    s = f.read()

map = {
    'S': "Sweep",
    'D': "DSweep",
    'Q': "Quit",
    'F': "Flag"
}
st = s.split(",")
case = "\n".join(map[i[0]] + i[1:] for i in st if i)

print(case)