//
// Created by plant on 31.05.2025.
//

#include "RoundRobin.h"


void RoundRobin::create_bracket(){

  this->add_bye_if_needed();

  bracket = std::vector<std::pair<Player*, Player*>>();
  for (size_t i = 0; i < players.size()/2; ++i) {
    bracket.emplace_back(&players[i], &players[players.size()-1-i]);
  }
  current_round += 1;
}

int RoundRobin::count_rounds() const{
  return players.size() - 1;
}

int RoundRobin::count_matches() const{
  return  (players.size() - 1) * players.size() / 2;
}

std::string RoundRobin::system_name() const{
  return "Round Robin";
}

void RoundRobin::accept_result(bool results[]){
  for (size_t i = 0; i < bracket.size(); ++i) {
    if (results[i]) {
      bracket[i].first->add_win();
      bracket[i].second->add_loss();
    }else{
      bracket[i].first->add_loss();
      bracket[i].second->add_win();
    }
  }

  for (size_t i = 0; i < players.size(); ++i) {
    std::swap(players[i], players[(i+1)%players.size()]);
  }
}


