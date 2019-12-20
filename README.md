# Yelp Review Sentiment Analysis using Logistic Regression in C++

### About:

This classifier reads yelp reviews from CSV files and uses logistic regression to classify them as postive or negative.

### System requirements:

- This project is fully compatible with the Windows version of Visual Studio 2019.
- I expect this to be also compatible with other Windows versions of Visual Studio.
- This should be compatible with Linux and MacOS versions of Visual Studio after making a few minor changes.
- If anyone is able to run this on Linux or MacOS, I would request you to create a pull request so that I can integrate your changes in this repo.

### How to use the classifier?

- The yelp reviews should be stored in a CSV file. You will need to edit the Input.h file to specify which row of your CSV files corresponds to the textual content of your reviews and which row corresponds to the ratings of your reviews.
- That's all you need to do!

Extra: You can also modify the value of alpha, the number of epochs, the value of lambda (for regularization) and other parameters in the Model.h file.

### How does the classifier work?

The classifier uses a logistic regression model which is trained using the batch gradient descent algorithm.
The model also uses additional features to optimize the gradient descent algorithm such as:

1) Normalization
2) Regularization
3) Removal of "insignificant words" (words that appear only a few numbers of times)
4) Removal of [stopwords](https://en.wikipedia.org/wiki/Stop_words)

All these additional features can be disabled/enabled or modified by making changes to the Model.h file.