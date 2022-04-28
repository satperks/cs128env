#include "illini_book.hpp"

#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "utilities.hpp"

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::ifstream ifs_person{people_fpath};
  std::ifstream ifs_relation{relations_fpath};
  // if (ifs_person.is_open()) std::cout << "open file successfully" <<
  // std::endl;

  for (std::string line; std::getline(ifs_person, line); line = "") {
    adj_.insert(std::pair<int, std::list<std::pair<int, std::string>>>(
        std::stoi(line), std::list<std::pair<int, std::string>>()));
    // std::cout << "add " << std::stoi(line) << " to the map" << std::endl;
  }
  for (std::string line; std::getline(ifs_relation, line); line = "") {
    std::vector<std::string> each_line = utilities::Split(line, ',');
    int p1 = std::stoi(each_line.at(0));
    int p2 = std::stoi(each_line.at(1));
    std::string re = each_line.at(2);
    adj_.find(p1)->second.push_back(std::make_pair(p2, re));
    adj_.find(p2)->second.push_back(std::make_pair(p1, re));
    res_.insert(re);
    // std::cout << p1 << " has relationship [" << re << "] with " << p2
    //           << std::endl;
  }
}

IlliniBook::~IlliniBook() {
  adj_ = std::map<int, std::list<std::pair<int, std::string>>>();
  res_ = std::set<std::string>();
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  std::queue<int> q;
  std::set<int> s;
  q.push(uin_1);
  s.insert(uin_1);

  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    std::list<std::pair<int, std::string>> conncect_to =
        adj_.find(curr)->second;
    for (auto const& each : conncect_to) {
      if (each.first == uin_2) return true;
      if (s.find(each.first) == s.end()) {
        q.push(each.first);
        s.insert(each.first);
      }
    }
  }

  return false;
}

bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  if (res_.find(relationship) == res_.end()) return false;
  std::queue<int> q;
  std::set<int> s;
  q.push(uin_1);
  s.insert(uin_1);

  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    std::list<std::pair<int, std::string>> conncect_to =
        adj_.find(curr)->second;
    for (auto const& each : conncect_to) {
      if (s.find(each.first) == s.end() && each.second == relationship) {
        if (each.first == uin_2) return true;
        q.push(each.first);
        s.insert(each.first);
      }
    }
  }

  return false;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  std::queue<int> q;
  std::set<int> s;
  q.push(uin_1);
  s.insert(uin_1);

  std::map<int, int> num;
  for (auto const& item : adj_) {
    num.insert(std::pair<int, int>(item.first, 0));
  }

  while (!q.empty()) {
    int curr = q.front();
    q.pop();

    std::list<std::pair<int, std::string>> conncect_to =
        adj_.find(curr)->second;
    for (auto const& each : conncect_to) {
      if (s.find(each.first) == s.end()) {
        num.find(each.first)->second = num.find(curr)->second + 1;
        q.push(each.first);
        s.insert(each.first);
        if (each.first == uin_2) return num.find(uin_2)->second;
      }
    }
  }

  return -1;
}

int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  if (res_.find(relationship) == res_.end()) return -1;
  std::queue<int> q;
  std::set<int> s;
  q.push(uin_1);
  s.insert(uin_1);

  std::map<int, int> num;
  for (auto const& item : adj_) {
    num.insert(std::pair<int, int>(item.first, 0));
  }

  while (!q.empty()) {
    int curr = q.front();
    q.pop();

    std::list<std::pair<int, std::string>> conncect_to =
        adj_.find(curr)->second;
    for (auto const& each : conncect_to) {
      if (s.find(each.first) == s.end() && each.second == relationship) {
        num.find(each.first)->second = num.find(curr)->second + 1;
        q.push(each.first);
        s.insert(each.first);
        if (each.first == uin_2) return num.find(uin_2)->second;
      }
    }
  }

  return -1;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::vector<int> step;
  std::queue<int> q;
  std::set<int> s;
  q.push(uin);
  s.insert(uin);

  std::map<int, int> num;
  for (auto const& item : adj_) {
    num.insert(std::pair<int, int>(item.first, 0));
  }

  while (!q.empty()) {
    int curr = q.front();
    q.pop();

    std::list<std::pair<int, std::string>> conncect_to =
        adj_.find(curr)->second;
    for (auto const& each : conncect_to) {
      if (s.find(each.first) == s.end()) {
        num.find(each.first)->second = num.find(curr)->second + 1;
        int d = num.find(each.first)->second;
        if (d == n) step.push_back(each.first);
        if (d > n) return step;
        q.push(each.first);
        s.insert(each.first);
      }
    }
  }

  return step;
}

size_t IlliniBook::CountGroups() const {
  size_t count = 0;
  std::set<int> s;

  for (auto const& each_p : adj_) {
    if (s.find(each_p.first) == s.end()) {
      std::queue<int> q;
      q.push(each_p.first);
      s.insert(each_p.first);

      while (!q.empty()) {
        int curr = q.front();
        q.pop();
        std::list<std::pair<int, std::string>> conncect_to =
            adj_.find(curr)->second;
        for (auto const& each : conncect_to) {
          if (s.find(each.first) == s.end()) {
            q.push(each.first);
            s.insert(each.first);
          }
        }
      }
      count++;
    }
  }

  return count;
}

size_t IlliniBook::CountGroups(const std::string& relationship) const {
  if (res_.find(relationship) == res_.end()) return adj_.size();
  size_t count = 0;
  std::set<int> s;

  for (auto const& each_p : adj_) {
    if (s.find(each_p.first) == s.end()) {
      std::queue<int> q;
      q.push(each_p.first);
      s.insert(each_p.first);

      while (!q.empty()) {
        int curr = q.front();
        q.pop();
        std::list<std::pair<int, std::string>> conncect_to =
            adj_.find(curr)->second;
        for (auto const& each : conncect_to) {
          if (s.find(each.first) == s.end() && each.second == relationship) {
            q.push(each.first);
            s.insert(each.first);
          }
        }
      }
      count++;
    }
  }

  return count;
}

size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  size_t count = 0;
  std::set<int> s;

  for (auto const& each_p : adj_) {
    if (s.find(each_p.first) == s.end()) {
      std::queue<int> q;
      q.push(each_p.first);
      s.insert(each_p.first);

      while (!q.empty()) {
        int curr = q.front();
        q.pop();
        std::list<std::pair<int, std::string>> conncect_to =
            adj_.find(curr)->second;
        for (auto const& each : conncect_to) {
          if (s.find(each.first) == s.end()) {
            for (const std::string& rela : relationships) {
              if (each.second == rela) {
                q.push(each.first);
                s.insert(each.first);
                break;
              }
            }
          }
        }
      }
      count++;
    }
  }

  return count;
}
