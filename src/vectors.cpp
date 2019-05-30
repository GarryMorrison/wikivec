#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <iomanip>
#include "vectors.h"



std::map<std::string, std::vector<ulong> > load_sw_vec(const std::string filename, const std::string op, size_t min_learn_rule_size) {
    std::map<std::string, std::vector<ulong> > result;
    std::string op_head = op + " |";
    size_t op_head_length = op_head.length();

    std::string line;
    std::ifstream infile;
    infile.open(filename);
    if (!infile.is_open()) {
        std::cerr << "Failed to load file: " << filename << std::endl;
        std::_Exit(0);
    }
    while(std::getline(infile, line)) {
        if (line.rfind(op_head, 0) == 0) {
            size_t break_pos = line.find("> => ");
            std::string label = line.substr(op_head_length, break_pos - op_head_length);
            std::string tail = line.substr(break_pos + 6, line.size() - break_pos - 7);

            std::vector<ulong> vec_tail;
            size_t pos_start = 0, pos_end, delim_len = 5;
            while ((pos_end = tail.find("> + |", pos_start)) != std::string::npos) {
                std::string token = tail.substr(pos_start, pos_end - pos_start);
                pos_start = pos_end + delim_len;
                ulong value = std::stoul(token, nullptr, 16);
                vec_tail.push_back(value);
            }
            std::string token = tail.substr(pos_start);
            ulong value = std::stoul(token, nullptr, 16);
            vec_tail.push_back(value);

            if (vec_tail.size() >= min_learn_rule_size) {
                result.insert(std::make_pair(label, vec_tail));
            }

            // std::cout << "line: " << line << std::endl;
            // std::cout << "label: " << label << std::endl;
            // std::cout << "tail: " << tail << std::endl;
        }
    }
    infile.close();
    return result;
}

void print_sw_map(std::map<std::string, std::vector<ulong> > &sw_map) {
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



// code for intersection from here:
// https://leetcode.com/problems/intersection-of-two-arrays/discuss/266901/C%2B%2B-beats-100.
ulong first_find_intersection_size(const std::vector<ulong> &A, const std::vector<ulong> &B) {
        std::vector<ulong> result;
        std::vector<ulong> one = A, two = B;
        std::sort(one.begin(), one.end());
        std::sort(two.begin(), two.end());
        int l = 0, r = 0;
        while(l < one.size() && r < one.size()){
            ulong left = one[l], right = two[r];
            if(left == right){
                result.push_back(right);
                while(l < one.size() && one[l] == left )l++;
                while(r < two.size() && two[r] == right )r++;
                continue;
            }
            if(left < right){
            while(l < one.size() && one[l] == left )l++;
            }else while( r < two.size()  && two[r] == right )r++;
        }
        return result.size();
}

ulong second_find_intersection_size(const std::vector<ulong> &one, const std::vector<ulong> &two) {
    ulong result = 0;
    if (one.empty() || two.empty()) {
        return 0;
    }
    std::unordered_set<ulong> set{one.cbegin(), one.cend()};
    for (auto n: two) {
        if (set.erase(n) > 0) {
            result++;
        }
    }
    return result;
}

ulong find_intersection_size(const std::vector<ulong> &one, const std::vector<ulong> &two) {
    // std::unordered_set<ulong> us(std::begin(one), std::end(one));
    std::set<ulong> us(std::begin(one), std::end(one));
    ulong result = std::count_if(std::begin(two), std::end(two), [&](ulong n) {return us.find(n) != std::end(us);});
    return result;
}

ulong find_union_size(const std::vector<ulong> &one, const std::vector<ulong> &two) {
    // std::unordered_set<ulong> us(std::begin(one), std::end(one));
    std::set<ulong> us(std::begin(one), std::end(one));
    for (auto const n: two) {
        us.insert(n);
    }
    return us.size();
}

ulong second_find_union_size(const std::vector<ulong> &one, const std::vector<ulong> &two) {
    std::set<ulong> result;
    set_union(one.begin(), one.end(), two.begin(), two.end(), std::inserter(result, result.begin()));
    return result.size();
}


float simm(const std::vector<ulong> &one, const std::vector<ulong> &two) {
    ulong union_size = find_union_size(one, two);
    ulong intersection_size = find_intersection_size(one, two);
    if (union_size == 0) { return 0.0; }
    return (float)intersection_size / (float)union_size;
}

std::vector<std::pair<float, std::string> > pattern_recognition(const std::map<std::string, std::vector<ulong> > &sw_map, const std::vector<ulong> &pattern, ulong number_of_results) {
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

std::vector<std::pair<float, std::string> > print_wikivec_similarity(const std::map<std::string, std::vector<ulong> > &sw_map, const std::string &wikipage, int number_of_results) {
    // test wikipage is in sw_map:
    if (sw_map.find(wikipage) == sw_map.end()) {
        std::cout << wikipage << " not in dictionary" << std::endl;
        std::vector<std::pair<float, std::string> > empty;
        return empty;
    }

    // print details header:
    std::cout << "----------------" << std::endl;
    std::cout << "vector version" << std::endl;
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

    // print out a table of results:
    // std::cout << "result size: " << result.size() << std::endl;
    int max_width = 0;
    for (const auto x: result) {
        max_width = std::max(max_width, (int)x.second.size());
    }
    int k = 1;
    for (const auto x: result) {
        std::cout << std::left << std::setw(4) << k << std::left << std::setw(max_width + 1) << x.second << " " << (int)(10000.0 * x.first)/100.0 << std::endl;
        k++;
    }
    std::cout << std::endl;
    return result;
}


