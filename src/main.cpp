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
// const std::string source = "sw/small.sw";
const std::string source = "sw/30k--wikivec.sw";
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

std::map<std::string, std::set<ulong> > load_sw(const std::string filename, const std::string op) {
    std::map<std::string, std::set<ulong> > result;
    std::string op_head = op + " |";
    size_t op_head_length = op_head.length();

    std::string line;
    std::ifstream infile;
    infile.open(filename);
    while(std::getline(infile, line)) {
        if (line.rfind(op_head, 0) == 0) {
            size_t break_pos = line.find("> => ");
            std::string label = line.substr(op_head_length, break_pos - op_head_length);
            std::string tail = line.substr(break_pos + 6, line.size() - break_pos - 7);

            std::set<ulong> set_tail;
            size_t pos_start = 0, pos_end, delim_len = 5;
            while ((pos_end = tail.find("> + |", pos_start)) != std::string::npos) {
                std::string token = tail.substr(pos_start, pos_end - pos_start);
                pos_start = pos_end + delim_len;
                ulong value = std::stoul(token, nullptr, 16);
                set_tail.insert(value);
            }
            std::string token = tail.substr(pos_start);
            ulong value = std::stoul(token, nullptr, 16);
            set_tail.insert(value);

            result.insert(std::make_pair(label, set_tail));

            // std::cout << "line: " << line << std::endl;
            // std::cout << "label: " << label << std::endl;
            // std::cout << "tail: " << tail << std::endl;
        }
    }
    infile.close();
    return result;
}

// assumes a well constructed sw file!
std::map<std::string, std::set<ulong> > first_load_sw(const std::string filename, const std::string op) {
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
            // line.erase(0, op_head.length());
            size_t break_pos = line.find("> => ");
            // label = line.substr(0, break_pos);
            label = line.substr(op_head.length(), break_pos);
            tail = line.substr(break_pos + 5);
            // split_tail = split(tail, " + ");
            tail = tail.substr(1, tail.size() - 2);
            split_tail = split(tail, "> + |");

            std::set<ulong> set_tail;
            for (auto const &ket: split_tail) {
                // auto hex_ket = ket.substr(1, ket.size() - 2);  // crashes if ket.size() < 2
                std::stringstream ss;
                ulong value;
                // ss << std::hex << hex_ket;
                ss << std::hex << ket;
                ss >> value;
                set_tail.insert(value);
            }
            result.insert(std::make_pair(label, set_tail));

            // std::cout << "line: " << line << std::endl;
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

ulong find_intersection_size(const std::set<ulong> &one, const std::set<ulong> &two) {
    std::set<ulong> result;
    set_intersection(one.begin(), one.end(), two.begin(), two.end(), std::inserter(result, result.begin()));
    return result.size();
}

ulong find_union_size(const std::set<ulong> &one, const std::set<ulong> &two) {
    std::set<ulong> result;
    set_union(one.begin(), one.end(), two.begin(), two.end(), std::inserter(result, result.begin()));
    return result.size();
}

float simm(const std::set<ulong> &one, const std::set<ulong> &two) {
    ulong union_size = find_union_size(one, two);
    ulong intersection_size = find_intersection_size(one, two);
    if (union_size == 0) { return 0.0; }
    return (float)intersection_size / (float)union_size;
}

std::vector<std::pair<float, std::string> > pattern_recognition(const std::map<std::string, std::set<ulong> > &sw_map, const std::set<ulong> &pattern, ulong number_of_results) {
    std::vector<std::pair<float, std::string> > result;
    for (auto const & pair: sw_map) {
        float value = simm(pattern, pair.second);
        if (value > 0) {
            result.push_back(std::make_pair(value, pair.first));
        }
    }    
    std::sort(result.rbegin(), result.rend());
    result.resize(number_of_results);
    return result;
}

void print_wikivec_similarity(const std::map<std::string, std::set<ulong> > &sw_map, const std::string &wikipage, int number_of_results) {
    // test wikipage is in sw_map:
    if (sw_map.find(wikipage) == sw_map.end()) {
        std::cout << wikipage << " not in dictionary" << std::endl;
        return;
    }

    // print details header:
    std::cout << "----------------" << std::endl;
    auto pattern = sw_map.at(wikipage);
    std::cout << "wikipage: " << wikipage << std::endl;
    std::cout << "pattern: {";
    for (const auto ket: pattern) {
        std::cout << ket << ", ";
    }
    std::cout << "}" << std::endl;
    std::cout << "pattern length: " << pattern.size() << std::endl;
    std::cout << "----------------" << std::endl;

    // find matching patterns:
    auto result = pattern_recognition(sw_map, pattern, number_of_results);
    std::cout << "result size: " << result.size() << std::endl;
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
    // print_sw_map(sw_map);
    // return 0;

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


    // test sorting of results:
    std::vector<std::pair<float, std::string>> vec;
    vec = {{2.5, "e"}, {1.7, "d"}, {3, "c"}, {9, "b"}, {0.1, "a"}};
    std::sort(vec.rbegin(), vec.rend());
    for (auto x: vec) {
        std::cout << x.first << " " << x.second << std::endl;
    }

    // 
    print_wikivec_similarity(sw_map, wikipage, number_of_results);

    return 0;
}
