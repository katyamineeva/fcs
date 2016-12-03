eps = 0.00000000001
k1, b1 = map(int, input().split())
k2, b2 = map(int, input().split())

if (abs(k1 - k2) < eps and abs(b1 - b2) < eps):
    print("coincide")

elif (abs(k1 - k2) < eps and abs(b1 - b2) > eps):
    print("parallel")

else:
    print("intersect")
    x0 = (b2 - b1) / (k1 - k2)
    y0 = k1 * x0 + b1
    print(x0, y0)