#include <wchar.h>
#include <stdlib.h>
#include <string.h>

#include <jaccard.h>

// hash value for the pattern matcher
struct hashVal {
        wchar_t* key;
        int value;
};
unsigned int hash( wchar_t* w, unsigned int n ) {
	unsigned int v = 0;
	unsigned int i = 0;
	for ( ; i < n && w[i] != '\0'; ++i ) {
		v = (v * 31) + w[i];
	}
	return v;
}

// jaccard distance of two strings with given n-gram width
int jaccard( const wchar_t* w1, const wchar_t* w2, unsigned int n ) {
}

// jaccard distance of two strings with given lengths and given n-gram width
int jaccard_len( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2, unsigned int n ) {
	int tbl_sz = (l1 + l2) * 2;
	int i, intersection_sz, difference_sz;
	int union_sz = 0;
	struct hashVal H[ tbl_sz ] = {{(wchar_t*)0,0}};
	for ( i = 0; i < l1; ++i ) {
		for ( j = hash(w1+i); H[j%tbl_sz].key != 0 && ! strncmp( H[j%tbl_sz].key, w1+i, n ); ++j ) {}
		if ( ! H[j%tbl_sz].value & 1 ) {
			H[ j % tbl_sz ].key = w1[i];
			H[ j % tbl_sz ].matches &= 1;
			++union_sz;
		}
	} 
	difference_sz = union_sz;
	intersection_sz = 0;
	for ( i = 0; i < l2; ++i ) {
		for ( j = hash(w2+i); H[j%tbl_sz].key != 0 && ! strncmp( H[j%tbl_sz].key, w2+i, n ); ++j ) {}
		if ( ! H[j%tbl_sz].value & 2 ) {
			H[ j % tbl_sz ].matches &= 2;
			if ( H[j%tbl_sz].value & 1 ) {
				--difference_sz;
				++intersection_sz;
			}
			else {
				H[ j % tbl_sz ].key = w2[i];
				++union_sz;
			}
		}
	} 
/*
print 'jaccard similarity coefficient or jaccard index: ', len(intersection)/float(len(union))
print 'jaccard distance: ', (len(union)-len(intersection))/float(len(union))
print 'jaccard distance:', 1-(len(intersection)/float(len(union)))
print 'dice coefficient: ', 2*(len(intersection))/float(len(union))
*/
}

	

