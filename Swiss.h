//
// Created by plant on 06.06.2025.
//

#ifndef SWISS_H
#define SWISS_H


#include "TournamentSystem.h"

class Swiss : public TournamentSystem {
protected:
    void create_bracket() override;

    void accept_result(bool results[]) override;

public:
    Swiss(const std::vector<std::string> &player_names,
          float avg_ex_time): TournamentSystem(player_names, avg_ex_time) {
    }

    Swiss(std::vector<Player> players_, float avg_ex_time): TournamentSystem(std::move(players_), avg_ex_time) {
    }

    [[nodiscard]] int count_rounds() const override;

    [[nodiscard]] int count_matches() const override;

    [[nodiscard]] std::string system_name() const override;
};


#endif //SWISS_H
