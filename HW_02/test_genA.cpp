#include <iostream>
#include <chrono>
#include <vector>

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

int main() {
    // Change the value of 'n' to the desired input size
    int n = 1000;  // Example: n = 1000

    // Measure the runtime of genA_recur
    auto start_time_recur = std::chrono::high_resolution_clock::now();
    unsigned long result_recur = genA_recur(n);
    auto end_time_recur = std::chrono::high_resolution_clock::now();
    auto duration_recur = std::chrono::duration_cast<std::chrono::microseconds>(end_time_recur - start_time_recur);

    // Measure the runtime of genA_iter
    auto start_time_iter = std::chrono::high_resolution_clock::now();
    unsigned long result_iter = genA_iter(n);
    auto end_time_iter = std::chrono::high_resolution_clock::now();
    auto duration_iter = std::chrono::duration_cast<std::chrono::microseconds>(end_time_iter - start_time_iter);

    // Output the results and durations
    std::cout << "genA_recur Result: " << result_recur << std::endl;
    std::cout << "genA_recur Runtime: " << duration_recur.count() << " microseconds" << std::endl;

    std::cout << "genA_iter Result: " << result_iter << std::endl;
    std::cout << "genA_iter Runtime: " << duration_iter.count() << " microseconds" << std::endl;

    return 0;
}
