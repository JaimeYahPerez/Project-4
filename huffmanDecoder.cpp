#include "huffmanDecoder.hpp"
#include <algorithm>

HuffmanTree::~HuffmanTree() {
	destroy(root_);
	root_ = nullptr;
}

error_type HuffmanTree::buildFromHeader(const std::vector<std::pair<std::string, std::string>>& header) {

    destroy(root_);
    root_ = nullptr;

    root_ = new TreeNode(0);   // freq not used in decoder
    root_->setKey("");         // internal nodes can have empty key

    for (const auto& [word, code] : header) {
        TreeNode* cur = root_;
        for (char b : code) {
            if (b == '0') {
                if (cur->leftSubtree() == nullptr) {
                    auto* child = new TreeNode(0);
                    child->setKey("");
                    cur->leftSubtree(child);
                }
                cur = cur->leftSubtree();
            }
            else if (b == '1') {
                if (cur->rightSubtree() == nullptr) {
                    auto* child = new TreeNode(0);
                    child->setKey("");
                    cur->rightSubtree(child);
                }
                cur = cur->rightSubtree();
            }
            else {
                // invalid bit in header
                return FAILED_TO_WRITE_FILE;
            }
        }
        // at the end of the code, cur must be a leaf for this word
        cur->setKey(word);
    }

    return NO_ERROR;
}

error_type HuffmanTree::decode(std::istream& codeStream, std::ostream& outStream) const {
    if (!root_) {
        // no tree, but let's allow empty decode -> empty output
        return NO_ERROR;
    }
    if (!codeStream.good()) {
        return UNABLE_TO_OPEN_FILE;
    }
    if (!outStream.good()) {
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;
    }

    const TreeNode* cur = root_;
    char ch;
    while (codeStream.get(ch)) {
        // Just skip newlines in the .code file
        if (ch == '\n' || ch == '\r') {
            continue;
        }
        // unexpected character in .code 
        if (ch != '0' && ch != '1') {
            return FAILED_TO_WRITE_FILE;
        }

        // follow bit
        if (ch == '0') {
            cur = cur->leftSubtree();
        }
        else {
            cur = cur->rightSubtree();
        }

        // we followed a path that doesn't exist
        if (cur == nullptr) {
            return FAILED_TO_WRITE_FILE;
        }

        //is leaf?
        if (cur->leftSubtree() == nullptr && cur->rightSubtree() == nullptr) {
            // this node must have the word from header
            outStream << cur->key() << '\n';
            if (!outStream) { 
                return FAILED_TO_WRITE_FILE; 
            }

            // restart for next word
            cur = root_;
        }
    }

    if (cur != root_) {
        // incomplete code at end of file
        return FAILED_TO_WRITE_FILE;
    }

    return NO_ERROR;
}

void HuffmanTree::destroy(TreeNode* n) noexcept {
    if (!n) { 
        return; 
    }
    destroy(n->leftSubtree());
    destroy(n->rightSubtree());
    delete n;
}

