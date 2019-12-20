#include "catch.hpp"

#include "../BagOfWords.h"

TEST_CASE("Constructor") {
	SECTION("Blank/meaningless reviews") {
		BagOfWords reviewBlank("");
		BagOfWords reviewOnlySpaces("  ");
		BagOfWords reviewNoAlphabets(".3.3...1#@#!@");

		REQUIRE(reviewBlank == reviewOnlySpaces);
		REQUIRE(reviewOnlySpaces == reviewNoAlphabets);
	}

	SECTION("Meaningful reviews") {
		BagOfWords reviewWithNoExtraSpaces("This place was great!");
		BagOfWords reviewWithNoPunctuations("  This place was great");
		BagOfWords reviewWithPunctuationsAndSpaces(" This   place   was great !!!!");

		REQUIRE(reviewWithNoExtraSpaces == reviewWithNoPunctuations);
		REQUIRE(reviewWithNoPunctuations == reviewWithPunctuationsAndSpaces);
	}
}

TEST_CASE("getNumberOfOccurencesOfWord function") {
	SECTION("Blank review") {
		BagOfWords review("");
		std::string word = "anyRandomWord";
		int numberOfOccurencesOfWord = review.getNumberOfOccurencesOfWord(word);

		REQUIRE(numberOfOccurencesOfWord == 0);
	}

	SECTION("One word review") {
		BagOfWords review(" randomWord ");

		std::string firstWord = "randomWord";
		std::string secondWord = "someOtherWord";

		int numberOfOccurenceOfFirstWord = review.getNumberOfOccurencesOfWord(firstWord);
		int numberOfOccurencesOfSecondWord = review.getNumberOfOccurencesOfWord(secondWord);

		REQUIRE(numberOfOccurenceOfFirstWord == 1);
		REQUIRE(numberOfOccurencesOfSecondWord == 0);
	}

	SECTION("Multi word review") {
		BagOfWords review("firstWord secondWord");

		std::string firstWord = "firstWord";
		std::string secondWord = "secondWord";
		std::string thirdWord = "someOtherWord";

		int numberOfOccurencesOfFirstWord = review.getNumberOfOccurencesOfWord(firstWord);
		int numberOfOccurencesOfSecondWord = review.getNumberOfOccurencesOfWord(secondWord);

		int numberOfOccurencesOfThirdWord = review.getNumberOfOccurencesOfWord(thirdWord);

		REQUIRE(numberOfOccurencesOfFirstWord == 1);
		REQUIRE(numberOfOccurencesOfSecondWord == 1);
		REQUIRE(numberOfOccurencesOfThirdWord == 0);
	}
}

TEST_CASE("findUniqueWords function") {
	SECTION("Blank review") {
		BagOfWords review("");
		std::vector<std::string> uniqueWordsList = review.findUniqueWords();

		REQUIRE(uniqueWordsList.empty());
	}

	SECTION("One word review") {
		BagOfWords review("word");

		std::vector<std::string> uniqueWordsListExpected{ "word" };
		std::vector<std::string> uniqueWordsListActual = review.findUniqueWords();

		REQUIRE(uniqueWordsListExpected == uniqueWordsListActual);
	}

	SECTION("Two word review with no repitions") {
		BagOfWords review("firstWord secondWord");

		std::vector<std::string> uniqueWordsListExpected{ "firstWord", "secondWord" };
		std::vector<std::string> uniqueWordsListActual = review.findUniqueWords();

		REQUIRE(uniqueWordsListExpected == uniqueWordsListActual);
	}

	SECTION("Two word review with repitions") {
		BagOfWords review("firstWord secondWord secondWord");

		std::vector<std::string> uniqueWordsListExpected{ "firstWord", "secondWord" };
		std::vector<std::string> uniqueWordsListActual = review.findUniqueWords();

		REQUIRE(uniqueWordsListExpected == uniqueWordsListActual);
	}
}