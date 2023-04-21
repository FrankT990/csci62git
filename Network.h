#ifndef NETWORK_H
#define NETWORK_H

#include "User.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Network {

public:
  Network();

  void add_user(User *inp);

  int add_connection(std::string s1, std::string s2);

  int remove_connection(std::string s1, std::string s2);

  int get_id(std::string name);

  int read_friends(char *fname);

  int write_friends(char *fname);

  std::size_t num_users();

  std::string user_info(size_t id);

  std::vector<int> shortest_path(int from, int to);

  User *get_user(std::size_t id);

  bool bfs(int from, int to, std::unordered_map<int, int> &parent,
           std::unordered_set<int> &visited, std::vector<std::size_t> &set);

  std::vector<std::vector<std::size_t>> disjoint_sets();

private:
  std::vector<User *>
      users_; // You may choose to use a vector of User pointers instead.
};

#endif // NETWORK_H
