#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
/*
--- Day 4: Passport Processing ---
--- Part Two ---
The line is moving more quickly now, but you overhear airport security talking about how passports with invalid data are getting through. Better add some data validation, quick!

You can continue to ignore the cid field, but each other field has strict rules about what values are valid for automatic validation:

byr (Birth Year) - four digits; at least 1920 and at most 2002.
iyr (Issue Year) - four digits; at least 2010 and at most 2020.
eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
hgt (Height) - a number followed by either cm or in:
If cm, the number must be at least 150 and at most 193.
If in, the number must be at least 59 and at most 76.
hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
pid (Passport ID) - a nine-digit number, including leading zeroes.
cid (Country ID) - ignored, missing or not.
Your job is to count the passports where all required fields are both present and valid according to the above rules. Here are some example values:

byr valid:   2002
byr invalid: 2003

hgt valid:   60in
hgt valid:   190cm
hgt invalid: 190in
hgt invalid: 190

hcl valid:   #123abc
hcl invalid: #123abz
hcl invalid: 123abc

ecl valid:   brn
ecl invalid: wat

pid valid:   000000001
pid invalid: 0123456789
Here are some invalid passports:

eyr:1972 cid:100
hcl:#18171d ecl:amb hgt:170 pid:186cm iyr:2018 byr:1926

iyr:2019
hcl:#602927 eyr:1967 hgt:170cm
ecl:grn pid:012533040 byr:1946

hcl:dab227 iyr:2012
ecl:brn hgt:182cm pid:021572410 eyr:2020 byr:1992 cid:277

hgt:59cm ecl:zzz
eyr:2038 hcl:74454a iyr:2023
pid:3556412378 byr:2007
Here are some valid passports:

pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1980
hcl:#623a2f

eyr:2029 ecl:blu cid:129 byr:1989
iyr:2014 pid:896056539 hcl:#a97842 hgt:165cm

hcl:#888785
hgt:164cm byr:2001 iyr:2015 cid:88
pid:545766238 ecl:hzl
eyr:2022

iyr:2010 hgt:158cm hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719
Count the number of valid passports - those that have all required fields and valid values. Continue to treat cid as optional. In your batch file, how many passports are valid?
*/

