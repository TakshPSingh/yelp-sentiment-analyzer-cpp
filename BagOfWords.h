#pragma once

#include <map>
#include <vector>
#include <string>
#include <algorithm>

class BagOfWords {
	std::map<std::string, int> wordMap;
public:
	BagOfWords(std::string review);
	int getNumberOfOccurencesOfWord(std::string word);
	std::vector<std::string> findUniqueWords();

	bool operator==(const BagOfWords& rhs) const;
	friend std::ostream& operator<<(std::ostream& os, const BagOfWords& review);
};