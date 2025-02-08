#ifndef AKELOX_BIX
#define AKELOX_BIX

typedef uint8_t  bool;
typedef uint8_t  byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t size;

typedef bs*   bytes;
typedef byte* addr ;

bytes mkBytes (size );
bytes cpBytes (bytes);

byte  gtByte  (bytes, size);
bit   gtBit   (bytes, size);
word  gtWord  (bytes, size);
dword gtDWord (bytes, size);

bytes stByte  (bytes, size, byte );
bytes stBit   (bytes, size, bit  );
bytes stWord  (bytes, size, word );
bytes stDWord (bytes, size, dword);

bytes shl (bytes, size);
bytes shr (bytes, size);

#endif
