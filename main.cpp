#include <iostream>
#include "TournamentSystem.cpp"
#include "RoundRobin.cpp"
#include "SingleEliminationBracket.cpp"
#include "Swiss.cpp"


int main() {
    int player_amount;
    float avg_ex_time;

    std::cout << "Enter number of players (int) and average expected time for round in minutes (float): " << std::endl;
    std::cin >> player_amount >> avg_ex_time;

    std::vector<std::string> player_names(player_amount);

    std::cout << "Enter player names in separate lines (" + std::to_string(player_amount) + " strings):" << std::endl;
    std::cin.ignore();
    for (int i = 0; i < player_amount; i++) {
        std::getline(std::cin, player_names[i]);
    }

    char choice = '_';

    TournamentSystem *tournament = new Swiss(player_names, avg_ex_time);

    std::cout << "Enter your choice (S for Swiss, E for Single Elimination or R for Round Robin) and then Y to confirm:"
            << std::endl;
    while (choice != 'y' && choice != 'Y') {
        std::cin >> choice;
        switch (choice) {
            case 'S':
                ;
            case 's': {
                delete(tournament);
                tournament = new Swiss(player_names, avg_ex_time);
                break;
            }
            case 'E':
                ;
            case 'e': {
                delete(tournament);
                tournament = new SingleEliminationBracket(player_names, avg_ex_time);
                break;
            }
            case 'R':
                ;
            case 'r': {
                delete(tournament);
                tournament = new RoundRobin(player_names, avg_ex_time);
                break;
            }
            default: {
                std::cout << "Invalid choice, using default/last known system" << std::endl;
            }
        }
        tournament->list_info();
    }

    tournament->run();
    delete(tournament);
    return 0;
}


/*
 * << Haru Free PDF Library 2.0.0 >> -- arc_demo.c
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */





