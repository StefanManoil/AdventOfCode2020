#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <vector>
/*
Puzzle Description:

--- Part Two ---
The Elves in accounting are thankful for your help; one of them even offers you a starfish coin they had left over from a past vacation. They offer you a second one if you can find three numbers in your expense report that meet the same criteria.

Using the above example again, the three entries that sum to 2020 are 979, 366, and 675. Multiplying them together produces the answer, 241861950.

In your expense report, what is the product of the three entries that sum to 2020?
*/

int main () {
    std::string line;
    std::ifstream myFile("reportRepairInput.txt");
    //std::set<int> numbersSeenSoFar;
    std::vector<int> allNumbers;
    if (myFile.is_open()) {
        while (std::getline(myFile, line)) {
            std::stringstream numberStream(line);
            int number;
            numberStream >> number;
            allNumbers.emplace_back(number);
        }
        // three sum implementation, go through the vector, anchor the current element and perform two sum on all other elements except current element, with the new target being 2020 - current
        for (int i = 0; i < allNumbers.size(); i++) {
            int anchorNumber = allNumbers.at(i);
            int newTarget = 2020 - anchorNumber;
            std::set<int> numberSeenSoFarTwoSum;
            for (int j = 0; j < allNumbers.size(); j++) {
                if (i == j) continue;
                int currentNumber = allNumbers.at(j);
                int differenceNewTargetAndCurrentNumber = newTarget - currentNumber;
                if (numberSeenSoFarTwoSum.count(differenceNewTargetAndCurrentNumber) > 0) {
                    std::cout << differenceNewTargetAndCurrentNumber * currentNumber * anchorNumber << std::endl;
                    return 0;
                }
                else {
                    numberSeenSoFarTwoSum.emplace(allNumbers.at(j));
                }
            }
        }
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }
}