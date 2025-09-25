#include "BST.h"

// helper function for in-order traversal to find the k-th largest element after x
void inorderSuccessor(Node* node, int x, vector<int>& keys, int k) {
    if (node == nullptr || keys.size() >= k) {
        return;
    }

    // traverse left subtree
    inorderSuccessor(node->left, x, keys, k);

    // check the node if it is greater than x
    if (node->key > x) {
        keys.push_back(node->key);
        // If we've found enough elements, return early
        if (keys.size() >= k) {
            return;
        }
    }

    // traverse right subtree
    inorderSuccessor(node->right, x, keys, k);
}

// this is the function that you need to implement */
// function to find the k-th largest key after x
int BST::nextKLargest(int x, int k) {
    vector<int> keys; //initialize an empty vector to store keys which are greater than 'x'
    inorderSuccessor(root, x, keys, k); //call "inorderSuccessor" starting with the root of the BST to fill keys
    
    if (keys.size() < k) {
        // If there are not enough keys greater than x
        if (keys.empty()) 
            return -1; // 1. empty: return -1; 
        
        else return keys.back(); // Otherwise, return the largest key
    }
    return keys[k - 1]; //if there are at least k keys in vector, simply return k-th elements we need, [k-1] in index
}

/*int main()
{
    // Create a BST
    vector<int> nums = {5, 4, 3, 1, 7, 6, 9};
    BST bst(nums);

    // Print the BST
    cout << "Binary Search Tree:" << endl;
    cout << bst.print() << endl;

    // Test cases
    vector<pair<int, int>> testCases = {
        {3, 4},
        {6, 4},
        {2, 4},
        {8, 2},
        {0, 10}
    };

    // Run the test cases
    for (const auto& test : testCases)
    {
        int x = test.first;
        int k = test.second;
        int result = bst.nextKLargest(x, k);

        cout << "nextKLargest(" << x << ", " << k << ") = " << result << endl;
    }

    return 0;
}
*/