#include "ofMain.h"
#include "ofApp.h"

#include <iostream>
#include <string>
#include <fstream>

#include "../BagOfWords.h"
#include "../Input.h"
#include "../ModelAnalyzer.h"

void classifyCustomReview(Model& model);
void saveModel(Model& model);

// The only reason these 2 functions exist is because I need to use cin.ignore() only in the 2nd function
void handleTestingWithPreTrainedModel(Input& testingInput);
void handleTestingWithNewlyTrainedModel(Input& testingInput);

constexpr bool USE_GUI_TO_READ_CUSTOM_REVIEWS = false;

int main() {
	char usePreTrainedModel;
	std::cout << "Do you want to use a pre-trained model? (y/n) : ";
	std::cin >> usePreTrainedModel;

	Model sentimentPredictor;
	Input testingInput;

	if (usePreTrainedModel == 'Y' || usePreTrainedModel == 'y') {
		std::cout << "Let's use a pretrained model!" << std::endl;

		std::string savedModelLocation;
		std::cout << "Enter saved model location: ";
		std::cin.ignore();
		std::getline(std::cin, savedModelLocation);

		sentimentPredictor.usePreTrainedModel(savedModelLocation);
		handleTestingWithPreTrainedModel(testingInput);
	}
	else {
		std::cout << "Let's train a new model!" << std::endl;

		std::string trainingDataLocation;
		std::cout << "Enter training reviews location: ";
		std::cin.ignore();
		std::getline(std::cin, trainingDataLocation);

		char extraInfoPrompt;
		bool shouldPrintExtraInfo = false;

		std::cout << "Do you want extra infomation while the model is being trained? (y/n) : ";
		std::cin >> extraInfoPrompt;

		if (extraInfoPrompt == 'Y' || extraInfoPrompt == 'y') {
			shouldPrintExtraInfo = true;
		}

		Input trainingInput;
		trainingInput.fetchDataFromFile(trainingDataLocation);

		sentimentPredictor.initializeWithTrainingData(trainingInput.getReviews(), trainingInput.getSentiments());
		sentimentPredictor.train(shouldPrintExtraInfo);

		handleTestingWithNewlyTrainedModel(testingInput);
	}

	ModelAnalyzer sentimentAnalyzer(testingInput.getReviews(), testingInput.getSentiments(), &sentimentPredictor);
	sentimentAnalyzer.fetchPredictionsFromModel();
	sentimentAnalyzer.calculateConfusionMatrix();
	sentimentAnalyzer.analyze();
	//these 3 functions need to be called in this specific order

	classifyCustomReview(sentimentPredictor);

	char saveModelPrompt;
	std::cout << "Do you wish to save this model? (y/n) : ";
	std::cin >> saveModelPrompt;

	if (saveModelPrompt == 'Y' || saveModelPrompt == 'y') {
		saveModel(sentimentPredictor);
	}

	return 0;
}

void classifyCustomReview(Model& model) {
	std::cout << "Would you like to write a review and get it classified by our model? (y/n): ";
	char writeOwnReview;
	std::cin >> writeOwnReview;

	ofSetupOpenGL(8000, 8000, OF_WINDOW);

	std::string customReviewText;
	while (writeOwnReview == 'Y' || writeOwnReview == 'y') {
		std::string customReviewText = "";

		if (USE_GUI_TO_READ_CUSTOM_REVIEWS) {
			customReviewText = ofSystemTextBoxDialog("Enter your review here: ");
		}
		else {
			std::cout << "Enter your review (in the next line only) : " << std::endl;
			std::cin.ignore();
			std:getline(std::cin, customReviewText);
		}

		if (customReviewText == "")
			continue;

		BagOfWords customReview(customReviewText);
		int prediction = model.classify(customReview);
		std::string predictionInWords = (prediction == 1) ? "positive" : "negative";

		std::cout << "Your review is " << predictionInWords << std::endl;

		std::cout << "Want to write another review? (y/n): ";
		std::cin >> writeOwnReview;
	}
}

void saveModel(Model& model) {
	std::string modelSaveLocation;
	std::cout << "Enter location to save this model: ";

	std::cin.ignore();
	std::getline(std::cin, modelSaveLocation);

	model.saveModel(modelSaveLocation);
}

void handleTestingWithPreTrainedModel(Input& testingInput) {
	std::string testingDataLocation;

	std::cout << "Enter testing reviews location: ";
	std::getline(std::cin, testingDataLocation);

	testingInput.fetchDataFromFile(testingDataLocation);
}

void handleTestingWithNewlyTrainedModel(Input& testingInput) {
	std::string testingDataLocation;

	std::cout << "Enter testing reviews location: ";
	std::cin.ignore();
	std::getline(std::cin, testingDataLocation);

	testingInput.fetchDataFromFile(testingDataLocation);
}