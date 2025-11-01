#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <string>
class TreeNode {
public:
    TreeNode( int n ): left(nullptr), right(nullptr), count(n) {}
    ~TreeNode() {
        leftSubtree(nullptr);
        rightSubtree(nullptr);
    }

    TreeNode *leftSubtree() { return left; }
    TreeNode *rightSubtree() { return right; }

    //Const overloads
    const TreeNode* leftSubtree() const { return left; }
    const TreeNode* rightSubtree() const{ return right; }

    void leftSubtree( TreeNode *newLeft ) { left = newLeft; }
    void rightSubtree(TreeNode *newRight) { right = newRight; }

    int& value() { return count; }
    const int& value() const { return count; }


    const std::string& key() const { return word; }
    void setKey(const std::string& w) { word = w; }

private:
    TreeNode *left, *right;
    int count;
    std::string word;
};
#endif
