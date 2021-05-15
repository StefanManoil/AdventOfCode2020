#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
/*
Your flight departs in a few days from the coastal airport; the easiest way down to the coast from here is via toboggan.

The shopkeeper at the North Pole Toboggan Rental Shop is having a bad day. "Something's wrong with our computers; we can't log in!" You ask if you can take a look.

Their password database seems to be a little corrupted: some of the passwords wouldn't have been allowed by the Official Toboggan Corporate Policy that was in effect when they were chosen.

To try to debug the problem, they have created a list (your puzzle input) of passwords (according to the corrupted database) and the corporate policy when that password was set.

For example, suppose you have the following list:

1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc
Each line gives the password policy and then the password. The password policy indicates the lowest and highest number of times a given letter must appear for the password to be valid. For example, 1-3 a means that the password must contain a at least 1 time and at most 3 times.

In the above example, 2 passwords are valid. The middle password, cdefg, is not; it contains no instances of b, but needs at least 1. The first and third passwords are valid: they contain one a or nine c, both within the limits of their respective policies.

How many passwords are valid according to their policies?
*/

int main () {
    std::string line;
    std::ifstream myFile("PasswordPhilosophy.txt");
    if (myFile.is_open()) {
        int numValid = 0;
        while (std::getline(myFile, line)) {
            // get the three strings on each line, simple as they are seperated by whitespace
            std::stringstream lineStream(line);
            std::string minAndMaxNumOccurence, letter, password;
            lineStream >> minAndMaxNumOccurence >> letter >> password;
            // get the min and max occurence from the first string and store them
            std::string numString;
            int minNum, maxNum;
            for (unsigned i = 0; i < minAndMaxNumOccurence.length(); i++) {
                if (minAndMaxNumOccurence[i] == '-') {
                    minNum = std::stoi(numString);
                    numString = "";
                }
                else {
                    numString += minAndMaxNumOccurence[i];
                }
            }
            maxNum = std::stoi(numString);
            // get the char we look for in the password
            char letterToCheck = letter[0];
            // scan the current password and increment the counter if valid
            int amountLetterAppears = 0;
            for (unsigned i = 0; i < password.length(); i++) {
                if (password[i] == letterToCheck) amountLetterAppears++;
            }
            if (amountLetterAppears >= minNum && amountLetterAppears <= maxNum) numValid++;
        }
        std::cout << "Number of valid passwords: " << numValid << std::endl;
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }
}