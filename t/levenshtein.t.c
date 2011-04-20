extern "C" {
#include "levenshtein.h"
}
#include <gtest/gtest.h>

TEST( Levenshtein, two_strings_are_empty ) {
	EXPECT_EQ( 0, levenshtein( L"", L"" ) );
}
TEST( Levenshtein, one_string_is_empty ) {
	EXPECT_EQ( 1, levenshtein( L"", L"a" ) );
	EXPECT_EQ( 1, levenshtein( L"a", L"" ) );
	EXPECT_EQ( 4, levenshtein( L"", L"aaaa" ) );
	EXPECT_EQ( 4, levenshtein( L"aaaa", L"" ) );
}
TEST( Levenshtein, two_equal_strings ) {
	EXPECT_EQ( 0, levenshtein( L"a", L"a" ) );
	EXPECT_EQ( 0, levenshtein( L"aaaa", L"aaaa" ) );
}
TEST( Levenshtein, substitute ) {
	EXPECT_EQ( 1, levenshtein( L"a", L"b" ) );
	EXPECT_EQ( 4, levenshtein( L"aaaaa", L"abbbb" ) );
}
TEST( Levenshtein, insert_or_delete ) {
	EXPECT_EQ( 1, levenshtein( L"a", L"ab" ) );
	EXPECT_EQ( 1, levenshtein( L"ab", L"a" ) );
	EXPECT_EQ( 1, levenshtein( L"a", L"ba" ) );
	EXPECT_EQ( 1, levenshtein( L"ba", L"a" ) );
	EXPECT_EQ( 1, levenshtein( L"aba", L"aa" ) );
	EXPECT_EQ( 1, levenshtein( L"aa", L"aba" ) );
}
TEST( Levenshtein, insert_and_delete ) {
	EXPECT_EQ( 8, levenshtein( L"aaaabbbb", L"bbbbaaaa" ) );
	EXPECT_EQ( 6, levenshtein( L"aaabbbb", L"bbbbaaa" ) );
	EXPECT_EQ( 2, levenshtein( L"aabb", L"aacc" ) );
	EXPECT_EQ( 2, levenshtein( L"bbaa", L"ccaa" ) );
}
TEST( Levenshtein, non_ascii ) {
	EXPECT_EQ( 0, levenshtein( L"ä", L"ä" ) );
	EXPECT_EQ( 4, levenshtein( L"ﹰﺗﺺ", L"豈朗歷ﹰﺗﺺ館" ) );	
}
