
#include <iostream>
#include <vector>

//Recursive with memo

//Helper function for genA_recur(int n)
unsigned long genA_recur_helper(int n, std::vector<unsigned long>& memo) {
    if (n == 0 || n == 1) {
        return 1;
    }

    if (memo[n] != 0) {
        return memo[n];
    }

    unsigned long result = 0;
    for (int i = 0; i < n; i++) {
        result += genA_recur_helper(i, memo) * genA_recur_helper(n - 1 - i, memo);
    }

    memo[n] = result;
    return result;
}

unsigned long genA_recur(int n) {
    std::vector<unsigned long> memo(n + 1, 0);
    memo[0] = 1;
    memo[1] = 1;
    genA_recur_helper(n, memo);
    return memo[n];
}

//Iterative 
unsigned long genA_iter(int n) {
    if (n == 0) {
        return 0;
    }

    std::vector<unsigned long> An(n + 1, 0);
    An[0] = 1;
    An[1] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            An[i] += An[j] * An[i - 1 - j];
        }
    }
    return An[n];
}