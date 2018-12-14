#include <iostream>
#include <map>
#include <vector>

int main() {
    long int nPlayers = 9;
    long int lastMarble = 25;
    std::string waste;
    std::cin >> nPlayers;
    while (std::cin >> waste) {
        try {
            lastMarble = std::stoi(waste);
        } catch (const std::exception&) {
            continue;
        }
        break;
    }
    std::cout << nPlayers << " " << lastMarble << std::endl;
    lastMarble = lastMarble*100;

    std::vector<long int> marbles (1, 0);
    marbles.reserve(lastMarble);
    std::map<long int, long int> score;
    for (long int i=0; i<nPlayers; ++i) {
        score[i] = 0;
    }

    long int currentPlayer = -1;
    long int currentPos = 1;
    for (long int i=1; i<=lastMarble; ++i) {
        currentPlayer = (currentPlayer+1)%nPlayers;

        if (i%23 == 0) {
            currentPos -= 9;
            if (currentPos < 0) {
                currentPos = marbles.size()+currentPos;
            }
            score[currentPlayer] += marbles[currentPos];
            score[currentPlayer] += i;
            marbles.erase(marbles.begin()+currentPos);
            std::vector<long int>::iterator it = marbles.begin()+currentPos;

            if (++it == marbles.end()) {
                currentPos = 1;
            } else {
                currentPos = (currentPos+1)%marbles.size()+1;
            }
            continue;
        }
        
        std::vector<long int>::iterator it = marbles.begin()+currentPos;
        marbles.insert(it, i);

        if (++it == marbles.end()) {
            currentPos = 1;
        } else {
            currentPos = (currentPos+1)%marbles.size()+1;
        }

        // for (long int m : marbles) {
        //     std::cout << m << " ";
        // }
        // std::cout << std::endl;
    }

    long int best = 0;
    for (auto player : score) {
        if (player.second > best) {
            best = player.second;
        }
    }

    std::cout << "High score: " << best << std::endl;
    
    return 0;
}
