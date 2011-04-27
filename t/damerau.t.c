extern "C" {
#include "damerau.h"
}
#include <gtest/gtest.h>

TEST( Damerau, two_strings_are_empty ) {
	EXPECT_EQ( 0, damerau( L"", L"" ) );
}
TEST( Damerau, one_string_is_empty ) {
	EXPECT_EQ( 1, damerau( L"", L"a" ) );
	EXPECT_EQ( 1, damerau( L"a", L"" ) );
	EXPECT_EQ( 4, damerau( L"", L"aaaa" ) );
	EXPECT_EQ( 4, damerau( L"aaaa", L"" ) );
}
TEST( Damerau, two_equal_strings ) {
	EXPECT_EQ( 0, damerau( L"a", L"a" ) );
	EXPECT_EQ( 0, damerau( L"aaaa", L"aaaa" ) );
}
TEST( Damerau, character_exchange ) {
	EXPECT_EQ( 1, damerau( L"ab", L"ba" ) );
	EXPECT_EQ( 2, damerau( L"abba", L"baab" ) );
	EXPECT_EQ( 2, damerau( L"aba", L"bab" ) );
}
TEST( Damerau, insert_or_delete ) {
	EXPECT_EQ( 1, damerau( L"aba", L"aa" ) );
	EXPECT_EQ( 1, damerau( L"aa", L"aba" ) );
}
TEST( Damerau, insert_and_delete ) {
	EXPECT_EQ( 7, damerau( L"aaaabbbb", L"bbbbaaaa" ) );
	EXPECT_EQ( 6, damerau( L"aaabbbb", L"bbbbaaa" ) );
	EXPECT_EQ( 2, damerau( L"aabb", L"aacc" ) );
	EXPECT_EQ( 2, damerau( L"bbaa", L"ccaa" ) );
	EXPECT_EQ( 3, damerau( L"ac", L"cba" ) );
}
TEST( Levenshtein, non_ascii ) {
	EXPECT_EQ( 0, damerau( L"ä", L"ä" ) );
	EXPECT_EQ( 4, damerau( L"ﹰﺗﺺ", L"豈朗歷ﹰﺗﺺ館" ) );	
	EXPECT_EQ( 4, damerau( L"ﹰ朗ﺗﺺ", L"豈朗歷ﹰﺗﺺ館" ) );	
}
