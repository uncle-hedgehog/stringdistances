#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>

#include <damerau.h>
#include <levenshtein.h>

#define min3(a,b,c) (a < b ? (a < c ? a : c) : (b < c ? b : c))
#define TBL_SZ (8*sizeof(UINT64))
//#define OPTIMIZE4ASCII

typedef unsigned long long UINT64;

int damerau( const wchar_t* w1, const wchar_t* w2 ) {
	return damerau_len( w1, wcslen( w1 ), w2, wcslen( w2 ) );
}

int damerau_len( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 ) {
	return ( l1 < 8 * sizeof(UINT64) || l2 < 8 * sizeof(UINT64) )
		 ? damerau_bits( w1, l1, w2, l2 ) 
		 : damerau_matrix( w1, l1, w2, l2 );
}

// hash value for the pattern matcher
struct hashVal {
        wchar_t key;
        UINT64 value;
};

int damerau_bits( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 ) {

	// pattern match vectors
#ifdef OPTIMIZE4ASCII
	UINT64 PMV[ 128 ] = {0};
#endif
	struct hashVal PMH[ TBL_SZ ] = {{L'\0',0}};

        // vertical positive, vertical negative, horizontal positive, horizontal negative, diagonal zero and pattern match bit-vectors
        UINT64 VP = -1;
        UINT64 VN = 0;
        UINT64 PM = 0;
        UINT64 HP, HN, D; //, PM;
        size_t i, j;

        /// second string should be biggest
        const wchar_t* tmp;
        if ( l1 > l2 ) { tmp = w1; w1 = w2; w2 = tmp; i = l1; l1 = l2; l2 = i;  }

        /// ignore common prefixes
        for ( ; l1 && *w1 == *w2; ++w1, ++w2, --l1, --l2 ) {}

        /// ignore common suffixes 
        for ( ; l1 & l2 && w1[l1-1] == w2[l2-1]; --l1, --l2 ) {}

        /// return length of longer string if shorter string is empty
        if ( ! l1 ) return l2;
        if ( ! l2 ) return l1;

        /// build pattern match vector and pattern match hash (for non-ascii)
        for ( j = 0; j < l2; ++j ) {
#ifdef OPTIMIZE4ASCII
		if( w2[j] < 128 ) PMV[ w2[j] ] |=  (UINT64)1 << j;
		else {
#endif
                        for ( i = 0; PMH[ (w2[j] + i) % TBL_SZ ].key != L'\0' && PMH[ (w2[j] + i) % TBL_SZ ].key != w2[j]; ++i ) {
			}
                        PMH[ (w2[j] + i) % TBL_SZ ].key = w2[j];
                        PMH[ (w2[j] + i) % TBL_SZ ].value |= (UINT64)1 << j;
#ifdef OPTIMIZE4ASCII
		}
#endif
        }

        /// actual distance computation 
        for ( i = 0; i < l1; ++i ) {
#ifdef OPTIMIZE4ASCII
                if ( w1[i] < 128 ) {
                		D = (((~D) & PMV[w1[i]]) << 1) & PM;
                		D = D | (((PMV[w1[i]] & VP) + VP) ^ VP ) | PMV[w1[i]] | VN;
                	PM = PMV[w1[i]];
		}
		else {
#endif
                        for ( j = 0; PMH[ (w1[i] + j) % TBL_SZ ].key != L'\0' && PMH[ (w1[i] + j) % TBL_SZ ].key != w1[i]; ++j ) {}
                	D = (((~D) & PMH[(w1[i]+j)%TBL_SZ ].value) << 1) & PM;
                	D = D | (((PMH[(w1[i]+j)%TBL_SZ ].value & VP) + VP) ^ VP ) | PMH[(w1[i]+j)%TBL_SZ ].value | VN;
                	PM = PMH[(w1[i]+j)%TBL_SZ ].value;
#ifdef OPTIMIZE4ASCII
                }
#endif
                HP = VN | ~( D | VP );
                HN = D & VP;
                VP = ( HN << 1 ) | ~( D | (( HP << 1 ) | 1 )  );
                VN = D & ( ( HP << 1 ) | 1 );
        }

        /// sum up result
        for ( j = 0; j < l2; ++j ) {
                l1 += ( VP & 1 ) - ( VN & 1 );
                VP >>= 1;
                VN >>= 1;
        }

        return l1;
}

int damerau_matrix( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 ) {
        unsigned int i, j, len, *d, *d_current, *d_pre1, *d_pre2;
        int res;

        if ( ! l1 ) return l2;
        else if ( ! l2 ) return l1;
        else if ( l1 == 1 || l2 == 1 ) return levenshtein_matrix( w1, l1, w2, l2 );
        
        len = l1 + 1;
        d = (unsigned int*) malloc ( 3 * len * sizeof ( unsigned int ) );
        for ( i = 0; i <= l1; ++i )
        {
                d[i] = i;
        }
        d[len] = 1;
        for ( i = 1; i <= l1; ++i )
        {
                d[i+len] = min3 ( d[i+len-1] + 1, d[i-1] + (w1[i-1] != w2[0]), d[i] + 1 );
        }
        for ( j = 2; j <= l2; ++j ) {
                switch( j % 3 ) {
                        case 0: d_current = d; d_pre2 = d_current + len; d_pre1 = d_pre2 + len; break;
                        case 1: d_pre1 = d; d_current = d_pre1 + len; d_pre2 = d_current + len; break;
                        case 2: d_pre2 = d; d_pre1 = d_pre2 + len; d_current = d_pre1 + len; break;
                }
                d_current[0] = d_pre1[0]+1;
                d_current[1] = min3( d_current[0] + 1, d_pre1[0] + (w1[0] != w2[j-1]), d_pre1[1] + 1 );
                for ( i = 2; i <= l1; ++i ) {
                        d_current[i] = min3( d_current[i-1] + 1, d_pre1[i-1] + (w1[i-1] != w2[j-1]), d_pre1[i] + 1 );
                        if ( w1[i-1] == w2[j-2] && w1[i-2] == w2[j-1] && d_current[i] > d_pre2[i-2]+1 ) d_current[i] = d_pre2[i-2]+1; 
                }
        }
        res = d_current[l1];
        free ( d );
        return res;
}

