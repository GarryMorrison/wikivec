#ifndef SETS_H
#define SETS_H

#include <map>
#include <string>
#include <set>
#include <vector>

typedef unsigned long ulong;

std::map<std::string, std::set<ulong> > load_sw_set(const std::string filename, const std::string op);
std::vector<std::pair<float, std::string> > print_wikivec_similarity(const std::map<std::string, std::set<ulong> > &sw_map, const std::string &wikipage, int number_of_results);

#endif
