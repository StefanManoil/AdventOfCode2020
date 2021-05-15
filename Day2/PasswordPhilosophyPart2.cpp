#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
/*
--- Part Two ---
While it appears you validated the passwords correctly, they don't seem to be what the Official Toboggan Corporate Authentication System is expecting.

The shopkeeper suddenly realizes that he just accidentally explained the password policy rules from his old job at the sled rental place down the street! The Official Toboggan Corporate Policy actually works a little differently.

Each policy actually describes two positions in the password, where 1 means the first character, 2 means the second character, and so on. (Be careful; Toboggan Corporate Policies have no concept of "index zero"!) Exactly one of these positions must contain the given letter. Other occurrences of the letter are irrelevant for the purposes of policy enforcement.

Given the same example list from above:

1-3 a: abcde is valid: position 1 contains a and position 3 does not.
1-3 b: cdefg is invalid: neither position 1 nor position 3 contains b.
2-9 c: ccccccccc is invalid: both position 2 and position 9 contain c.
How many passwords are valid according to the new interpretation of the policies?
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
            // get the first and second position from the first string and store them
            std::string numString;
            int firstPos, secondPos;
            for (unsigned i = 0; i < minAndMaxNumOccurence.length(); i++) {
                if (minAndMaxNumOccurence[i] == '-') {
                    firstPos = std::stoi(numString) - 1;
                    numString = "";
                }
                else {
                    numString += minAndMaxNumOccurence[i];
                }
            }
            secondPos = std::stoi(numString) - 1;
            // get the char we look for in the password
            char letterToCheck = letter[0];
            // scan the current password and check if it is valid according to above constraints
            if ((password[firstPos] == letterToCheck && password[secondPos] != letterToCheck) || (password[firstPos] != letterToCheck && password[secondPos] == letterToCheck)) {
                numValid++;
            }
        }
        std::cout << "Number of valid passwords: " << numValid << std::endl;
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }
}