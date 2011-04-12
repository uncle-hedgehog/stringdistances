#ifndef _STRING_DISTANCES_H_
#define _STRING_DISTANCES_H_

#include <stdlib.h>

int levenshtein ( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 );

int levenshtein_damerau ( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 );

#endif /* _STRING_DISTANCES_H_ */
