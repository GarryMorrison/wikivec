#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

typedef unsigned long ulong;

// define some settings:
const std::string op = "wikivec";
const std::string source = "sw/small.sw";
// const std::string source = "sw/30k--wikivec.sw";
// const std::string source = "sw/300k--wikivec.sw";
const bool interactive = true;
// const bool interactive = false;



std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    std::vector<std::string> result;
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        result.push_back(token);
    }
    result.push_back(s.substr(pos_start));
    return result;
}


// assumes a well constructed sw file!
std::map<std::string, std::set<ulong> > load_sw(const std::string filename, const std::string op) {
    std::map<std::string, std::set<ulong> > result;
    std::string op_head = op + " |";
    std::string label;
    std::string tail;
    std::vector<std::string> split_tail;

    std::string line;
    std::ifstream infile;
    infile.open(filename);
    while(std::getline(infile, line)) {
        if (line.rfind(op_head, 0) == 0) {
            line.erase(0, op_head.length());
            size_t break_pos = line.find("> => ");
            label = line.substr(0, break_pos);
            tail = line.substr(break_pos + 5);
            split_tail = split(tail, " + ");

            std::set<ulong> set_tail;
            for (auto const &ket: split_tail) {
                auto hex_ket = ket.substr(1, ket.size() - 2);  // crashes if ket.size() < 2
                std::stringstream ss;
                ulong value;
                ss << std::hex << hex_ket;
                ss >> value;
                set_tail.insert(value);
            }
            result.insert(std::make_pair(label, set_tail));

            std::cout << "line: " << line << std::endl;
            // std::cout << "label: " << label << std::endl;
            // std::cout << "tail: " << tail << std::endl;
        }
    }
    infile.close();
    return result;
}

void print_sw_map(std::map<std::string, std::set<ulong> > &sw_map) {
    std::cout << "sw map: " << std::endl;
    for (auto const & rule: sw_map) {
        std::cout << "wikivec |" << rule.first << "> => |";
        auto it = rule.second.begin();
        std::cout << *it++;
        for (; it != rule.second.end(); it++) {
            std::cout << "> + |";
            std::cout << *it;
        }
        std::cout << ">" << std::endl;
    }
}

std::set<ulong> find_intersection(const std::set<ulong> &one, const std::set<ulong> &two) {
    std::set<ulong> result;
    set_intersection(one.begin(), one.end(), two.begin(), two.end(), std::inserter(result, result.begin()));
    return result;
}

std::set<ulong> find_union(const std::set<ulong> &one, const std::set<ulong> &two) {
    std::set<ulong> result;
    set_union(one.begin(), one.end(), two.begin(), two.end(), std::inserter(result, result.begin()));
    return result;
}

float simm(const std::set<ulong> &one, const std::set<ulong> &two) {
    auto the_union = find_union(one, two);
    auto the_intersection = find_intersection(one, two);
    if (the_union.size() == 0) { return 0.0; }
    return (float)the_intersection.size() / (float)the_union.size();
}


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
    std::cout << "wikipage: " << wikipage << std::endl;
    std::cout << "number of results to show: " << number_of_results << std::endl;


    // load the sw file:
    auto sw_map = load_sw(source, op);

    // test it loads:
    print_sw_map(sw_map);

    // test set intersection:
    std::set<ulong> one, two, the_intersection, the_union;
    one.insert(5);
    one.insert(10);
    one.insert(15);
    one.insert(20);
    two.insert(10);
    two.insert(20);
    two.insert(25);

    the_intersection = find_intersection(one, two);
    for (auto const number: the_intersection) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    the_union = find_union(one, two);
    for (auto const number: the_union) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    std::cout << "simm: " << simm(one, two) << std::endl;

    return 0;
}
