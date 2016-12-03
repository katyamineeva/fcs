// mark1:

// test 20%
// homework 12% * 5
// seminars 20%

// mark2:

// exam

// mark = 0.7 * mark1 + 0.3 * mark2

in case n = (m(m + 1) / 2)


Hanoi4(n, i, j, k, l) {
    if (n > 0) {
        Hanoi4(n - m, i , l, j, k);
        Hanoi3(m, i, j, k);
        Hanoi4(n - m, l, j, i, k);
    }
}


m  * 2^m - (2^m - 1) = (m - 1) 2^m + 1

Hanoi(n, i, j, P){
    if (n > 0) {
        choose p from P
        R = P \ {p};
        if R.size() == 0 {
            Hanoi3(n, i, j, p);
            Hanoi3(n, i, j, p);
        } else {
            Hanoi(n - m, i, p, R + {j});
            Hanoi(m, i, j, R);
        }
    }
}
