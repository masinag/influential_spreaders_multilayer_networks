logs_file = "simulations/logs/2020-06-03_13:51:25:272.log"


# 2020-06-03_14:01:50:453 - Simulation 2 out of 2 done

def get_sec(t):
    date, time = t.split('_')
    year, month, day = map(int, date.split('-')) 
    hour, minute, second, _  = map(int, time.split(':')) 
    return second + 60*minute + 60*60*hour + 24*60*60*day


def time_diff(end, start):
    return get_sec(end) - get_sec(start)

sec = 0
i = 0
with open(logs_file) as f: 
    start_read = False
    for r in f:

        timestamp, msg = r.split(' - ')
        if i == 0:
            first = timestamp
        else:
            last = timestamp
        if msg.startswith('#'):
            start_read = True
            start = timestamp
        elif start_read:
            start_read = False
            sec += time_diff(timestamp, start)
        i += 1
print(sec)
tot_sec = time_diff(last, first)
s = tot_sec % 60
tot_sec //= 60
m = tot_sec % 60
tot_sec //= 60
h = tot_sec
print(h, m, s)