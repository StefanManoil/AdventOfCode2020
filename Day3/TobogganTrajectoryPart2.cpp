#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
/*
--- Part Two ---
Time to check the rest of the slopes - you need to minimize the probability of a sudden arboreal stop, after all.

Determine the number of trees you would encounter if, for each of the following slopes, you start at the top-left corner and traverse the map all the way to the bottom:

Right 1, down 1.
Right 3, down 1. (This is the slope you already checked.)
Right 5, down 1.
Right 7, down 1.
Right 1, down 2.
In the above example, these slopes would find 2, 7, 3, 4, and 2 tree(s) respectively; multiplied together, these produce the answer 336.

What do you get if you multiply together the number of trees encountered on each of the listed slopes?
*/

int main() {
    std::string line;
    std::ifstream myFile("TobogganTrajectory.txt");
    if (myFile.is_open()) {
        // now we have a bunch of slopes we need to worry about but it doesn't matter we can still do this in one pass through the input without storing it
        // have different variables for all the slopes and if any pos(s) are larger than the current line length, extend it like we did in part 1
        // we also need to be careful of the fifth and last slope as it goes down by 2, simple just check it every other line
        int posSlope1 = 0;
        int numTreesSlope1 = 0;
        //
        int posSlope2 = 0;
        int numTreesSlope2 = 0;
        //
        int posSlope3 = 0;
        int numTreesSlope3 = 0;
        //
        int posSlope4 = 0;
        int numTreesSlope4 = 0;
        //
        int posSlope5 = 0;
        int numTreesSlope5 = 0;
        int lineCounter = 0;
        while (std::getline(myFile, line)) {
            int amountOfTimesToExpandRight = 0;
            int lineLength = line.length();
            std::string newLine = line;
            // int maxPos = std::max(std::max(std::max(posSlope1, posSlope2), std::max(posSlope3, posSlope4)), posSlope5);
            // ^^ we don't even need this computation, we already are assured that slope4 is the largest
            if (posSlope4 >= lineLength) {
                amountOfTimesToExpandRight = posSlope4 / lineLength;
            }
            for (int i = 0; i < amountOfTimesToExpandRight; i++) {
                newLine += line;
            }
            if (newLine[posSlope1] == '#') {
                numTreesSlope1++;
            }
            if (newLine[posSlope2] == '#') {
                numTreesSlope2++;
            }
            if (newLine[posSlope3] == '#') {
                numTreesSlope3++;
            }
            if (newLine[posSlope4] == '#') {
                numTreesSlope4++;
            }
            if (lineCounter % 2 == 0 && newLine[posSlope5] == '#') {
                numTreesSlope5++;
            }
            posSlope1 += 1;
            posSlope2 += 3;
            posSlope3 += 5;
            posSlope4 += 7;
            if (lineCounter % 2 == 0) {
                posSlope5 += 1;
            }
            lineCounter++;
        }
        std::cout << numTreesSlope1 << std::endl;
        std::cout << numTreesSlope2 << std::endl;
        std::cout << numTreesSlope3 << std::endl;
        std::cout << numTreesSlope4 << std::endl;
        std::cout << numTreesSlope5 << std::endl;
        int multiplyTreesEncountered = numTreesSlope1 * numTreesSlope2 * numTreesSlope3 * numTreesSlope4 * numTreesSlope5;
        std::cout << "Multiply together number of trees encountered: " << multiplyTreesEncountered << std::endl;
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }
}