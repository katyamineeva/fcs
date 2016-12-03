f(billboards, n) {
    res[n];
    res[1] = b1;
    for (i = 2 .. n) {
        near = findNearest(i);
        res[i] = max(b_i + res[near], res[i - 1]);
    }
}
