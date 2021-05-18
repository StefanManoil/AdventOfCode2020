#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
/*
--- Day 7: Handy Haversacks ---
You land at the regional airport in time for your next flight. In fact, it looks like you'll even have time to grab some food: all flights are currently delayed due to issues in luggage processing.

Due to recent aviation regulations, many rules (your puzzle input) are being enforced about bags and their contents; bags must be color-coded and must contain specific quantities of other color-coded bags. Apparently, nobody responsible for these regulations considered how long they would take to enforce!

For example, consider the following rules:

light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.
These rules specify the required contents for 9 bag types. In this example, every faded blue bag is empty, every vibrant plum bag contains 11 bags (5 faded blue and 6 dotted black), and so on.

You have a shiny gold bag. If you wanted to carry it in at least one other bag, how many different bag colors would be valid for the outermost bag? (In other words: how many colors can, eventually, contain at least one shiny gold bag?)

In the above rules, the following options would be available to you:

A bright white bag, which can hold your shiny gold bag directly.
A muted yellow bag, which can hold your shiny gold bag directly, plus some other bags.
A dark orange bag, which can hold bright white and muted yellow bags, either of which could then hold your shiny gold bag.
A light red bag, which can hold bright white and muted yellow bags, either of which could then hold your shiny gold bag.
So, in this example, the number of bag colors that can eventually contain at least one shiny gold bag is 4.

How many bag colors can eventually contain at least one shiny gold bag? (The list of rules is quite long; make sure you get all of it.)
*/

/* **** Important Note! ****
This solution only works for input where the sentences describing which bag contains what other bags are in a chronological order, what I mean by this 
is that a bag appearing on the left hand side of the word "contain" in a sentence should have been preceded by a sentence at some point which had that same bag appear 
on the right hand side. This is only necessary however if there is a logical chain of bags contained with other bags, for example:

Test Case 1:
light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 2 bright white bags, 3 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 4 faded blue bags, 3 dark brown bags.
faded blue bags contain 2 shiny gold bags.
shiny gold bags contain 8 light green bags.
dark brown bags contain no other bags.
light green bags contain no other bags.

Test Case 2:
light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 2 bright white bags, 3 muted yellow bags.
bright white bags contain 1 shiny gold bag.
dark brown bags contain no other bags.
muted yellow bags contain 4 faded blue bags, 3 dark brown bags.
faded blue bags contain 2 shiny gold bags.
shiny gold bags contain 8 light green bags.
light green bags contain no other bags.


My solution works for Test Case 1, as the above notes are satisfied, and I only need to do 1 pass over the input

My solution does not work for Test Case 2, because of the line, "dark brown bags contain no other bags", note there is "dark brown" on left hand side of contain in the sentence
but there is no sentence preceding this one with "dark brown" in the right hand side, it actually comes right after. My 1-pass solution will not work for test cases like this
but it can be fixed by doing 2 passes, pass first over the input and create the rightHandSideMap, then parse the rightHandSideMap to arrive at a solution.

*/
class TrieNode {
    private:
        std::string color;
        std::unordered_map<std::string, TrieNode*> children;
    public:
        TrieNode() {
        }
        TrieNode(std::string color) {
            this->color = color;
        }
        ~TrieNode() {
            for (auto& element : children) {
                delete element.second;
            }
        }
        void addNodeToChildren(TrieNode* newNode, std::string& color) {
            children.emplace(color, newNode);
        }
        std::string& getColor() {
            return color;
        }
        std::unordered_map<std::string, TrieNode*>& getChildren() {
            return children;
        }
};

void updateTree(TrieNode* rootNode, TrieNode* node, std::unordered_map<std::string, std::vector<std::string>>& rHSMap, std::unordered_set<std::string>& outermostBags,
std::vector<std::string>& currentMapPath, std::vector<std::string> createTreePath, bool outerBagOfShinyGold, int& returnCounter) {
    for (unsigned i = 0; i < currentMapPath.size(); i++) {
        createTreePath.emplace_back(currentMapPath[i]);
        std::cout << "added currentMapPath element to tree path successfully, the element is: " << currentMapPath[i] << std::endl;
        if ((outerBagOfShinyGold) && (outermostBags.count(currentMapPath[i]) == 0)) {
            returnCounter = returnCounter + 1;
            outermostBags.emplace(currentMapPath[i]);
        }
        if (rHSMap.count(currentMapPath[i]) > 0) {
            // createTreePath.emplace_back(currentMapPath[i]);
            std::cout << "currentMapPath element is in the right hand side map, so we update the mapPath to be the value of this element in the map" << std::endl;
            std::vector<std::string> newMapPath = rHSMap[currentMapPath[i]];
            // currentMapPath = rHSMap[currentMapPath[i]];
            std::cout << "new current map path: ";
            for (unsigned j = 0; j < currentMapPath.size(); j++) {
                std::cout << currentMapPath[j] << " ";
            }
            std::cout << std::endl;
            updateTree(rootNode, node, rHSMap, outermostBags, newMapPath, createTreePath, outerBagOfShinyGold, returnCounter);
            createTreePath.pop_back();
        }
        else {
            // createTreePath.emplace_back(currentMapPath[i]);
            // i guess the segmentation fault is happening because i am not reseting the node pointer to the root
            node = rootNode;
            int lastPosOfTreePath = createTreePath.size() - 1;
            std::cout << "traverse the tree to the correct node and add the new node, if necessary" << std::endl;
            for (unsigned j = lastPosOfTreePath; j >= 1; j--) {
                std::cout << "element of tree path: " << createTreePath[j] << std::endl;
                node = node->getChildren()[createTreePath[j]];
            }
            std::cout << "first element of tree path: " << createTreePath[0] << std::endl;
            if (node->getChildren().count(createTreePath[0]) == 0) {
                std::cout << "adding to the " << node->getColor() << " node, the child node: " << createTreePath[0] << std::endl;
                node->addNodeToChildren(new TrieNode(createTreePath[0]), createTreePath[0]);
            }
            createTreePath.pop_back();
        }

    }
}

