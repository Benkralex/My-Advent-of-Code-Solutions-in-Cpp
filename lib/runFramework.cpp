#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <functional>

using std::vector, std::string;

class RunFramework {
private:
    vector<string> examplePaths;
    vector<int> exampleOutputs;
    string inputPath;
    std::function<int(string, bool)> func;
    bool debug;
public:
    RunFramework(
        const vector<string> examplePaths_, 
        const vector<int> exampleOutputs_, 
        const string inputPath_, 
        std::function<int(string, bool)> func_,
        bool debug_ = false
    )
    : examplePaths(examplePaths_), exampleOutputs(exampleOutputs_), inputPath(inputPath_), func(func_), debug(debug_) {}

    bool runExample(const int index) {
        std::cout << "Running example from: " << examplePaths[index] << std::endl;
        long start = now();
        int result = func(examplePaths[index], debug);
        long end = now();
        if (result == exampleOutputs[index]) {
            std::cout << "Example " << index << " passed. Output: " << result << ". Time taken: " << (end - start) << " ms\n";
            return true;
        } else {
            std::cout << "Example " << index << " failed. Expected: " << exampleOutputs[index] << ", Got: " << result << ". Time taken: " << (end - start) << " ms\n";
            return false;
        }
    }

    void runAllExamples() {
        int notPassed = 0;
        for (size_t i = 0; i < examplePaths.size(); ++i) {
            if (!runExample(i)) {
                notPassed++;
            }
            std::cout << "-------------------------\n";
        }
        if (notPassed == 0) {
            std::cout << "All examples passed!\n";
        } else {
            std::cout << notPassed << " example(s) failed.\n";
        }
    }

    void runInput() {
        std::cout << "Running input from: " << inputPath << std::endl;
        long start = now();
        int result = func(inputPath, debug);
        long end = now();
        std::cout << "Output: " << result << ". Time taken: " << (end - start) << " ms\n";
    }

    long now() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    };
};