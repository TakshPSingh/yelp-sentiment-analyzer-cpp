#include "Model.h"

Model::Model() {}

void Model::initializeWithTrainingData(std::vector<BagOfWords>& reviews, std::vector<int>& sentiments) {
	this->reviews = reviews;
	this->sentiments = sentiments;

	findUniqueWords();
}

void Model::findUniqueWords() {
	std::cout << "Preprocessing reviews. This shouldn't take long." << std::endl;

	for (BagOfWords review : reviews) {
		for (std::string word : review.findUniqueWords()) {
			uniqueWords[word] = true;
		}
	}

	uniqueWordsList.push_back(""); // for bias unit case so that indexing of words begins at 1
	for (auto itr : uniqueWords) {
		std::string word = itr.first;

		bool wordSignificant = wordIsSignificant(word);
		bool wordStopWord = wordIsAStopWord(word);

		if (SHOULD_REMOVE_STOPWORDS && wordSignificant && !wordStopWord) {
			uniqueWordsList.push_back(word);
		}
		else if (!SHOULD_REMOVE_STOPWORDS && wordSignificant) {
			uniqueWordsList.push_back(word);
		}
	}
}

bool Model::wordIsSignificant(std::string word) {
	int numberOfOccurences = 0;
	for (BagOfWords& review : reviews) {
		numberOfOccurences += review.getNumberOfOccurencesOfWord(word);
	}
	return numberOfOccurences >= CUTOFF_FOR_SIGNIFICANT_WORD;
}

void Model::train(bool shouldPrintExtraInfo) {
	std::cout << "Training model. This might take a while." << std::endl;

	for (int count = 0; count < uniqueWordsList.size(); ++count) {
		thetas.push_back(0);
		gradients.push_back(0);
	}

	// Normalization =>
	calculateMeans();
	calculateRanges();

	gradientDescent(shouldPrintExtraInfo);

	std::cout << "Model trained :)" << std::endl;
}

double Model::sigmoid(double number) {
	return 1.0 / (1 + exp(-1 * number));
}

double Model::valueCalculator(BagOfWords& review) {
	double value = 0;
	value += thetas[0] * 1; // Adding value contributed by bias unit

	for (int index = 1; index < uniqueWordsList.size(); ++index) {
		std::string word = uniqueWordsList[index];
		double numberOfOccurencesOfWordInReview = review.getNumberOfOccurencesOfWord(word);

		double numberOfOccurencesOfWordInReviewNormalized = (numberOfOccurencesOfWordInReview - means[index]) / ranges[index];

		value += thetas[index] * numberOfOccurencesOfWordInReviewNormalized; // analogous to theta(i) * x(i)
	}
	return value;
}

double Model::predictedValueCalculator(BagOfWords& review) {
	double value = valueCalculator(review);
	return sigmoid(value);
}

double Model::costContributionByReview(BagOfWords& review, int sentiment) {
	// Using regression cost function formula:

	double predictedValue = predictedValueCalculator(review);

	double costIfPositive = -1 * sentiment * log(predictedValue);
	double costIfNegative = -1 * (1 - sentiment) * log(1 - predictedValue);

	double costContribution = (sentiment == 1) ? costIfPositive : costIfNegative;
	return costContribution;
}

double Model::costFunction() {
	double totalCost = 0;
	double numberOfReviews = reviews.size();

	for (int index = 0; index < reviews.size(); ++index) {
		totalCost += costContributionByReview(reviews[index], sentiments[index]);
	}

	for (int parameter = 1; parameter < thetas.size(); ++parameter) { //regularization
		totalCost += LAMBDA * thetas[parameter] * thetas[parameter];
	} //fix this

	return totalCost / (2 * numberOfReviews);

	//formula of cost function in logisitic regression
}

void Model::predictedActualDifferenceListCalculator() {
	predictedActualDifferenceList.clear();

	for (int index = 0; index < reviews.size(); ++index) {
		double difference = predictedValueCalculator(reviews[index]) - sentiments[index];
		predictedActualDifferenceList.push_back(difference);
	}
	//analogous to h(x) - y for all training samples 
}

void Model::gradientDescent(bool shouldPrintExtraInfo) {
	//Batch gradient descent algorithm =>

	for (int epoch = 1; epoch <= NUMBER_OF_EPOCHS; ++epoch) {
		adjustThetas();

		if (shouldPrintExtraInfo) {
			printExtraTrainingInfo(epoch);
		}
	}
}

