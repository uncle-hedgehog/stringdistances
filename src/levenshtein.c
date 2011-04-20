#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>

#include <levenshtein.h>

#define min3(a,b,c) (a < b ? (a < c ? a : c) : (b < c ? b : c))

typedef unsigned long long UINT64;

// pattern match vector
static UINT64 PMV[ 256 ] = {0};

// pattern match hash
struct hashVal {
        wchar_t key;
        UINT64 value;
} PMH[256] = {{L'\0',0}};

// myers bit parallelism algorithm. one string has to be shorter than sizeof(unsigned long long).
int levenshtein_myers( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 );

// dynamic programming matrix. classical algorithm.
int levenshtein_matrix( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 );

int levenshtein( const wchar_t* w1, const wchar_t* w2 ) {
	return levenshtein_len( w1, wcslen( w1 ), w2, wcslen( w2 ) );
}

int levenshtein_len( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 ) {
	return ( l1 < 8 * sizeof(UINT64) || l2 < 8 * sizeof(UINT64) )
		 ? levenshtein_myers( w1, l1, w2, l2 ) 
		 : levenshtein_matrix( w1, l1, w2, l2 );
}



int levenshtein_myers( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 ) {
        // vertical positive, vertical negative, horizontal positive, horizontal negative, diagonal zero and pattern match bit-vectors
        UINT64 VP = -1;
        UINT64 VN = 0;
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

        /// build pattern match vector and pattern match hash (for non-ascii)
        for ( j = 0; j < l2; ++j ) {
                if( w2[j] < 256 ) PMV[ w2[j] ] |=  (UINT64)1 << j;
                else {
                        for ( i = 0; PMH[ (w2[j] + i) % 256 ].key != L'\0' && PMH[ (w2[j] + i) % 256 ].key != w2[j]; ++i ) {
			}
                        PMH[ (w2[j] + i) % 256 ].key = w2[j];
                        PMH[ (w2[j] + i) % 256 ].value |= (UINT64)1 << j;
		}
        }
        /// actual distance computation 
        for ( i = 0; i < l1; ++i ) {
                if ( w1[i] > 256 ) {
                        for ( j = 0; PMH[ (w1[i] + j) % 256 ].key != L'\0' && PMH[ (w1[i] + j) % 256 ].key != w1[i]; ++i ) {}
                        D = (((( PMH[ (w1[i] + j) % 256 ].value & VP ) + VP )) ^ VP) | PMH[ (w1[i] + j) % 256 ].value | VN;
                }
                else {
                        D = (((( PMV[ w1[i] % 256 ] & VP ) + VP )) ^ VP ) | PMV[ w1[i] % 256 ] | VN;
                }
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
        /// clean up pattern match vector and hash
        for ( j = 0; j < l2; ++j ) {
                if( w2[j] < 256 ) PMV[ w2[j] ] = 0;
                else {
                        for ( i = 0; PMH[ (w2[j] + i) % 256 ].key != w2[j]; ++i ) {}
                        PMH[ (w2[j] + i) % 256 ].key = L'\0';
                        PMH[ (w2[j] + i) % 256 ].value = 0;
                }
        }
        return l1;
}

int levenshtein_matrix( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 ) {
        unsigned int d_tmp, d_new, i, j;
        unsigned int* d = (unsigned int*) malloc ( ( l1 + 1 ) * sizeof ( unsigned int ) );
        int res;

        if ( ! l1 ) return l2;
        if ( ! l2 ) return l1;

        for ( i = 0; i <= l1; ++i ) { d[i] = i; }
        for ( j = 1; j <= l2; ++j ) {
                d_tmp = d[0]++;
                for ( i = 1; i <= l1; ++i ) {
                        d_new = min3 ( d[i-1] + 1, d_tmp + ( w1[i-1] != w2[j-1] ), d[i] + 1 );
                        d_tmp = d[i];
                        d[i] = d_new;
                }
        }
        res = d[l1];
        free ( d );
        return res;
}
