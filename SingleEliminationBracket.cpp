//
// Created by plant on 05.06.2025.
//

#include "SingleEliminationBracket.h"
#include <cmath>

void SingleEliminationBracket::create_bracket() {
    if (static_cast<int>(ceil(player_amount / pow(2, current_round))) % 2 == 1) {
        players.emplace_back("Bye");
        player_amount++;
        std::swap(players[ceil(player_amount / pow(2, current_round + 1)) * 2 - 1], players[player_amount - 1]);
    }

    bracket = std::vector<std::pair<Player *, Player *> >();
    int matches_amount = ceil(player_amount / pow(2, current_round + 1));
    for (size_t i = 0; i < matches_amount; ++i) {
        bracket.emplace_back(&players[i], &players[matches_amount * 2 - 1 - i]);
    }
    current_round += 1;
}

int SingleEliminationBracket::count_rounds() const {
    return ceil(log2(player_amount));
}

int SingleEliminationBracket::count_matches() const {
    return player_amount - 1;
}

std::string SingleEliminationBracket::system_name() const {
    return "Single Elimination Bracket";
}

void SingleEliminationBracket::accept_result(bool results[]) {
    for (size_t i = 0; i < bracket.size(); ++i) {
        if (results[i]) {
            bracket[i].first->add_win();
            bracket[i].second->add_loss();
        } else {
            bracket[i].first->add_loss();
            bracket[i].second->add_win();
            std::swap(players[i], players[ceil(player_amount / pow(2, current_round)) * 2 - 1 - i]);
        }
    }
}
