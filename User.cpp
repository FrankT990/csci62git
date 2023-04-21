#include "User.h"
#include <fstream>
#include <sstream>
// pre:
// post:
User::User() {}

// pre: all inputs are valid
// post: creates a user with corresponding inputs
User::User(std::size_t id, std::string name, int year, int zip,
           std::vector<std::size_t> friends) {
  id_ = id;
  name_ = name;
  year_ = year;
  zip_ = zip;
  friends_ = friends;
}

// pre: None
// post: Adds the id of the "friend" User to this User's friends_
void User::add_friend(int id) {
  for (size_t i = 0; i < friends_.size(); i++) {
    if (friends_[i] == id) {
      return;
    }
  }
  friends_.push_back(id);
}

// pre: None
// post: Deletes the id of the "friend" User to this User's friends_
void User::delete_friend(int id) {
  for (size_t i = 0; i < friends_.size(); i++) {
    if (friends_[i] == id) {
      friends_[i] = friends_[friends_.size() - 1];
      friends_.pop_back();
    }
  }
}

// pre: None
// post: returns this User's id
std::size_t User::id() const { return id_; }

// pre: None
// post: returns this User's name
std::string User::name() const { return name_; }

// pre: None
// post: returns this User's birth year
int User::year() const { return year_; }

// pre: None
// post: returns this User's zip code
int User::zip() const { return zip_; }

// pre: None
// post: returns a pointer to this User's friends_
std::vector<std::size_t> User::friends() { return friends_; }
