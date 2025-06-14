//
// Created by plant on 31.05.2025.
//

#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include <utility>

#include "TournamentSystem.h"

class RoundRobin : public TournamentSystem {
protected:
    void create_bracket() override;
    void accept_result(bool results[]) override;

public:
    RoundRobin(const std::vector<std::string> &player_names, float avg_ex_time): TournamentSystem(player_names, avg_ex_time) {}
    RoundRobin(std::vector<Player> players_, float avg_ex_time): TournamentSystem(std::move(players_), avg_ex_time) {}

    [[nodiscard]] int count_rounds() const override;
    [[nodiscard]] int count_matches() const override;
    [[nodiscard]] std::string system_name() const override;

};



#endif //ROUNDROBIN_H
