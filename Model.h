#pragma once
#include "BagOfWords.h"

#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <fstream>

const std::vector<std::string> stopWords{ "a", "an", "the", "it", "A", "An", "The", "It" };

class Model {
	const double CUTOFF_POSITIVE_VALUE = 0.5;
	const double ALPHA = 0.01;
	const int NUMBER_OF_EPOCHS = 13;
	const int CUTOFF_FOR_SIGNIFICANT_WORD = 5; //number of occurences for a word to be considered significant
	const double LAMBDA = 1;
	const bool SHOULD_REMOVE_STOPWORDS = true;

	std::vector<BagOfWords> reviews;
	std::map<std::string, bool> uniqueWords;
	std::vector<std::string> uniqueWordsList;
	std::vector<int> sentiments;
	std::vector<double> thetas;
	std::vector<double> gradients;
	std::vector<double> predictedActualDifferenceList;
	std::vector<double> means;
	std::vector<double> ranges;

	void gradientDescent(bool shouldPrintExtraInfo);
	double costFunction();
	double sigmoid(double number);
	double predictedValueCalculator(BagOfWords& review);
	double valueCalculator(BagOfWords& review);
	double costContributionByReview(BagOfWords& review, int sentiment);
	void predictedActualDifferenceListCalculator();
	double sumCalculatorForEachParamater(int paramater);
	void adjustThetas();
	void printExtraTrainingInfo(int epoch);
	bool wordIsSignificant(std::string word);
	void calculateMeans();
	void calculateRanges();
	bool wordIsAStopWord(std::string word);
public:
	Model();
	void initializeWithTrainingData(std::vector<BagOfWords>& reviews, std::vector<int>& sentiments);
	void findUniqueWords();
	void train(bool shouldPrintExtraInfo);
	int classify(BagOfWords& review);
	void usePreTrainedModel(std::string modelLocation);
	void saveModel(std::string saveLocation);
};