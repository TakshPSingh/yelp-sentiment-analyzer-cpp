#include "Input.h"

#include <iostream>

Input::Input() {}

void Input::fetchDataFromFile(std::string fileLocation) {
	std::cout << "Fetching reviews from file. This shouldn't take long." << std::endl;

	this->fileLocation = fileLocation;

	std::ifstream fin(this->fileLocation);
	aria::csv::CsvParser parser(fin); // parser library

	bool headerRow = true;

	for (auto& row : parser) {
		if (!headerRow) {
			if (row[COLUMN_NUMBER_RATING].empty()) // in case a row is blank
				continue;

			int rating = stoi(row[COLUMN_NUMBER_RATING]);
			std::string textReview = row[COLUMN_NUMBER_TEXT];

			int sentiment = 0;
			sentiment = (rating >= CUTOFF_FOR_POSITIVE_SENTIMENT) ? 1 : 0;

			sentiments.push_back(sentiment);
			textReviews.push_back(textReview);
		}
		else {
			headerRow = false;
		}
	}

	convertTextReviewsIntoBagOfWords();
}

std::vector<int>& Input::getSentiments() {
	return sentiments;
};

void Input::convertTextReviewsIntoBagOfWords() {
	for (std::string textReview : textReviews) {
		BagOfWords convertedReview(textReview);
		reviews.push_back(convertedReview);
	}
}

std::vector<BagOfWords>& Input::getReviews() {
	return reviews;
}