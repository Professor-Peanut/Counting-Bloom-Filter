/*
  LICENSE
      This software is dual-licensed to the public domain and under the following
      license: you are granted a perpetual, irrevocable license to copy, modify,
      publish, and distribute this file as you see fit.
 
  AUTHOR
      Professor Peanut
 
  HISTORY
      0.1.0  Initial release
 
  GIBS
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
    int counters[sizeof(Inttype) * 8] = {0};

    Inttype bitmap = 0;
    
public:
    void put(Inttype key) {}
    
    void remove(Inttype key) {}
    
    bool maybeHave(Inttype key) const {}
};


// tests:
constexpr unsigned cbf__test()
{
    CountingBloomFilter bloomTest;
    
    return 1;
}
static constexpr unsigned res = cbf__test();

static_assert(res& 1, "");


#endif // COUNTING_BLOOM_FILTER_H
