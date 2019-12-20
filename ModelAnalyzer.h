#pragma once

#include "Model.h"

constexpr int NUMBER_OF_SENTIMENTS = 2;

class ModelAnalyzer {
	Model* model;
	std::vector<BagOfWords> testingReviews;
	std::vector<int> actualSentiments;
	std::vector<int> predictedSentiments;
	int confusionMatrix[NUMBER_OF_SENTIMENTS][NUMBER_OF_SENTIMENTS] = { 0 };
	double accuracy;
	double senstivity;
	double specificity;
	double precision;
public:
	ModelAnalyzer(std::vector<BagOfWords>& testingReviews, std::vector<int>& actualSentiments, Model* model);
	void fetchPredictionsFromModel();
	void calculateConfusionMatrix();
	void analyze();
	// these 4 functions need to be called in this specific order

	double getAccuracy();
	double getSenstivity();
	double getSpecificity();
	double getPrecision();
	// these 4 functions should only be called after the first 4 functions have been called
};