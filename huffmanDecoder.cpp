#include "huffmanDecoder.hpp"


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
        TreeNode* curr = root_;
        for (char b : code) {
            if (b == '0') {
                if (curr->leftSubtree() == nullptr) {
                    auto* child = new TreeNode(0);
                    child->setKey("");
                    curr->leftSubtree(child);
                }
                curr = curr->leftSubtree();
            }
            else if (b == '1') {
                if (curr->rightSubtree() == nullptr) {
                    auto* child = new TreeNode(0);
                    child->setKey("");
                    curr->rightSubtree(child);
                }
                curr = curr->rightSubtree();
            }
            else {
                // invalid bit in header
                return FAILED_TO_WRITE_FILE;
            }
        }
        // at the end of the code, curr must be a leaf for this word
        curr->setKey(word);
    }

    return NO_ERROR;
}

error_type HuffmanTree::decode(std::istream& codeStream, std::ostream& outStream) const {
    //No tree present is allowed
    if (!root_) {
        return NO_ERROR;
    }
    if (!codeStream.good()) {
        return UNABLE_TO_OPEN_FILE;
    }
    if (!outStream.good()) {
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;
    }

    const TreeNode* curr = root_;
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
            curr = curr->leftSubtree();
        }
        else {
            curr = curr->rightSubtree();
        }

        // we followed a path that doesn't exist
        if (curr == nullptr) {
            return FAILED_TO_WRITE_FILE;
        }

        // is cur a leaf?
        if (curr->leftSubtree() == nullptr && curr->rightSubtree() == nullptr) {
            // this node must have the word from header
            outStream << curr->key() << '\n';
            if (!outStream) { 
                return FAILED_TO_WRITE_FILE; 
            }

            // restart for next word
            curr = root_;
        }
    }

    // incomplete code at end of file
    if (curr != root_) {
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

