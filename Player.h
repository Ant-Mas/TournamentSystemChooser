
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
#include <utility>

class Player {
private:
  std::string name;
  int wins = 0;
  int losses = 0;

public:
  Player(std::string name, int wins, int losses): name(std::move(name)), wins(wins), losses(losses) {
  };

  explicit Player(std::string name): name(std::move(name)) {
  };

  [[nodiscard]] std::string get_name() const { return name; };
  [[nodiscard]] int get_wins() const { return wins; };
  [[nodiscard]] int get_losses() const { return losses; };

  bool operator==(const Player &other) const {
    return get_wins() == other.get_wins() && get_name() == other.get_name();
  }

  bool operator<(const Player &other) const { return get_wins() < other.get_wins(); }
  bool operator>(const Player &other) const { return get_wins() > other.get_wins(); }


  void add_win() { wins++; };
  void add_loss() { losses++; };

  void print() const { std::cout << name << ", record: " << wins << "-" << losses << std::endl; };
};


#endif //PLAYER_H
