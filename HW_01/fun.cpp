#include "fun.h"
#include <iostream>
#include <map>
#include <utility> 

// Define a map to store the already computed results.
std::map<std::pair<unsigned int, unsigned int>, unsigned int> memo;

// Helper function to check if can find computed result and get the result 
unsigned int findMemoResult(unsigned int x, unsigned int y) {
    // Check if the result is already computed.
    // use std::pair to represent the key.
    auto memo_key = std::make_pair(x, y);
    auto it = memo.find(memo_key);
    // If the result is already computed, return it.
    return (it != memo.end()) ? it->second:0;
}

unsigned int fun(unsigned int x, unsigned int y) {
    // Check if the result is already computed.
    unsigned int memoResult = findMemoResult(x, y);
    if (memoResult != 0) {
        // Return the cached result.
        return memoResult;
    }

    // Compute the result under specific condition
    unsigned int result;
    if (x == 0 && y == 0) {
        result = 1;
    } else if (x == 0) {
        result = y + 1;
    } else if (y == 0) {
        result = fun(x - 1, 1);
    } else {
        result = fun(x - 1, fun(x - 1, y - 1));
    }

    // Store the result before returning it.
    memo[std::make_pair(x, y)] = result;
    // Return the result.
    return result;
}



