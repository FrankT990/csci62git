#ifndef USER_H
#define USER_H

#include <iostream>
#include <queue>


class User {

public:
  User();

  User(std::size_t id, std::string name, int year, int zip,
       std::vector<std::size_t>);

  void add_friend(int id);

  void delete_friend(int id);

  size_t id() const;

  std::string name() const;

  int year() const;

  int zip() const;

  std::vector<std::size_t> friends();

  int depth, predecessor;

private:
  std::size_t id_;

  std::string name_;

  int year_;

  int zip_;

  std::vector<std::size_t> friends_;
};

#endif // USER_H
