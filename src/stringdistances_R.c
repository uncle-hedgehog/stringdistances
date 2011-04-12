#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <R.h>

#include "stringdistances.h"

void levenshtein_damerau_R ( char ** strvec_1, char ** strvec_2, int * length_1, int * length_2, int * ans )
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
		lev_dist = l1 == 1 || l2 == 1 ? levenshtein ( wstr_1, l1, wstr_2, l2 ) : levenshtein_damerau ( wstr_1, l1, wstr_2, l2 );

		ans[str_ind] = lev_dist;
	}
} 
