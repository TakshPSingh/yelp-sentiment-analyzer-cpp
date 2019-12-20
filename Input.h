#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "BagOfWords.h"

#include "parser.hpp"

const int COLUMN_NUMBER_RATING = 1;
const int COLUMN_NUMBER_TEXT = 2;
const int CUTOFF_FOR_POSITIVE_SENTIMENT = 4;

class Input {
	std::string fileLocation;
	std::vector<std::string> textReviews;
	std::vector<int> sentiments;
	std::vector<BagOfWords> reviews;
	void convertTextReviewsIntoBagOfWords();
public:
	Input();
	void fetchDataFromFile(std::string fileLocation);
	std::vector<int>& getSentiments();
	std::vector<BagOfWords>& getReviews();
};