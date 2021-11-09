#include <bits//stdc++.h>

using namespace std;


typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

}TreeNode;


// pre mid last
void preSearch(TreeNode *root) {
        if (root != nullptr) {
                printf("%d", root -> val);
                preSearch(root -> left);
                preSearch(root -> right);
        }
}

void midSearch(TreeNode *root) {
        if (root != nullptr) {
                preSearch(root -> left);
                printf("%d", root -> val);
                preSearch(root -> right);
        }
}

void lastSearch(TreeNode *root) {
        if (root != nullptr) {
                preSearch(root -> left);
                preSearch(root -> right);
                printf("%d", root -> val);
        }
}


// Layered Search -> dfs
void dfs(TreeNode *root, vector<vector<int>> &res, int level) {
        if (!root) return;

        if (level == res.size()) {
                res.emplace_back(vector<int>());
        }

        res[level].emplace_back(root -> val);
        dfs(root -> left, res, level + 1);
        dfs(root -> right, res, level + 1);

}
vector<vector<int>> layeredSearchByDFS(TreeNode *root) {
        vector<vector<int>> res;
        if (root == nullptr) return res;
        dfs(root, res, 0);
}


// Layered Search -> bfs

vector<vector<int>> layeredSearchByBFS(TreeNode *root) {
        vector<vector<int>> res;
        if (root == nullptr) return res;
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty()) {
                vector<int> level;
                int len = q.size();
                for (int i = 0; i < len; i++) {
                        TreeNode *tmp = q.front();
                        level.emplace_back(tmp -> val);
                        if (!tmp -> left) q.push(tmp -> left);
                        if (!tmp -> right) q.push(tmp -> right);
                }
                res.emplace_back(level);
        }
        return res;
}

// 左右反转
void invert(TreeNode *root) {
        if (!root) return;
        TreeNode *tmp = root -> left;
        root -> left = root->right;
        root -> right = tmp;

        invert(root -> left);
        invert(root -> right);
}

// 获取最大值

int getMax(TreeNode *root) {
        if (!root) return INT_MAX;
        int left = getMax(root -> left);
        int right = getMax(root -> right);

        return max(root -> val, max(left, right));
}

// 获取最大深度
int getMaxDepth(TreeNode *root) {
        if (!root) return 0;

        int left = getMaxDepth(root -> left);
        int right = getMaxDepth(root -> right);

        return max(left, right) + 1;
}

// 获取最小深度
int getMinDepth(TreeNode *root) {
        if (!root) return 0;

        int left = getMinDepth(root -> left);
        int right = getMinDepth(root -> right);

        if (left == 0) return right + 1; // 如果没有左子树返回右子树
        else if (right == 0) return left + 1;
        else return min(left, right) + 1;
}

// 平衡二叉树
int maxDepth(TreeNode *root) {
        if (!root) return 0;

        int left = maxDepth(root -> left);
        int right = maxDepth(root -> right);

        if (left == -1 || right == -1 || abs(left - right) > 1) return -1;

        return max(left, right) + 1;
}
bool isBalanced(TreeNode *root) {
        return maxDepth(root) != -1;
}

int main() {
        std::cout << "Hello, World!" << std::endl;
        return 0;
}
