/* public interface */

// levenshtein distance over two strins
int levenshtein( const wchar_t* w1, const wchar_t* w2 );

// levenshtein distance over two strins with given lengths
int levenshtein_len( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 );
