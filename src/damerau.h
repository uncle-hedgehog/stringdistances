/* public interface */

// damerau distance over two strins
int damerau( const wchar_t* w1, const wchar_t* w2 );

// damerau distance over two strins with given lengths
int damerau_len( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 );

/* internal */

/* myers bit parallelism algorithm adopted for damerau distance by hyyrö.
   NOTE: one string HAS to be shorter than sizeof(unsigned long long). */
int damerau_bits( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 );

// dynamic programming matrix. classical algorithm with minor optimizations.
int damerau_matrix( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2 );

