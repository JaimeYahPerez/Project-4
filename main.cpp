#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

#include "TreeNode.hpp"
#include "utils.hpp"
#include "huffmanDecoder.hpp"

static error_type readHeaderFile(const std::string& hdrPath, std::vector<std::pair<std::string, std::string>>& out) {
    out.clear();
    std::ifstream in(hdrPath);

    if (!in.is_open()) {
        return UNABLE_TO_OPEN_FILE;
    }

    std::string word;
    std::string code;

    while (in >> word >> code) {
        // safety check: header lines should start with a letter
        if (!word.empty() && (word[0] == '0' || word[0] == '1')) {
            return FAILED_TO_WRITE_FILE;
        }
        out.emplace_back(word, code);
    }
    return NO_ERROR;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << " <filename>\n";
        return 1;
    }

    //record and normalize paths
    std::filesystem::path headerPath(argv[1]);
    std::filesystem::path codePath(argv[2]);
    if (headerPath.parent_path().empty() || codePath.parent_path().empty()) {
        headerPath = std::filesystem::path("input_output") / headerPath.filename();
        codePath = std::filesystem::path("input_output") / codePath.filename();
    }
    
    //build output path
    std::string base = std::filesystem::path(headerPath).stem().string();;
    std::filesystem::path outPath = headerPath.parent_path() / (base + ".tokens_decoded");

    //check paths
    if (auto st = regularFileExistsAndIsAvailable(headerPath.string()); st != NO_ERROR)
        exitOnError(st, headerPath.string());

    if (auto st = regularFileExistsAndIsAvailable(codePath.string()); st != NO_ERROR)
        exitOnError(st, codePath.string());

    if (auto st = canOpenForWriting(outPath.string()); st != NO_ERROR)
        exitOnError(st, outPath.string());

    //read header and create vector of pairs
    std::vector<std::pair<std::string, std::string>> headerPairs;
    if (auto st = readHeaderFile(headerPath.string(), headerPairs); st != NO_ERROR)
        exitOnError(st, headerPath.string());

    // build decoder tree
    HuffmanTree decoder;
    if (auto st = decoder.buildFromHeader(headerPairs); st != NO_ERROR)
        exitOnError(st, headerPath.string());


    // open and check code file and output path
    std::ifstream codeIn(codePath);
    if (!codeIn.is_open())
        exitOnError(UNABLE_TO_OPEN_FILE, codePath.string());

    std::ofstream out(outPath);
    if (!out.is_open())
        exitOnError(UNABLE_TO_OPEN_FILE_FOR_WRITING, outPath.string());

    //open and decode incrementally
    if (auto st = decoder.decode(codeIn, out); st != NO_ERROR)
        exitOnError(st, outPath.string());

    return 0;
}