#pragma once
#ifndef HUFFMANTREE_HPP
#define HUFFMANTREE_HPP

#include <vector>
#include <string>
#include <iostream>

#include "utils.hpp"
#include "TreeNode.hpp"

class HuffmanTree {
public:
    HuffmanTree() = default;
    ~HuffmanTree();

    // build from header (word,code) pairs
    error_type buildFromHeader(const std::vector<std::pair<std::string, std::string>>& header);

    // decode 0/1 stream (with newlines) to words, one per line
    error_type decode(std::istream& codeStream, std::ostream& outStream) const;

private:
    TreeNode* root_ = nullptr;

    static void destroy(TreeNode* n) noexcept;
};

#endif