/*
  LICENSE
      This software is dual-licensed to the public domain and under the following
      license: you are granted a perpetual, irrevocable license to copy, modify,
      publish, and distribute this file as you see fit.
 
  AUTHOR
      Professor Peanut
 
  USAGE
      Important! To keep things simple this class does NOT include a hash function.
      All function params are assumed to be already hashed.
 
      !!Attention!!
      This class does not protect from misuse! Removing the same key twice,
      or removing a non-existent key may break functionality.
 
  HISTORY
      0.1.0  Initial release
 
  PEANUTS
      BTC:  1H1RrCrEgUXDFibpaJciLjS9r7upQs6XPc
      BCH:  qzgfgd6zen70mfzasjtc4rx9m7fhz65zyg0n6v3sdh
      BSV:  15dtAGzzMf6yWF82aYuGKZYMCyP5HoWVLP
      ETH:  0x32a42d02eB021914FE8928d4A60332970F96f2cd
      DCR:  DsWY2Z1NThKqumM6x9oiyM3f2RkW28ruoyA
      LTC:  LWZ5HCcpModc1XcFpjEzz25J58eeQ8fJ7F
      DASH: XqMBmnxrgJWsvF7Hu3uBQ53TpcKLEsxsEi
      Let's make the World a better place!
*/

#ifndef COUNTING_BLOOM_FILTER_H
#define COUNTING_BLOOM_FILTER_H

template <class Inttype=unsigned>
class CountingBloomFilter
{
private:
    static constexpr int N_SLOTS = sizeof(Inttype) * 8;
    
    int counters[N_SLOTS] = {0};

    Inttype bitmap = 0;
    
public:
    constexpr void put(Inttype hash)
    {
        bitmap |= hash;
        for (int i=0; i<N_SLOTS; i+=8)
        {
            counters[i+0] += hash & 1; hash >>= 1;
            counters[i+1] += hash & 1; hash >>= 1;
            counters[i+2] += hash & 1; hash >>= 1;
            counters[i+3] += hash & 1; hash >>= 1;
            counters[i+4] += hash & 1; hash >>= 1;
            counters[i+5] += hash & 1; hash >>= 1;
            counters[i+6] += hash & 1; hash >>= 1;
            counters[i+7] += hash & 1; hash >>= 1;
        }
    }
    
    constexpr void remove(Inttype hash)
    {
        Inttype mask = 0;
        for (int i=0; i<N_SLOTS; i+=8)
        {
            counters[i+0] -= hash & 1; hash >>= 1;
            counters[i+1] -= hash & 1; hash >>= 1;
            counters[i+2] -= hash & 1; hash >>= 1;
            counters[i+3] -= hash & 1; hash >>= 1;
            counters[i+4] -= hash & 1; hash >>= 1;
            counters[i+5] -= hash & 1; hash >>= 1;
            counters[i+6] -= hash & 1; hash >>= 1;
            counters[i+7] -= hash & 1; hash >>= 1;
            mask |= !!counters[i+0] << i  ;
            mask |= !!counters[i+1] << i+1;
            mask |= !!counters[i+2] << i+2;
            mask |= !!counters[i+3] << i+3;
            mask |= !!counters[i+4] << i+4;
            mask |= !!counters[i+5] << i+5;
            mask |= !!counters[i+6] << i+6;
            mask |= !!counters[i+7] << i+7;
        }
        bitmap = bitmap & mask;
    }
    
    constexpr bool maybeHave(Inttype hash) const
    {
        return !((hash&bitmap) ^ hash);
    }
};


// tests:
constexpr unsigned cbf__test()
{
    CountingBloomFilter bloomTest;
    
    bloomTest.put(0b0110);
    const bool TEST_PUT_OK = bloomTest.maybeHave(0b0110);
    const bool TEST_SURE_DOESNT_HAVE = bloomTest.maybeHave(0b0001) == false;
    const bool TEST_OVERLAPPING_BITS = bloomTest.maybeHave(0b0100) == true;
    const bool TEST_CONFLICTING_BITS = bloomTest.maybeHave(0b1100) == false;
    bloomTest.put(0b1111);
    bloomTest.remove(0b0110);
    const bool TEST_KEY_FOUND_AFTER_REMOVE = bloomTest.maybeHave(0b0110) == true;
    bloomTest.remove(0b1111);
    const bool TEST_KEY_NOT_FOUND_AFTER_REMOVE = bloomTest.maybeHave(0b1111) == false;
    
    return  TEST_PUT_OK
         | (TEST_SURE_DOESNT_HAVE << 1)
         | (TEST_OVERLAPPING_BITS << 2)
         | (TEST_CONFLICTING_BITS << 3)
         | (TEST_KEY_FOUND_AFTER_REMOVE << 4)
         | (TEST_KEY_NOT_FOUND_AFTER_REMOVE << 5)
         ;
}
static constexpr unsigned resCBF = cbf__test();

static_assert(resCBF&  1, "Didn't work");
static_assert(resCBF&  2, ".maybeHave() returned 'true' when the key clearly didn't exist");
static_assert(resCBF&  4, ".maybeHave() overlapping bits");
static_assert(resCBF&  8, ".maybeHave() conflicting bits");
static_assert(resCBF& 16, "key disappeard after remove");
static_assert(resCBF& 32, "key should have disappeard after remove");


#endif // COUNTING_BLOOM_FILTER_H
