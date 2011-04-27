/* public interface */

// jaccard distance of two strings with given n-gram width
int jaccard( const wchar_t* w1, const wchar_t* w2, unsigned int n );

// jaccard distance of two strings with given lengths and given n-gram width
int jaccard_len( const wchar_t* w1, unsigned int l1, const wchar_t* w2, unsigned int l2, unsigned int n );

