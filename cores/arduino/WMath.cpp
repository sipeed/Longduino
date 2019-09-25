#include <stdlib.h>
#include <stdint.h>
#include <gd32vf103.h>

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

uint64_t getSeed() {
    rcu_periph_clock_enable(RCU_BKPI);
    rcu_periph_clock_enable(RCU_PMU);
    pmu_backup_write_enable();
    bkp_deinit();
    rcu_osci_on(RCU_IRC40K);
    rcu_osci_stab_wait(RCU_IRC40K);
    rcu_rtc_clock_config(RCU_RTCSRC_IRC40K);
    rcu_periph_clock_enable(RCU_RTC);
    rtc_register_sync_wait();
    rtc_lwoff_wait();
    rtc_configuration_mode_enter();
    rtc_lwoff_wait();
    rtc_interrupt_enable(RTC_INT_SECOND);
    rtc_lwoff_wait();
    // increase second per about 1/100 second
    rtc_prescaler_set(399);
    rtc_lwoff_wait();
    rtc_counter_set(0);
    rtc_lwoff_wait();
    rtc_configuration_mode_exit();
    rtc_lwoff_wait();
    uint64_t ret;
    uint32_t virtualCounter = 0;
    for (size_t i = 0; i < 64; i++) {
        ret = ret << 1;
        uint32_t v0 = rtc_counter_get();
        while (v0 == rtc_counter_get()) {
            virtualCounter++;
        }
        ret = ret | (virtualCounter & 0x1);
    }
    return ret;
}