void Model::adjustThetas() {
	//Adjust thetas for a single iteratation of gradient descent =>
	predictedActualDifferenceListCalculator();

	double sum = std::accumulate(predictedActualDifferenceList.begin(), predictedActualDifferenceList.end(), 0);
	// for parameter theta 0 because x(i) sub 0 = 1 for all training samples

	thetas[0] -= ALPHA * sum;

	for (int parameter = 1; parameter < thetas.size(); ++parameter) {
		sum = sumCalculatorForEachParamater(parameter);
		sum += (LAMBDA / reviews.size()) * thetas[parameter];
		thetas[parameter] -= ALPHA * sum;
	}
}

double Model::sumCalculatorForEachParamater(int parameter) {
	std::string word = uniqueWordsList[parameter];
	double sum = 0;

	for (int index = 0; index < predictedActualDifferenceList.size(); ++index) {
		BagOfWords& review = reviews[index];

		double numberOfOccurencesOfWord = review.getNumberOfOccurencesOfWord(word);
		double numberOfOccurencesOfWordNormalized = (numberOfOccurencesOfWord - means[parameter]) / ranges[parameter]; //

		sum += predictedActualDifferenceList[index] * numberOfOccurencesOfWordNormalized;
	}

	return sum;
}

void Model::printExtraTrainingInfo(int epoch) {
	std::cout << "Epoch " << epoch << std::endl;
	std::cout << "Cost: " << costFunction() << std::endl;
}

int Model::classify(BagOfWords& review) {
	double predictedValue = predictedValueCalculator(review);
	return (predictedValue >= CUTOFF_POSITIVE_VALUE) ? 1 : 0;
}

void Model::calculateMeans() {
	means.push_back(0); //for theta sub 0

	for (int index = 1; index < uniqueWordsList.size(); ++index) {
		std::string word = uniqueWordsList[index];

		double sum = 0;
		for (BagOfWords& review : reviews) {
			sum += review.getNumberOfOccurencesOfWord(word);
		}
		double mean = sum / reviews.size();
		means.push_back(mean);
	}
}

void Model::calculateRanges() {
	ranges.push_back(1); // for theta sub 0

	for (int index = 1; index < uniqueWordsList.size(); ++index) {
		std::string word = uniqueWordsList[index];

		double minNumberOfOccurences = DBL_MAX;
		double maxNumberOfOccurences = DBL_MIN;

		for (BagOfWords& review : reviews) {
			double numberOfOccurences = review.getNumberOfOccurencesOfWord(word);
			minNumberOfOccurences = std::min(minNumberOfOccurences, numberOfOccurences);
			maxNumberOfOccurences = std::max(maxNumberOfOccurences, numberOfOccurences);
		}

		double range = maxNumberOfOccurences - minNumberOfOccurences;
		range = (range >= 1) ? range : 1; //to ensure that range != 0

		ranges.push_back(range);
	}
}

bool Model::wordIsAStopWord(std::string word) {
	for (std::string stopWord : stopWords) {
		if (word == stopWord)
			return true;
	}
	return false;
}

void Model::usePreTrainedModel(std::string modelLocation) {
	std::cout << "Reading pretrained model from file. This shouldn't take long" << std::endl;

	std::ifstream fin(modelLocation);

	if (!fin.good())
		throw std::runtime_error("Something is wrong with the input stream");

	int numberOfParameters;
	fin >> numberOfParameters;
	fin.ignore();
	
	for (int index = 0; index < numberOfParameters; ++index) {
		std::string word;
		std::getline(fin, word);
		uniqueWordsList.push_back(word);
	}

	for (int index = 0; index < numberOfParameters; ++index) {
		double theta;
		fin >> theta;
		thetas.push_back(theta);
	}

	for (int index = 0; index < numberOfParameters; ++index) {
		double mean;
		fin >> mean;
		means.push_back(mean);
	}

	for (int index = 0; index < numberOfParameters; ++index) {
		double range;
		fin >> range;
		ranges.push_back(range);
	}

	fin.close();
}

void Model::saveModel(std::string saveLocation) {
	std::cout << "Saving model. This shouldn't take long." << std::endl;

	std::ofstream fout(saveLocation);

	if (!fout.good())
		throw std::runtime_error("Something is wrong with the output stream");

	fout << thetas.size() << std::endl; //number of parameters

	for (std::string word : uniqueWordsList)
		fout << word << std::endl;
	for (double theta : thetas)
		fout << theta << std::endl;
	for (double mean : means)
		fout << mean << std::endl;
	for (double range : ranges)
		fout << range << std::endl;

	fout.close();
}