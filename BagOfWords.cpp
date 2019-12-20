#include "BagOfWords.h"
#include <cctype>
#include <iostream>

BagOfWords::BagOfWords(std::string review) {
	std::string currentWord = "";

	for (char currentCharacter : review) {
		if (isalpha(currentCharacter)) {
			currentWord += currentCharacter;
		}
		else if (currentWord != "") {
			if (wordMap.count(currentWord)) {
				wordMap[currentWord]++;
			}
			else {
				wordMap[currentWord] = 1;
			}
			currentWord = "";
		}
	}

	if (currentWord != "") {
		if (wordMap.count(currentWord)) {
			wordMap[currentWord]++;
		}
		else {
			wordMap[currentWord] = 1;
		}
	}
}

int BagOfWords::getNumberOfOccurencesOfWord(std::string word) {
	return wordMap[word];
}

bool BagOfWords::operator==(const BagOfWords& rhs) const {
	return this->wordMap == rhs.wordMap;
}

std::vector<std::string> BagOfWords::findUniqueWords() {
	std::vector<std::string> uniqueWords;

	for (auto it = wordMap.begin(); it != wordMap.end(); ++it) {
		uniqueWords.push_back(it->first);
	}
	return uniqueWords;
};

std::ostream& operator<<(std::ostream& os, const BagOfWords& review) {
	for (auto itr = review.wordMap.begin(); itr != review.wordMap.end(); ++itr) {
		std::cout << "Key: " << itr->first << " Value: " << itr->second << std::endl;
	}
	return os;
}