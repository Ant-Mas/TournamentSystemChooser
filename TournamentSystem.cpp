//
// Created by plant on 31.05.2025.
//

#include "TournamentSystem.h"

#include <algorithm>
#include "pdfwriter.cpp"

TournamentSystem::TournamentSystem(const std::vector<std::string> &player_names, float avg_ex_time_) {
  player_amount = player_names.size();
  avg_ex_time = avg_ex_time_;

  players.reserve(player_amount);

  for (const auto &name: player_names) {
    players.emplace_back(name);
  }
}

std::string format_minutes(const float minutes) {
  const int hours = minutes / 60;
  const int remaining_minutes = minutes - (hours * 60) + 0.5;
  std::string str_minutes;
  if (remaining_minutes >= 10) str_minutes = std::to_string(remaining_minutes);
  else str_minutes = "0" + std::to_string(static_cast<int>(minutes));
  if (hours > 0) return std::to_string(hours) + ":" + str_minutes;
  return str_minutes;
}

void TournamentSystem::list_info() const {
  std::cout << this->system_name() << std::endl
      << " ilosc rund: " << this->count_rounds() << std::endl
      << " spodziewany czas: " << format_minutes(this->count_ex_time()) << std::endl
      << " ilosc meczy: " << this->count_matches() << std::endl;
}


void TournamentSystem::list_players() const {
  for (const auto &player: players) {
    player.print();
  }
}

bool ptr_player_compare(const Player *player1, const Player *player2) {
  return player1->get_wins() - player2->get_wins() > 0;
}

std::vector<Player *> TournamentSystem::get_players_by_record() const {
  std::vector<Player *> ptr_players(player_amount);
  for (int i = 0; i < player_amount; ++i) {
    ptr_players[i] = const_cast<std::vector<Player *>::value_type>(&players[i]);
  }
  std::sort(ptr_players.begin(), ptr_players.end(), ptr_player_compare);
  return ptr_players;
}

void TournamentSystem::list_players_by_record() const {
  for (auto ptr_players = get_players_by_record(); const auto ptr_player: ptr_players) {
    ptr_player->print();
  }
}

void TournamentSystem::list_bracket() const {
  for (auto pair: bracket) {
    std::cout << pair.first->get_name() << " -- " << pair.second->get_name() << std::endl;
  }
}

void TournamentSystem::print_pdf_standings() const {
  createPDFTableFromVectors(this->get_players_by_record(),
                            "standings/standings_round" + std::to_string(current_round) + ".pdf");
}

void TournamentSystem::print_pdf_pairings() const {
  std::vector<std::pair<std::string, std::string> > names;
  names.reserve(bracket.size());
  for (auto pair: bracket) {
    names.emplace_back(pair.first->get_name(), pair.second->get_name());
  }
  createPDFWithCenteredText(names, "pairings/pairings_round" + std::to_string(current_round) + ".pdf");
}


bool TournamentSystem::add_bye_if_needed() {
  if (players.size() % 2 == 1) {
    players.emplace_back("Bye");
    player_amount++;
    return true;
  }
  return false;
}

void TournamentSystem::shuffle_players() {
  srand(time(nullptr));
  for (int i = 0; i < players.size(); i++) {
    std::swap(players[i], players[i + rand() % (players.size() - i)]);
  }
}

float TournamentSystem::count_ex_time() const {
  return this->count_rounds() * avg_ex_time;
}

void TournamentSystem::get_results(bool empty_results[]) const {
  std::cout << "Input round results 1 for left player win and 0 for right player win, divided by spaces" << std::endl;
  for (int i = 0; i < bracket.size(); i++) {
    std::cin >> empty_results[i];
  }
}

void TournamentSystem::run() {
  bool empty_results[(player_amount + 1) / 2];
  this->shuffle_players();
  for (int i = 0; i < this->count_rounds(); ++i) {
    this->create_bracket();
    this->print_pdf_pairings();
    this->list_bracket();
    this->get_results(empty_results);
    this->accept_result(empty_results);
    this->print_pdf_standings();
  }

  this->list_players_by_record();
}
