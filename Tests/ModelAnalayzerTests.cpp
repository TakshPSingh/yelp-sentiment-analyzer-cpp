#include "catch.hpp"

#include "../Input.h"
#include "../Model.h"
#include "../ModelAnalyzer.h"

const double BENCHMARK_ACCURACY = 0.70;

TEST_CASE("Benchmark accuracy") {
	std::string trainingDataLocation = "yelp_train.csv";
	std::string testingDataLocation = "yelp_test.csv";

	Input trainingInput;
	trainingInput.fetchDataFromFile(trainingDataLocation);

	Input testingInput;
	testingInput.fetchDataFromFile(testingDataLocation);

	bool shouldPrintExtraInfo = false;

	Model sentimentPredictor;
	sentimentPredictor.initializeWithTrainingData(trainingInput.getReviews(), trainingInput.getSentiments());
	sentimentPredictor.train(shouldPrintExtraInfo);

	ModelAnalyzer sentimentAnalyzer(testingInput.getReviews(), testingInput.getSentiments(), &sentimentPredictor);
	sentimentAnalyzer.fetchPredictionsFromModel();
	sentimentAnalyzer.calculateConfusionMatrix();
	sentimentAnalyzer.analyze();

	double accuracy = sentimentAnalyzer.getAccuracy();

	REQUIRE(accuracy >= BENCHMARK_ACCURACY);
}