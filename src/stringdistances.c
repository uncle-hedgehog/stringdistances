#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <R.h>


#define min2(a,b) (a < b ? a : b)
#define min3(a,b,c) (a < b ? (a < c ? a : c) : (b < c ? b : c))

int levenshtein_internal ( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 );

int levenshtein_damerau_internal ( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 );

void levenshtein_damerau ( char ** strvec_1, char ** strvec_2, int * length_1, int * length_2, int * ans );

// Yes, I have tested the code.
/*
int main (  )
{
	char* test1 = "Täst";
	char* test2 = "Tsät";
	char* test_vec1[2];
	char* test_vec2[2];
	int values[2];
	int l1 = 2, l2 = 2;

	test_vec1[0] = test1;
	test_vec1[1] = test2;

	test_vec2[1] = test1;
	test_vec2[0] = test2;

	levenshtein_damerau ( test_vec1, test_vec2, &l1, &l2, values );

	for ( ; l1 > 0; --l1 )
	{
		printf ( "%i\n", values[l1 - 1] );
	}

	return 0;
}
*/

void levenshtein_damerau ( char ** strvec_1, char ** strvec_2, int * length_1, int * length_2, int * ans )
{
	int max_length= *length_1 > *length_2 ? *length_1 : *length_2;  
	int str_ind;
	for ( str_ind=0; str_ind < max_length; ++str_ind )
	{
		// declaration of loop variables
		char * str_1 = strvec_1[str_ind % *length_1];
		char * str_2 = strvec_2[str_ind % *length_2];
		unsigned int l1 = strlen ( str_1 ) + 1;
		wchar_t wstr_1[l1];
		unsigned int l2 = strlen ( str_2 ) + 1;
		wchar_t wstr_2[l2];
		int lev_dist;
		
		// convert multi byte strings to wide character strings using current locale
		setlocale ( LC_ALL, "" );
		l1 = mbstowcs ( wstr_1, str_1, l1 );
		wstr_1[l1] = L'\0';
		l2 = mbstowcs ( wstr_2, str_2, l2 );
		wstr_2[l2] = L'\0';

		// probably it is as easy as that
		if ( ! l1 ) lev_dist = l2;
		if ( ! l2 ) lev_dist = l1;

		// call the appropriate distance function
		// no transposition in stings of length 1!
		lev_dist = l1 == 1 || l2 == 1 ? levenshtein_internal ( wstr_1, l1, wstr_2, l2 ) : levenshtein_damerau_internal ( wstr_1, l1, wstr_2, l2 );

		ans[str_ind] = lev_dist;
	}
} 

int levenshtein_internal ( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 )
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

int levenshtein_damerau_internal ( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 )
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
