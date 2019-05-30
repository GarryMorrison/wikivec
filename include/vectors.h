#ifndef VECTORS_H
#define VECTORS_H

#include <map>
#include <string>
#include <vector>

typedef unsigned long ulong;

std::map<std::string, std::vector<ulong> > load_sw_vec(const std::string filename, const std::string op);
ulong find_intersection_size(const std::vector<ulong> &one, const std::vector<ulong> &two);
ulong find_union_size(const std::vector<ulong> &one, const std::vector<ulong> &two);
std::vector<std::pair<float, std::string> > print_wikivec_similarity(const std::map<std::string, std::vector<ulong> > &sw_map, const std::string &wikipage, int number_of_results);

#endif
