#include "heap_search.h"
#include <stdexcept> // Needed for std::out_of_range

template <typename T, typename Compare>
T MinHeap<T, Compare>::get_kth_smallest(int k) {
    if (k > size)
        throw std::out_of_range("The heap contains less than k elements");

    // Lambda for comparing two elements based on indices
    auto indexComparator = [this](int leftInd, int rightInd) {
        return compare(arr[leftInd], arr[rightInd]);
    };

    // Initialize a new heap for the indices
     MinHeap<int, std::function<bool(int, int)>> H(size, indexComparator);
    H.insert(0); // Start at the root element

    T kthSmallest;
    int kthSmallestInd;
  
    for (size_t i = 0; i < k; i++) {
        kthSmallestInd = H.extract_min();
        kthSmallest = arr[kthSmallestInd];

        int leftInd = left_child(kthSmallestInd);
        int rightInd = right_child(kthSmallestInd);

        if (leftInd < size) {
            H.insert(leftInd);
        }
        if (rightInd < size) {
            H.insert(rightInd);
        }
    }
    return kthSmallest;
}


/*int main() {
    // heap with integer elements
    std::vector<int> v1 = {3, 4, 1, 7, 5, 2};
    MinHeap<int> h1(v1, 8);
    std::cout << "heap<int>: ";
    for (int i=0;i<h1.get_size();i++) {
        std::cout << h1.get_array()[i] << " ";
    }
    std::cout << std::endl;
    
    // get the kth smallest element
    for (int k = 1; k <= h1.get_size(); k++)
    {
        int result = h1.get_kth_smallest(k);
        std::cout << k << " smallest element: " << result << std::endl;
    }

    // heap with integer pairs as elements
    using PairType = std::pair<int, int>;
    std::vector<PairType> v2 = {{3, 0}, {4, 1}, {5, 2}, {1, 3}};
    auto compareFirst = [](const PairType& a, const PairType& b) {
        return a.second < b.second;
    };
    MinHeap<PairType, std::function<bool(const PairType&, const PairType&)>> h2(v2, 8, compareFirst);
    std::cout << "heap<pair<int, int>>: ";
    for (int i=0;i<h2.get_size();i++) {
        PairType* h2_arr = h2.get_array();
        std::cout << "{" << h2_arr[i].first << "," << h2_arr[i].second << "} ";
    }
    std::cout << std::endl;

    // get the kth smallest element
    for (int k = 1; k <= h2.get_size(); k++)
    {
        PairType result = h2.get_kth_smallest(k);
        std::cout << k << " smallest element: "
                  << "{" << result.first << "," << result.second << "}" << std::endl;
    }

    return 0;
}
*/
