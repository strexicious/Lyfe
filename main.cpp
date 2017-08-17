/*   _   _______ _      _      ___  ___ _____ 
    | | / /_   _| |    | |     |  \/  ||  ___|
    | |/ /  | | | |    | |     | .  . || |__  
    |    \  | | | |    | |     | |\/| ||  __| 
    | |\  \_| |_| |____| |____ | |  | || |___ 
    \_| \_/\___/\_____/\_____/ \_|  |_/\____/ 
*/

#include <ctime>
#include <random>
#include <iostream>
#include <array>
#include <vector>

template <int size>
using universe_t = std::array<std::array<bool, size>, size>;

// program constants
constexpr unsigned int UPS = 7*2; // update per second
// 45 works well with maximized normal font terminal
// Maximum zoomed out on my screen is 98
constexpr unsigned int UNIVERSE_SIZE = 98; // it's *UNIVERSAL*
constexpr double CHANCE_TO_LIVE = 0.4;

void PerfomCheckup(const universe_t<UNIVERSE_SIZE>& universe, const unsigned int& x,
	const unsigned int& y, const bool& alive, bool& nextMomentAlive) {
    int mfn = 0;// meFuckingNeigbours
    for (int i = -1; i < 2; ++i) {
        if (x == 0 && i == -1)
            continue;
        if (x == UNIVERSE_SIZE-1 && i == 1)
            continue;

        if (y != 0) {
            bool fromPrev = universe[y-1][x+i];
            if(fromPrev)
                ++mfn;
        }

        if (y != UNIVERSE_SIZE-1) {
            bool fromNext = universe[y+1][x+i];
            if(fromNext)
                ++mfn;
        }

        if (i%2) {
            bool fromThis = universe[y][x+i];
            if(fromThis)
                ++mfn;
        }
    }

    // GAME RULES
    if (alive) {
        if (mfn < 2)
            nextMomentAlive = false;
        else if (mfn > 3)
            nextMomentAlive = false;
        else
            nextMomentAlive = alive;
    } else if (!alive) {
        if (mfn == 3)
            nextMomentAlive = true;
        else
            nextMomentAlive = alive;
    }
}

int main() {
    universe_t<UNIVERSE_SIZE> universe {};

    // TEST PATTERN - Glider Gun
    // universe[1][24+1] = true;
    // universe[2][24+1] = true;
    // universe[2][22+1] = true;
    // universe[3][36] = true;
    // universe[3][35] = true;
    // universe[3][21+1] = true;
    // universe[3][20+1] = true;
    // universe[3][13+1] = true;
    // universe[3][12+1] = true;
    // universe[4][36] = true;
    // universe[4][35] = true;
    // universe[4][21+1] = true;
    // universe[4][20+1] = true;
    // universe[4][15+1] = true;
    // universe[4][11+1] = true;
    // universe[5][21+1] = true;
    // universe[5][20+1] = true;
    // universe[5][16+1] = true;
    // universe[5][10+1] = true;
    // universe[5][2] = true;
    // universe[5][1] = true;
    // universe[6][24+1] = true;
    // universe[6][22+1] = true;
    // universe[6][17+1] = true;
    // universe[6][16+1] = true;
    // universe[6][14+1] = true;
    // universe[6][10+1] = true;
    // universe[6][2] = true;
    // universe[6][1] = true;
    // universe[7][24+1] = true;
    // universe[7][16+1] = true;
    // universe[7][10+1] = true;
    // universe[8][11+1] = true;
    // universe[8][15+1] = true;
    // universe[9][12+1] = true;
    // universe[9][13+1] = true;

    // give'em life
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(CHANCE_TO_LIVE);
    for (unsigned int i = 0; i < universe.size(); ++i)
    {
        for (unsigned int j = 0; j < universe.size(); ++j)
        {
            universe[i][j] = (bool) dist(gen); // Try your luck
        }
    }

    // initial draw
    for (unsigned int y = 0; y < universe.size(); ++y) {
		for (unsigned int x = 0; x < universe.size(); ++x) {
			if (universe[y][x])
				std::cout << "\u25A0 ";
			else
				std::cout << "- ";
		}
		std::cout << "\n";
	}

    std::clock_t lastTime = clock();
    while (true)
    {
        std::clock_t currentTime = clock();
        if ((currentTime - lastTime) < 1000000/UPS)
            continue;

        // 1. add one neighbour to other blocks
        // 2. check if they are alive and add them to me neighbours

        std::array<std::array<bool, UNIVERSE_SIZE>, UNIVERSE_SIZE> nextMoment = {};

        for (unsigned int i = 0; i < UNIVERSE_SIZE; ++i)
        {
            for (unsigned int j = 0; j < UNIVERSE_SIZE; ++j)
            {
                PerfomCheckup(universe, j, i, universe[i][j], nextMoment[i][j]);

                if (nextMoment[i][j])
                    std::cout << "\u25A0" << " ";
                else
                    std::cout << "- ";
            }
            std::cout << "\n";
        }

        universe = nextMoment;
        
        std::cout << "============================================ " <<
            (currentTime - lastTime)/1000 << " ms\n";
        lastTime = currentTime;
        // break;
    }

    return 0;
}
