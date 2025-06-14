# Tournament System Chooser

**Tournament System Chooser** allows you to compare different tournament systems, choose one, and then run it.

## Used Library

The **LibHaru** library was used, which can be found [here](https://github.com/libharu/libharu).  
libharu uses CMake, so you can easily install it and link it to your project.

## Usage

Run **TournamentSystemChooser.exe** located in **cmake-build-debug**. No command line arguments are taken.

The data is inputted via console. The program requires:

- Amount of players
- Expected length of a single game (in minutes)
- Names (or IDs) of all the players

Afterward the program reads a character (case-insensitive) to allow you to choose between the following systems:

- `S` - [Swiss](https://en.wikipedia.org/wiki/Swiss-system_tournament)
- `E` - [Single elimination](https://en.wikipedia.org/wiki/Single-elimination_tournament)
- `R` - [Round Robin](https://en.wikipedia.org/wiki/Round-robin_tournament)

Once a choice is made, all important metrics are shown in the console.  
Input `Y` to confirm your choice and run the tournament.

Pairings for each round are shown both in the console and printed to a PDF file named "pairings_round\<i>.pdf" located
in **pairings** folder.

Input results as `1` if the first player won and `0` if the second player won.  
Separate the results for each match with spaces.

After each round:

- New pairings are made
- Standings are printed to a PDF file named "standings_round\<i>.pdf" located in **standings** folder