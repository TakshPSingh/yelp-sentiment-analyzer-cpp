**November 19, 2019:** Added basic project structure:
- Added BagOfWords class and created a seperate project for testing

**November 20, 2019:** Added helper functions for the BagOfWords class and Model class:
- Still need to handle edge cases in the function that converts text reviews into a bag of words model

**November 21, 2019:** Created the main function, Added CSV parser, Added catch2, deleted the old testing project:
- Deleted Google Test
- Added Catch2
- Added CSV parsing library
- Added Input class
- Wrote helper functions for input class
- deleted old testing project
- moved test files to the main project

- Still need to integrate Catch2 with Visual Studio

**November 25, 2019:** Replaced old CSV parser library with new one and tested everything manually

**November 26, 2019:** Implemented gradient descent algorithm and cost function calculator.
- Also added many helper functions for the regression model.

**November 27, 2019:**
- Debugged gradient descent algorithm and the cost function calculator
- Trained algorithm with different input sizes, values of alpha and number of epochs
- Changed structure so that Input class passes BagOfWords reviews instead of text reviews
- Added ModelAnalyzer class
- Encountering multiple errors with the ModelAnalyzer class, need to figure this out tomorrow

**November 29, 2019:**
- I realized that my model was suboptimal.
- I tried different values of alpha and number of epochs and realized that I need to use one of the follwing strategies (or a combination of one or more of them) to optimize my algorithm:
1) Normalize hyperparameters
2) Regularization
3) Finding the optimal values of alpha and number of epochs
- Also started removing "insignificant" words that appeared only a few times in my training dataset.
- This reduced the computational power required to train my model, thus enabling me to use larger datasets.

**December 2, 2019**
- Optimized algorithm using normalization
- Made minor structural changes to the project
- Added helper functions to complete the ModelAnalyzer class
- Removed a few redunandant constructors

**December 3, 2019**
- Added regulatization to optimize the algorithm further
- Added the ability to remove stopwords
- Tried different values of alpha and the number of epochs to increase the accuracy of my model.

**December 6, 2019**
- Wrote README.md
- Added option for the user to disable the removal of stopwords

**December 7, 2019**
- Fixed bug that in the calculateMeans functions
- Tried different values of alpha, the number of epochs and lambda to optimize my algorithm

**December 8, 2019**
- Added openFrameworks
- Added ability to read custom reviews using GUI
- Project completed!