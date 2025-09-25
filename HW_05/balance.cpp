#include "node.h"
#include <cmath>
#include<iostream>
using namespace std;

//hint: this example is exactly the case of AVL tree, weight = height, isWeightBalanced = "binary factor <= k"

//your helper methods here to calculate the weight 
int calWeight(node* root) {
    if (root == NULL) return 0; // Base case: root is empty, nothing here 
    // Recursive case: both left and right subtrees
    return 1 + calWeight(root->left) + calWeight(root->right);
}



bool isWeightBalanced(node* root, int k) {
    //your implementation here 
    if (root == NULL) return true; //root is NULL, left-right = 0-0 

    if(abs(calWeight(root->left) - calWeight(root->right)) <= k) //check current node first: binary factor = height(left) - height(right) <= k
        {return isWeightBalanced(root->left,k) && isWeightBalanced(root->right,k);} //recursively check every node in subtree of the node
        else return false; //if current node fails, there is no need to check the subtree, e.g. isWeightBalanced(node1, 0), binary factor of 1 is 1 > 0
}



/*int main() {
    // Construct the binary tree from the example
    //       1
    //      / \
    //     2   3
    //    /   / \
    //   4   5   6
    //  /
    // 7

    // create 7 nodes
    node* node1 = new node(1);
    node* node2 = new node(2);
    node* node3 = new node(3);
    node* node4 = new node(4);
    node* node5 = new node(5);
    node* node6 = new node(6);
    node* node7 = new node(7);

    // assign relation between nodes
    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node3->left = node5;
    node3->right = node6;
    node4->left = node7;

    // Test the function with the provided examples
    cout << "isWeightBalanced(node1, 0) = " << isWeightBalanced(node1, 0) << endl;
    cout << "isWeightBalanced(node2, 1) = " << isWeightBalanced(node2, 1) << endl;
    cout << "isWeightBalanced(node3, 0) = " << isWeightBalanced(node3, 0) << endl;
    cout << "isWeightBalanced(node4, 1) = " << isWeightBalanced(node4, 1) << endl;

    // Clean up
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
    delete node6;
    delete node7;

    return 0;
}
*/
