#include "Network.h"
#include "User.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>

//this is a change to my file

void add_user(Network &n) {
  std::cout << "Enter in user to be added in format of: " << std::endl
            << "0 Jason Chen 2001 95053\n";
  std::string in;
  std::string in2;
  getline(std::cin >> in, in2);
  in += in2;

  std::stringstream ss(in);

  std::string word;
  std::vector<std::string> tokens;
  while (ss >> word)
    tokens.push_back(word);

  int i = std::stoi(tokens[0]);
  size_t id = i;
  std::string name = tokens[1] + " " + tokens[2];
  int year = std::stoi(tokens[3]);
  int zip = std::stoi(tokens[4]);
  std::vector<std::size_t> friends;
  User u(id, name, year, zip, friends);
  n.add_user(u);
  std::cout << "User added\n";
}

void make_friend(Network &n) {
  std::cout << "Enter in friendship to be added in format of: \nJason Chen "
               "Issac Boone\n";
  std::string in;
  std::string in2;
  getline(std::cin >> in, in2);
  in += in2;

  std::stringstream ss(in);
  std::string word;
  std::vector<std::string> tokens;
  while (ss >> word) {
    tokens.push_back(word);
  }
  std::string name1 = tokens[0] + " " + tokens[1];
  std::string name2 = tokens[2] + " " + tokens[3];

  if (n.add_connection(name1, name2) == 0) {
    std::cout << "Connection creation successful\n";
  } else {
    std::cout << "Connection creation unsuccessful\n";
  }
}

void remove_friend(Network &n) {
  std::cout << "Enter in friendship to be removed in format of: \nJason Chen "
               "Issac Boone\n";
  std::string in;
  std::string in2;
  getline(std::cin >> in, in2);
  in += in2;

  std::stringstream ss(in);
  std::string word;
  std::vector<std::string> tokens;
  while (ss >> word) {
    tokens.push_back(word);
  }
  std::string name1 = tokens[0] + " " + tokens[1];
  std::string name2 = tokens[2] + " " + tokens[3];
  if (n.remove_connection(name1, name2) == 0) {
    std::cout << "Connection removed successfully\n";
  } else {
    std::cout << "Connection removal unsuccessful\n";
  }
}

void print_users(Network &n) {
  std::cout
      << "ID Name Year "
         "Zip\n===========================================================\n";
  for (size_t i = 0; i < n.num_users(); i++) {
    std::cout << n.user_info(i) << "\n";
  }
}

void print_user_friends(Network &n) {

  std::cout << "Enter in user to to print friends in format of: " << std::endl
            << "Jason Chen\n";
  std::string in;
  std::string in2;
  getline(std::cin >> in, in2);
  in += in2;

  std::stringstream ss(in);

  std::string word;
  std::vector<std::string> tokens;
  while (ss >> word)
    tokens.push_back(word);

  User p = n.get_user(n.get_id(tokens[0] + " " + tokens[1]));

  for (int i = 0; i < p.friends().size(); i++) {
    std::cout << n.user_info(i) << "\n";
  }
}

void write_file(Network &n) {
  std::string s;
  std::cout << "input file name:\n";
  std::cin >> s;
  char *c_s = new char[s.length()];
  for (int i = 0; i < s.length(); i++) {
    c_s[i] = s[i];
  }
  n.write_friends(c_s);
}

void print_shortest_path(Network &n) {
  std::cout << "Enter in user to be added in format of: " << std::endl
            << "Isaac Boone Jasmine Clements\n";
  std::string in;
  std::string in2;
  getline(std::cin >> in, in2);
  in += in2;

  std::stringstream ss(in);

  std::string word;
  std::vector<std::string> tokens;
  while (ss >> word)
    tokens.push_back(word);

  std::string name1 = tokens[0] + " " + tokens[1];
  std::string name2 = tokens[2] + " " + tokens[3];

  int a = n.get_id(name1);
  int b = n.get_id(name2);

  std::vector<int> v;
  v = n.shortest_path(a, b);

  for (int i = v.size() - 1; i > 0; i--) {
    std::cout << n.get_user(i).name() << " . ";
  }
  std::cout << n.get_user(0).name() << "\n";
}

void print_sets(Network &n) {
  std::vector<std::vector<std::size_t>> sets = n.disjoint_sets();
  for (int i = 0; i < sets.size(); i++) {
    std::cout << "Set " << i << ":\n";
    for (int j = 0; j < sets[i].size(); j++) {
      std::cout << n.user_info(sets[i][j]) << "\n";
    }
  }
}

void read_file(Network &n) {
  std::string s;
  std::cout << "input file name:\n";
  std::cin >> s;
  char *c_s = new char[s.length()];
  for (int i = 0; i < s.length(); i++) {
    c_s[i] = s[i];
  }
  n.read_friends(c_s);
}

int main() {

  Network net;

  while (true) {
    std::cout << "=======================================================\n";
    std::cout << "pick an option:\n"
                 "1. Add user\n"
                 "2. Add friend connection\n"
                 "3. Remove friend connection\n"
                 "4. Print users\n"
                 "5. Print friends of a user\n"
                 "6. Write to file\n"
                 "7. Print shortest path to friend of user\n"
                 "8. Print Disjoint Sets\n"
                 "9. Terminate program\n"
                "10. Read File\n"
                "11. Terminate Program\n";
    int input;
    std::cin >> input;
    switch (input) {
    case 1:
      add_user(net);
      break;
    case 2:
      make_friend(net);
      break;
    case 3:
      remove_friend(net);
      break;
    case 4:
      print_users(net);
      break;
    case 5:
      print_user_friends(net);
      break;
    case 6:
      write_file(net);
      break;
    case 7:
      print_shortest_path(net);
      break;
    case 8:
      print_sets(net);
      break;
    case 9:
      break;
    case 10:
      read_file(net);
      break;
    default:
      assert(false);
      break;
    }
  }
}
