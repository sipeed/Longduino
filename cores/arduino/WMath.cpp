#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint64_t a, b;
} xorshift128p_state_t;

static xorshift128p_state_t _xorshift128p_state = { UINT64_MAX - 1, 1 };

void randomSeed(unsigned long seed) {
    if (seed != 0) {
        _xorshift128p_state.a = seed;
    }
}

uint64_t xorshift128p(void) {
    uint64_t t = _xorshift128p_state.a;
    uint64_t const s = _xorshift128p_state.b;
    _xorshift128p_state.a = s;
    t ^= t << 23;
    t ^= t >> 17;
    t ^= s ^ (s >> 26);
    _xorshift128p_state.b = t;
    return t + s;
}

long random(long upperBound) {
    if (upperBound == 0) {
        return 0;
    }
    return xorshift128p() % upperBound;
}

long random(long lowerBound, long upperBound) {
    if (lowerBound >= upperBound) {
        return lowerBound;
    }
    long diff = upperBound - lowerBound;
    return random(diff) + lowerBound;
}
