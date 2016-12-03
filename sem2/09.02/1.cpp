OPT[n]
OPT[i]
OPT[0] = 0
OPT[1] = max(0, p1)

for (i = 2 .. n) {
    OPT[i] = max(p[i] + OPT[i - 2], OPT[i - 1]);
}


Solution (OPT[1 .. n]) {
    set sol;
    i = n
    while i > 1 do {
        if p[i] + OPT[i - 2] > OPT[i - 1] {
            sol.add(i);
            i = i - 2;
        } else {
            i = i - 1;
        }
    }
    if i == 1 {
        sol.add(1)
    }
}

-----------------------------------------------

OPT[n]
OPT[i]
OPT[0] = 0
OPT[1] = max(0, p1)

for (i = 2 .. n) {
    if (p[i] + OPT[i - 2] > OPT[i - 1]) {
        H[i] = i - 2
        OPT[i] = p[i] + OPT[i - 2]
    }
    else {
        H[i] = i - 1
        OPT[i] = OPT[i - 1]
    }
    OPT[i] = max(p[i] + OPT[i - 2], OPT[i - 1]);
}

