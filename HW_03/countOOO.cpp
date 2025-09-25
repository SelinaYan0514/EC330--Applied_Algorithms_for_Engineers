#include "countOOO.h"
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Helper function to perform merge and count out-of-order pairs
int mergeAndCount(vector<int>& arr, int start, int mid, int end) {
    int count = 0;
    int len1 = mid - start + 1;
    int len2 = end - mid;

    vector<int> leftArr(len1), rightArr(len2);

    for (int i = 0; i < len1; i++)
        leftArr[i] = arr[start + i];
    for (int j = 0; j < len2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = start;

    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            count += (len1 - i); // Counting inversions here
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < len2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    return count;
}

// Modified mergeSort function to include counting of out-of-order pairs
int mergeSortAndCount(vector<int>& arr, int start, int end) {
    int count = 0;
    if (start < end) {
        int mid = start + (end - start) / 2;

        count += mergeSortAndCount(arr, start, mid);
        count += mergeSortAndCount(arr, mid + 1, end);

        count += mergeAndCount(arr, start, mid, end);
    }
    return count;
}

// countOOO function adapted to the new merge sort structure
int countOOO(vector<string> rankedListA, vector<string> rankedListB) {
    unordered_map<string, int> positionMap;
    for (int i = 0; i < rankedListB.size(); i++) {
        positionMap[rankedListB[i]] = i;
    }

    vector<int> arr(rankedListA.size());
    for (int i = 0; i < rankedListA.size(); i++) {
        arr[i] = positionMap[rankedListA[i]];
    }

    return mergeSortAndCount(arr, 0, arr.size() - 1);
}
