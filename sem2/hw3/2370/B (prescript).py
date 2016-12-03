def fib():
    f = [1, 1]
    maxVal = 10**5001
    while f[-1] // maxVal == 0:
        f.append(f[-1] + f[-2])
    print(len(f))

fib()