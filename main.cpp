#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "TreeNode.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << " <filename>\n";
        return 1;
    }

    std::filesystem::path headerPath = argv[1];
    std::filesystem::path codePath = argv[2];
    if (headerPath.parent_path().empty() || codePath.parent_path().empty()) {
        headerPath = std::filesystem::path("input_output") / headerPath.filename();
        codePath = std::filesystem::path("input_output") / codePath.filename();
    }


}