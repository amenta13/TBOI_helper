#pragma once
#include <string>
#include <vector>

struct TreeNode {
    std::string name;
    std::vector<TreeNode*> children;

    TreeNode(const std::string& name);
};