int main() {
    std::string line;
    std::ifstream myFile("PassportProcessing.txt");
    if (myFile.is_open()) {
        int numFieldsInBatch = 0;
        bool batchContainsCountryId = false;
        //std::set<std::string> fields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
        std::set<std::string> eyeColors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        std::string word;
        int numValid = 0;
        while (std::getline(myFile, line)) {
            if (line == "") {
                // check if the batch we just scanned over is valid
                if (((numFieldsInBatch == 7) && (batchContainsCountryId == false)) || numFieldsInBatch == 8) {
                    numValid++;
                }
                batchContainsCountryId = false;
                numFieldsInBatch = 0;
            }
            else {
                std::stringstream lineStream(line);
                while (lineStream >> word) {
                    std::string wholeWord = word;
                    word = word.substr(0, 3);
                    if (word == "cid") {
                        batchContainsCountryId = true;
                        numFieldsInBatch++;
                    }
                    else if (word == "byr") {
                        std::string lastFourDigitsString = wholeWord.substr(4);
                        bool isValid = false;
                        for (int i = 0; i < lastFourDigitsString.length(); i++) {
                            if (lastFourDigitsString[i] >= '0' && lastFourDigitsString[i] <= '9') {
                                if (i == (lastFourDigitsString.length() - 1)) {
                                    isValid = true;
                                }
                            }
                            else {
                                break;
                            }
                        }
                        if (lastFourDigitsString.length() == 4 && isValid) {
                            int lastFourDigits = std::stoi(lastFourDigitsString);
                            if (lastFourDigits >= 1920 && lastFourDigits <= 2002) {
                                // std::cout << "byr valid" << std::endl;
                                numFieldsInBatch++;
                            }
                        }
                    }
                    else if (word == "iyr") {
                        std::string lastFourDigitsString = wholeWord.substr(4);
                        bool isValid = false;
                        for (int i = 0; i < lastFourDigitsString.length(); i++) {
                            if (lastFourDigitsString[i] >= '0' && lastFourDigitsString[i] <= '9') {
                                if (i == (lastFourDigitsString.length() - 1)) {
                                    isValid = true;
                                }
                            }
                            else {
                                break;
                            }
                        }
                        if (lastFourDigitsString.length() == 4 && isValid) {
                            int lastFourDigits = std::stoi(lastFourDigitsString);
                            if (lastFourDigits >= 2010 && lastFourDigits <= 2020) {
                                // std::cout << "iyr valid" << std::endl;
                                numFieldsInBatch++;
                            }
                        }
                    }
                    else if (word == "eyr") {
                        std::string lastFourDigitsString = wholeWord.substr(4);
                        bool isValid = false;
                        for (int i = 0; i < lastFourDigitsString.length(); i++) {
                            if (lastFourDigitsString[i] >= '0' && lastFourDigitsString[i] <= '9') {
                                if (i == (lastFourDigitsString.length() - 1)) {
                                    isValid = true;
                                }
                            }
                            else {
                                break;
                            }
                        }
                        if (lastFourDigitsString.length() == 4 && isValid) {
                            int lastFourDigits = std::stoi(lastFourDigitsString);
                            if (lastFourDigits >= 2020 && lastFourDigits <= 2030) {
                                // std::cout << "eyr valid" << std::endl;
                                numFieldsInBatch++;
                            }
                        }
                    }
                    else if (word == "hgt") {
                        std::string units = wholeWord.substr(wholeWord.length() - 2);
                        int lenOfValue = (wholeWord.length() - 2) - 4;
                        std::string valueString = wholeWord.substr(4, lenOfValue);
                        bool isValid = false;
                        for (int i = 0; i < valueString.length(); i++) {
                            if (valueString[i] >= '0' && valueString[i] <= '9') {
                                if (i == (valueString.length() - 1)) {
                                    isValid = true;
                                }
                            }
                            else {
                                break;
                            }
                        }
                        int value;
                        if (isValid) value = std::stoi(valueString);
                        if (units == "cm") {
                            if (value >= 150 && value <= 193) {
                                // std::cout << "hgt valid" << std::endl;
                                numFieldsInBatch++;
                            }
                        }
                        else if (units == "in"){
                            if (value >= 59 && value <= 76) {
                                // std::cout << "hgt valid" << std::endl;
                                numFieldsInBatch++;
                            }
                        }
                    }
                    else if (word == "hcl") {
                        for (int i = 4; i < wholeWord.length(); i++) {
                            if (i == 4) {
                                if (wholeWord[i] != '#') break;
                            }
                            else {
                                if ((wholeWord[i] >= '0' && wholeWord[i] <= '9') || (wholeWord[i] >= 'a' && wholeWord[i] <= 'f')) {
                                    if (i == (wholeWord.length() - 1)) {
                                        if ((i - 4) == 6) {
                                            // std::cout << "hcl valid" << std::endl;
                                            numFieldsInBatch++;
                                        }
                                    }
                                }
                                else {
                                    break;
                                }
                            }
                        }
                    }
                    else if (word == "ecl") {
                        std::string currentColor = wholeWord.substr(4);
                        if (eyeColors.count(currentColor) > 0) {
                            std::cout << "ecl valid" << std::endl;
                            numFieldsInBatch++;
                        }
                    }
                    else if (word == "pid") {
                        std::string num = wholeWord.substr(4);
                        if (num.length() == 9) {
                            for (int i = 0; i < num.length(); i++) {
                                if (num[i] >= '0' && num[i] <= '9') {
                                    if (i == (num.length() - 1)) {
                                        // std::cout << "pid valid" << std::endl;
                                        numFieldsInBatch++;
                                    }
                                }
                                else {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        // it looks like the input does not have a "\n" character after the last line so, we will handle this here as our first if in the while loop won't do it
        if (((numFieldsInBatch == 7) && (batchContainsCountryId == false)) || numFieldsInBatch == 8) {
            numValid++;
        }
        std::cout << "Number of valid passports: " << numValid << std::endl;
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }
}