int main() {
    std::string line;
    std::ifstream myFile("HandyHaversacks.txt");
    if (myFile.is_open()) {
        std::unordered_set<std::string> outermostBagColorsCountedAlready;
        std::unordered_map<std::string, std::vector<std::string>> rightHandSideMap;
        TrieNode* root = new TrieNode("root");
        int returnCounter = 0;
        while (std::getline(myFile, line)) {
            std::stringstream lineStream(line);
            std::string currentWordOnLine;
            bool scanningLeftOfContains = true;
            std::string leftHandSideOfLine;
            std::vector<std::string> rightHandSideOfLine;
            std::vector<std::string> wholeLine;
            while (lineStream >> currentWordOnLine) {
                std::cout << "currentWordOnLine: " << currentWordOnLine << std::endl;
                if (currentWordOnLine == "contain") {
                    scanningLeftOfContains = false;
                }
                if (scanningLeftOfContains) {
                    if (currentWordOnLine == "bags") {
                        leftHandSideOfLine = wholeLine[0] + " " + wholeLine[1];
                        std::cout << "leftHandSideOfLine: " << leftHandSideOfLine << std::endl;
                        // if (rightHandSideMap.count(leftHandSideOfLine) == 0) {
                        //     root->addNodeToChildren(new TrieNode(leftHandSideOfLine));
                        // }
                    }
                    else {
                        wholeLine.emplace_back(currentWordOnLine);   
                    }
                }
                else {
                    if (currentWordOnLine == "bags," || currentWordOnLine == "bag," || currentWordOnLine == "bags." || currentWordOnLine == "bag.") {
                        int sizeOfWholeLine = wholeLine.size();
                        rightHandSideOfLine.emplace_back(wholeLine[sizeOfWholeLine - 2] + " " + wholeLine[sizeOfWholeLine - 1]);
                        std::cout << "last seen color on right side of line: " << wholeLine[sizeOfWholeLine - 2] << " " << wholeLine[sizeOfWholeLine - 1] << std::endl;
                        if (rightHandSideMap.count(rightHandSideOfLine.back()) == 0) {
                            std::vector<std::string> rightHandSideMapValue;
                            rightHandSideMapValue.emplace_back(leftHandSideOfLine);
                            rightHandSideMap.emplace(rightHandSideOfLine.back(), rightHandSideMapValue);
                            // update the tree using recursion if the leftHandSideOfLine is in rightHandSideMap already
                            // can also update the return count in the recursion while building the tree (check for shinyGold in rightHandSideMapKey at current level)
                            // we don't need to create the tree first, then parse it to get the return count, this can be done in one step
                            if (rightHandSideOfLine.back() == "shiny gold") {
                                std::cout << "start recursion if rhs key is placed for first time and it is shiny gold" << std::endl;
                                updateTree(root, root, rightHandSideMap, outermostBagColorsCountedAlready, rightHandSideMapValue, {}, true, returnCounter);
                            }
                            else {
                                std::cout << "start recursion if rhs key is placed for first time" << std::endl;
                                updateTree(root, root, rightHandSideMap, outermostBagColorsCountedAlready, rightHandSideMapValue, {}, false, returnCounter);
                            }
                        }
                        else {
                            std::vector<std::string> rightHandSideMapValue;
                            rightHandSideMapValue.emplace_back(leftHandSideOfLine);
                            rightHandSideMap[rightHandSideOfLine.back()].emplace_back(leftHandSideOfLine);
                            if (rightHandSideOfLine.back() == "shiny gold") {
                                std::cout << "start recursion if rhs key is already placed and it is shiny gold" << std::endl;
                                updateTree(root, root, rightHandSideMap, outermostBagColorsCountedAlready, rightHandSideMapValue, {}, true, returnCounter);
                            }
                            else {
                                std::cout << "start recursion if rhs key is already placed" << std::endl;
                                updateTree(root, root, rightHandSideMap, outermostBagColorsCountedAlready, rightHandSideMapValue, {}, false, returnCounter);
                            }
                        }
                    }
                    else {
                        wholeLine.emplace_back(currentWordOnLine);
                    }
                }
            }

        }
        // deallocate the tree from memory
        delete root;
        // print answer
        std::cout << returnCounter << std::endl;
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }
}