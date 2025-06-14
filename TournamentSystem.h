#ifndef TOURNAMENTSYSTEM_H
#define TOURNAMENTSYSTEM_H
#include <string>
#include <utility>
#include <vector>
#include "Player.h"

class TournamentSystem {
protected:
    size_t player_amount;
    std::vector<Player> players;
    float avg_ex_time;
    std::vector<std::pair<Player *, Player *> > bracket;
    int current_round = 0;

    virtual void create_bracket() = 0;

    virtual void accept_result(bool results[]) = 0;

    bool add_bye_if_needed();

    void shuffle_players();

public:
    virtual ~TournamentSystem() = default;

    TournamentSystem(std::vector<Player> players_, float avg_ex_time_): player_amount(players_.size()),
                                                                        players(std::move(players_)),
                                                                        avg_ex_time(avg_ex_time_) {
    };

    TournamentSystem(const std::vector<std::string> &player_names, float avg_ex_time_);

    [[nodiscard]] virtual int count_rounds() const = 0;

    [[nodiscard]] virtual int count_matches() const = 0;

    [[nodiscard]] float count_ex_time() const;

    [[nodiscard]] virtual std::string system_name() const = 0;

    [[nodiscard]] std::vector<Player *> get_players_by_record() const;

    void list_info() const;

    void list_players() const;

    void list_players_by_record() const;

    void list_bracket() const;

    void print_pdf_standings() const;

    void print_pdf_pairings() const;

    void get_results(bool empty_results[]) const;

    void run();
};


#endif //TOURNAMENTSYSTEM_H
