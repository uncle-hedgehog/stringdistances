#include "stringdistances.h"
#include <gtest/gtest.h>

/*
TEST( LevenshteinDamerau, two_strings_are_empty ) {
	EXPECT_EQ( 0, levenshtein_damerau( L"", L"" ) );
}
TEST( LevenshteinDamerau, one_string_is_empty ) {
	EXPECT_EQ( 1, levenshtein_damerau( L"", L"a" ) );
	EXPECT_EQ( 1, levenshtein_damerau( L"a", L"" ) );
	EXPECT_EQ( 4, levenshtein_damerau( L"", L"aaaa" ) );
	EXPECT_EQ( 4, levenshtein( L"aaaa", L"" ) );
}
TEST( LevenshteinDamerau, two_equal_strings ) {
	EXPECT_EQ( 0, levenshtein_damerau( L"a", L"a" ) );
	EXPECT_EQ( 0, levenshtein_damerau( L"aaaa", L"aaaa" ) );
}
TEST( LevenshteinDamerau, character_exchange ) {
	EXPECT_EQ( 1, levenshtein_damerau( L"ab", L"ba" ) );
	EXPECT_EQ( 2, levenshtein_damerau( L"abba", L"baab" ) );
	EXPECT_EQ( 2, levenshtein_damerau( L"aba", L"bab" ) );
}
TEST( LevenshteinDamerau, insert_or_delete ) {
	EXPECT_EQ( 1, levenshtein_damerau( L"aba", L"aa" ) );
	EXPECT_EQ( 1, levenshtein_damerau( L"aa", L"aba" ) );
}
TEST( LevenshteinDamerau, insert_and_delete ) {
	EXPECT_EQ( 7, levenshtein_damerau( L"aaaabbbb", L"bbbbaaaa" ) );
	EXPECT_EQ( 6, levenshtein_damerau( L"aaabbbb", L"bbbbaaa" ) );
	EXPECT_EQ( 2, levenshtein_damerau( L"aabb", L"aacc" ) );
	EXPECT_EQ( 2, levenshtein_damerau( L"bbaa", L"ccaa" ) );
	EXPECT_EQ( 2, levenshtein_damerau( L"ac", L"cba" ) );
}
*/
