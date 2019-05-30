#include <iostream>
#include <string>
#include <sstream>
#include "sets.h"
#include "vectors.h"


// define some settings:
const std::string op = "wikivec";
// const std::string source = "sw/small.sw";
const std::string source = "sw/30k--wikivec.sw";
// const std::string source = "sw/300k--wikivec.sw";
// const bool interactive = true;
const bool interactive = false;


int main(int argc, char* argv[]) {
    // first process our command line arguments:
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " wikipage-title [number-of-results-to-show]" << std::endl;
        return 1;
    }
    std::string wikipage = argv[1];
    int number_of_results = 30;
    if (argc == 3) {
        std::istringstream iss(argv[2]);
        if (!(iss >> number_of_results)) {
            std::cerr << "Usage: " << argv[0] << " wikipage-title [number-of-results-to-show]" << std::endl;
            return 1;
        }
    }
    // std::cout << "wikipage: " << wikipage << std::endl;
    // std::cout << "number of results to show: " << number_of_results << std::endl;


    // load the sw file, choosing set or vec version:
    auto sw_map = load_sw_set(source, op);  // set version
    // auto sw_map = load_sw_vec(source, op);  // vector version

    // test it loads:
    // print_sw_map(sw_map);
    // return 0;


    // find and print out wikivec similarity:
    auto result = print_wikivec_similarity(sw_map, wikipage, number_of_results);

    // if interactive then prompt for more wikipages:
    if (interactive) {
        while(true) {
            std::string input;
            std::cout << "Enter table row number, or wikipage: ";
            std::getline(std::cin, input);

            // check for empty input:
            if (input.size() == 0) { continue; }

            // exit the agent:
            if (input == "q") { return 0; }

            // get next page to run similarity on:
            try {
                int line = std::stoi(input, nullptr, 10) - 1;
                if (line < 0 || line >= number_of_results) {
                    line = 0;
                }
                wikipage = result[line].second;
            }
            catch ( std::invalid_argument ) {
                wikipage = input;
            }

            // find and print out wikivec similarity:
            result = print_wikivec_similarity(sw_map, wikipage, number_of_results);
        }
    }

    return 0;
}
