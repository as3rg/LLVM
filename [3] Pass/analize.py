import sys

distribution = {}

WINDOW = int(sys.argv[1]) if len(sys.argv) >= 2 else 5

def update_win(win, v):
    return win[1:] + (v,)

def add_to_stat(win):
    global distribution
    if win not in distribution:
        distribution[win] = 0
    distribution[win] += 1

with open("build/log.txt") as f:
    win = ("",) * WINDOW
    for _ in range(WINDOW):
        win = update_win(win, f.readline().strip())
    add_to_stat(win)
    
    i = WINDOW

    for l in f:
        i += 1
        if i % 1000000 == 0:
            print ("\033[A                             \033[A")
            print(f"{i}")

        win = update_win(win, l.strip())
        add_to_stat(win)
    
    res = distribution.items()
    res = sorted(res, key=lambda a: a[1], reverse=True)

with open(f"build/analize{WINDOW}.tsv", "w") as f:
    f.write(f"cnt\t{'\t'.join(f'line{i}' for i in range(1, WINDOW + 1))}\n")
    for k,v in res:
        f.write(f"{v}\t{'\t'.join(k)}\n")