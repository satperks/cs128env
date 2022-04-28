#include "solution.hpp"

#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

Solution::Solution(
    const std::vector<std::pair<std::string, std::string>>& prerequisites) {
  // std::cout << "both class exsit" << std::endl;
  for (size_t i = 0; i < prerequisites.size(); i++) {
    // std::cout << "WHAT THE HELL HAPPEN" << std::endl;
    std::string pre = prerequisites.at(i).first;
    std::string post = prerequisites.at(i).second;
    if (adj_.find(pre) == adj_.end())
      adj_.insert(std::pair<std::string, std::list<std::string>>(
          pre, std::list<std::string>()));
    if (adj_.find(post) == adj_.end())
      adj_.insert(std::pair<std::string, std::list<std::string>>(
          post, std::list<std::string>()));
    adj_.find(pre)->second.push_back(post);
  }
}

int Solution::Solve(const std::string& start, const std::string& dest) {
  if (VertexInGraph(start) && VertexInGraph(dest)) {
    // std::cout << "both class exsit" << std::endl;
    std::queue<std::string> que;
    std::set<std::string> set;
    std::vector<std::string> vec;
    que.push(start);
    set.insert(start);

    std::map<std::string, int> num;
    for (auto const& item : adj_) {
      num.insert(std::pair<std::string, int>(item.first, 0));
    }

    while (!que.empty()) {
      std::string current = que.front();
      vec.push_back(current);
      que.pop();

      std::list<std::string> list = GetAdjacencyList(current);
      // std::cout << "check adjacency for " << current << std::endl;
      for (const std::string& item : list) {
        if (set.find(item) == set.end()) {
          // std::cout << item << " haven't been visit, push to queue"
          //           << std::endl;
          num.find(item)->second = num.find(current)->second + 1;
          que.push(item);
          set.insert(item);
          vec.push_back(item);
          if (item == dest) return num.find(dest)->second;
        }
      }
    }
  }

  return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Provide function definitions (uncomment to use!)                          //
///////////////////////////////////////////////////////////////////////////////

void Solution::AddVertex(const std::string& vertex) {
  if (VertexInGraph(vertex))
    throw std::runtime_error("vertex already in graph.");
  adj_.insert(std::pair<std::string, std::list<std::string>>(
      vertex, std::list<std::string>()));
}

std::list<std::string>& Solution::GetAdjacencyList(const std::string& vertex) {
  return adj_.find(vertex)->second;
}

bool Solution::VertexInGraph(const std::string vertex) {
  if (adj_.find(vertex) != adj_.end())
    return true;
  else
    return false;
}

std::ostream& operator<<(std::ostream& os, const Solution& sol) {
  os << "Contents:" << std::endl;

  for (const auto& pair : sol.adj_) {
    os << "  " << pair.first << ": [ ";

    for (const auto& list_entry : pair.second) {
      os << list_entry << " ";
    }

    os << "]" << std::endl;
  }

  return os;
}