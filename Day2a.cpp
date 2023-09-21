#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

//Winnie Kam

struct Game
{
    char a;
    char b;
};

map<pair<char, char>, char> rules =
    {
        {{'A', 'X'}, 'D'},
        {{'A', 'Y'}, 'W'},
        {{'A', 'Z'}, 'L'},
        {{'B', 'X'}, 'L'},
        {{'B', 'Y'}, 'D'},
        {{'B', 'Z'}, 'W'},
        {{'C', 'X'}, 'W'},
        {{'C', 'Y'}, 'L'},
        {{'C', 'Z'}, 'D'},
};

map<char, unsigned int> score =
    {
        {'X', 1},
        {'Y', 2},
        {'Z', 3},
        {'L', 0},
        {'D', 3},
        {'W', 6},
};

vector<Game> read_game_file(const string &filename)
{
    ifstream file{filename};
    vector<Game> games;
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            char a, b;
            stringstream ss(line);
            ss >> a;
            ss >> b;
            // cout << "a:" << a << ",b:" << b << endl;
            games.push_back(Game{a, b});
        }
    }
    return games;
}

unsigned int calculate_score(Game game)
{
    if (auto search = rules.find(make_pair(game.a, game.b)); search != rules.end())
    {
        /*std::cout << "Found:" << search->first.first
                  << " ,  " << search->first.second
                  << "Found:" << search->second << '\n';*/
        char result = search->second;
        char myplay = game.b;
        int play_score = score[myplay]; //only use [] if key is sure to exist
        int result_score = score[result];
        return play_score + result_score;
    }
    else
    {
        std::cout << "Rule Not found\n";
        return 0;
    }
}

int main(int argc, char *argv[])
{
    /*
    1 read in file and store it into a vector/list
    2 create a map of the w, d, l
    3 create a map of the scores
    4 go thru the list and compute the score
    */
    //cout << argc << endl;
    if (argc != 2)
    {
        cout << "Error: Usage: " << argv[0] << " <input_filename>" << endl;
        return 1;
    }
    string filename = argv[1];
    vector<Game> games = read_game_file(filename);
    unsigned int total_score = 0;
    for (Game game : games)
    {
        total_score += calculate_score(game);
    }
    cout << "Total Score: " << total_score << endl;
    return 0;
}
