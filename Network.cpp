#include "Network.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

Network::Network() { users_ = std::vector<User *>(); }

void Network::add_user(User *inp) {
  for (int i = 0; i < users_.size(); i++)
    if (users_[i] == inp)
      return;

  users_.push_back(inp);
}

int Network::add_connection(std::string s1, std::string s2) {
  int indx1 = -1, indx2 = -1;
  for (int i = 0; i < users_.size(); i++) {
    if (users_[i]->name() == s1)
      indx1 = i;
    if (users_[i]->name() == s2)
      indx2 = i;
  }
  if (indx1 == -1 || indx2 == -1 || indx1 == indx2)
    return -1;
  users_[indx1]->add_friend(users_[indx2]->id());
  users_[indx2]->add_friend(users_[indx1]->id());
  return 0;
}

int Network::remove_connection(std::string s1, std::string s2) {
  int indx1 = -1, indx2 = -1;
  for (int i = 0; i < users_.size(); i++) {
    if (users_[i]->name() == s1)
      indx1 = i;
    if (users_[i]->name() == s2)
      indx2 = i;
  }
  if (indx1 == -1 || indx2 == -1 || indx1 == indx2)
    return -1;
  users_[indx1]->delete_friend(users_[indx2]->id());
  users_[indx2]->delete_friend(users_[indx1]->id());
  return 0;
}

int Network::get_id(std::string name) {
  for (int i = 0; i < users_.size(); i++)
    if (users_[i]->name() == name)
      return users_[i]->id();

  return -1;
}

int Network::read_friends(char *fname) {
  std::ifstream f(fname);
  if (f.fail())
    return -1;

  std::string line;
  std::vector<std::string> lines;
  while (std::getline(f, line)) {
    lines.push_back(line);
  }
  for (int i = 1; i < lines.size(); i += 5) {
    std::vector<std::size_t> friends;
    int ic = std::stoi(lines[i]);
    size_t id = ic;
    std::string name = lines[i + 1];
    int year = std::stoi(lines[i + 2]);
    int zip = std::stoi(lines[i + 3]);

    std::stringstream ss(lines[i + 4]);
    std::string word;
    std::vector<std::string> tokens;
    while (ss >> word) {
      tokens.push_back(word);
    }

    for (std::string token : tokens) {
      int tk = std::stoi(token);
      size_t pb = tk;
      friends.push_back(pb);
    }

    User u(id, name, year, zip, friends);
    User *p = &u;
    users_.push_back(p);
  }
  return 0;
}

int Network::write_friends(char *fname) {
  std::ofstream f(fname);
  if (f.fail())
    return -1;

  f << num_users();
  f << "\n";

  for (User *u : users_) {
    f << u->id();
    f << "\n\t";
    f << u->name();
    f << "\n\t";
    f << u->year();
    f << "\n\t";
    f << u->zip();
    f << "\n\t";
    for (std::size_t fren : u->friends()) {
      f << fren << " ";
    }
    f << "\n";
  }
  return 0;
}

std::size_t Network::num_users() { return users_.size(); }

std::string Network::user_info(size_t id) {
  std::string ret_s = "";
  for (size_t i = 0; i < users_.size(); i++) {
    if (i == id) {
      ret_s += users_[i]->id();
      ret_s += " ";
      ret_s += users_[i]->name();
      ret_s += " ";
      ret_s += users_[i]->year();
      ret_s += " ";
      ret_s += users_[i]->zip();
      return ret_s;
    }
  }
  return "bad input";
}

User *Network::get_user(std::size_t id) {

  for (User *&u : users_) {
    if (u->id() == id) {
      return u;
    }
  }
  return nullptr;
}

bool Network::bfs(int from, int to, std::unordered_map<int, int> &parent,
                  std::unordered_set<int> &visited, std::vector<size_t> &set) {

  std::queue<int> q;
  q.push(from);
  visited.insert(from);
  set.push_back(from);
  while (!q.empty()) {

    User *temp = get_user(q.front());
    q.pop();

    for (auto f : temp->friends()) {

      if (visited.count(f) == 0) {

        parent[f] = temp->id();
        q.push(f);
        visited.insert(f);
        set.push_back(f);
        if (f == to) {
          return true;
        }
      }
    }
  }
  return false;
}

std::vector<int> Network::shortest_path(int from, int to) {
  std::vector<int> ret;
  std::unordered_map<int, int> parent;
  std::unordered_set<int> visited;
  std::vector<size_t> set;

  if (bfs(from, to, parent, visited, set)) {
    int i = to;
    while (i != from) {
      ret.push_back(i);
      i = parent[i];
    }
    ret.push_back(from);
  }
  return ret;
}

std::vector<std::vector<std::size_t>> Network::disjoint_sets() {

  std::unordered_map<int, int> trash;
  std::vector<std::vector<std::size_t>> ret;
  std::unordered_set<int> visited;
  std::size_t set_num;
  std::vector<int> todo;
  for (int i = 0; i < users_.size(); i++) {
    if (visited.count(i) == 0) {
      std::vector<std::size_t> set;
      set_num++;
      bfs(i, users_.size() - 1, trash, visited, set);
      ret.push_back(set);
    }
  }

  return ret;
}

std::vector<User *> users_;
