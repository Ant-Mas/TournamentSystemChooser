//
// Created by plant on 06.06.2025.
//

#include "Swiss.h"
#include <cmath>
#include <algorithm>

void Swiss::create_bracket() {
    this->add_bye_if_needed();

    bracket = std::vector<std::pair<Player *, Player *> >();
    int matches_amount = player_amount / 2;
    for (size_t i = 0; i < matches_amount; ++i) {
        bracket.emplace_back(&players[2 * i], &players[2 * i + 1]);
    }
    current_round += 1;
}

int Swiss::count_rounds() const {
    return ceil(log2(player_amount));
}

int Swiss::count_matches() const {
    return this->count_rounds() * floor(player_amount / 2);
}

std::string Swiss::system_name() const {
    return "Swiss";
}

void Swiss::accept_result(bool results[]) {
    for (size_t i = 0; i < bracket.size(); ++i) {
        if (results[i]) {
            bracket[i].first->add_win();
            bracket[i].second->add_loss();
        } else {
            bracket[i].first->add_loss();
            bracket[i].second->add_win();
        }
    }
    sort(players.begin(), players.end(), std::greater<>());
}
