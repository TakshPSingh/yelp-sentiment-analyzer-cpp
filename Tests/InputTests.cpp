#include "catch.hpp"

#include "../Input.h"

TEST_CASE("fetcDataFromFile function") {
	SECTION("Blank reviews file") {
		Input reviewsInput;
		reviewsInput.fetchDataFromFile("blankReviews.csv");

		REQUIRE(reviewsInput.getReviews().empty());
		REQUIRE(reviewsInput.getSentiments().empty());
	}

	SECTION("Multiple reviews file") {
		Input reviewsInput;
		reviewsInput.fetchDataFromFile("multipleReviews.csv");

		std::vector<int> sentimentsExpected{ 1,1 };
		std::vector<int> sentimentsActual = reviewsInput.getSentiments();

		REQUIRE(sentimentsActual == sentimentsExpected);

		BagOfWords review1("review1");
		BagOfWords review2("review2");
		std::vector<BagOfWords> reviewsExpected{ review1, review2 };
		std::vector<BagOfWords> reviewsActual = reviewsInput.getReviews();

		REQUIRE(reviewsExpected == reviewsActual);
	}

	SECTION("Single review file") {
		Input reviewsInput;
		reviewsInput.fetchDataFromFile("singleReview.csv");

		std::vector<int> sentimentsExpected{ 1 };
		std::vector<int> sentimentsActual = reviewsInput.getSentiments();

		REQUIRE(sentimentsActual == sentimentsExpected);

		BagOfWords review1("review1");
		std::vector<BagOfWords> reviewsExpected{ review1 };
		std::vector<BagOfWords> reviewsActual = reviewsInput.getReviews();

		REQUIRE(reviewsExpected == reviewsActual);
	}
}