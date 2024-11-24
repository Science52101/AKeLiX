#ifndef AKELOX_BIX
#define AKELOX_BIX

long long filled_range_1 (unsigned, unsigned);
long long filled_range_0 (unsigned, unsigned);

long long fit_8bit  (long long);
long long fit_16bit (long long);
long long fit_32bit (long long);
long long fit_64bit (long long);

long long extract_range (long long, unsigned, unsigned);
long long fill_range_0  (long long, unsigned, unsigned);
long long fill_range_1  (long long, unsigned, unsigned);

long long leftmost_1  (long long);
long long rightmost_1 (long long);
long long leftmost_0  (long long);
long long rightmost_0 (long long);

#endif
