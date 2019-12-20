#include "ModelAnalyzer.h"

ModelAnalyzer::ModelAnalyzer(std::vector<BagOfWords>& testingReviews, std::vector<int>& actualSentiments, Model* model) {
	this->testingReviews = testingReviews;
	this->actualSentiments = actualSentiments;
	this->model = model;
}

void ModelAnalyzer::fetchPredictionsFromModel() {
	for (BagOfWords& review : testingReviews) {
		int prediction = model->classify(review);
		predictedSentiments.push_back(prediction);
	}
}

void ModelAnalyzer::calculateConfusionMatrix() {
	for (int index = 0; index < actualSentiments.size(); ++index) {
		int actualSentiment = actualSentiments[index];
		int predictedSentiment = predictedSentiments[index];
		++confusionMatrix[predictedSentiment][actualSentiment];
	}
}

void ModelAnalyzer::analyze() {
	int TP = confusionMatrix[1][1]; // predicted sentiment = +ve and actual sentiment = +ve
	int TN = confusionMatrix[0][0]; // predicted sentiment = -ve and actual sentiment = -ve
	int FP = confusionMatrix[1][0]; // predicted sentiment = +ve and actual sentiment = -ve
	int FN = confusionMatrix[0][1]; // predicted sentiment = -ve and actual sentiment = +ve

	accuracy = (TP + TN) / (double)(TP + TN + FP + FN);
	senstivity = TP / (double)(TP + FN);
	specificity = TN / (double)(TN + FP);
	precision = TP / (double)(TP + FP);

	std::cout << "Accuracy (% of reviews classifed correctly): " << accuracy * 100 << " %" << std::endl;
	std::cout << "Sensitivity (% of positive reviews classfied correctly): " << senstivity * 100 << " %" << std::endl;
	std::cout << "Specificity (% of negative reviews classfied correctly): " << specificity * 100 << " %" << std::endl;
	std::cout << "Precision (% of reviews classified as positive that were actually positive): " << precision * 100 << " %" << std::endl;
}

double ModelAnalyzer::getAccuracy() {
	return accuracy;
}

double ModelAnalyzer::getSenstivity() {
	return senstivity;
}

double ModelAnalyzer::getSpecificity() {
	return specificity;
}

double ModelAnalyzer::getPrecision() {
	return precision;
}