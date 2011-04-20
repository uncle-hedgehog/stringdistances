#include <string.h>
#include <stdio.h>

#include "stringdistances.h"

#define min3(a,b,c) (a < b ? (a < c ? a : c) : (b < c ? b : c))

int levenshtein ( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 )
{
	unsigned int d_tmp, d_new, i, j;
	unsigned int* d = (unsigned int*) malloc ( ( l1 + 1 ) * sizeof ( unsigned int ) );
	int res;

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

int levenshtein_damerau ( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 )
{
	// declaration of ALL variables prior to any other statements
	unsigned int i, j, len, *d, *d_current, *d_pre1, *d_pre2;
	int res;
	
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
