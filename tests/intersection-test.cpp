#include "gtest/gtest.h"
#include <vector>

extern "C" {
    #include "intersection.h"
    #include "leds.h"
    #include "state_machine.h"
    #include "HAL_stubs.h"

    // Mock shift register values
    uint8_t mock_shift_register_value = 0;
    std::vector<uint8_t> mock_shift_register_history;

    void leds_write(uint8_t value) {
        mock_shift_register_value = value;
        mock_shift_register_history.push_back(value);
    }
}

class IntersectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        mock_shift_register_value = 0;
        mock_shift_register_history.clear();
        mock_tick = 0;
        intersection_init();
    }
};

TEST_F(IntersectionTest, InitialStateIsNSgEWr) {
    EXPECT_EQ(mock_shift_register_value, PATTERN_NSgEWr);
    ASSERT_EQ(mock_shift_register_history.size(), 1U);
    EXPECT_EQ(mock_shift_register_history[0], PATTERN_NSgEWr);
}

TEST_F(IntersectionTest, NormalCycleTransitions) {
    uint32_t t1 = DURATION_NSgEWr;
    uint32_t t2 = t1 + DURATION_NSgrEWr;
    uint32_t t3 = t2 + DURATION_NSrEWg;
    uint32_t t4 = t3 + DURATION_NSrEWgr;

    // Initial state: NSgEWr (starts at t=0)
    mock_tick = t1 - 1;
    intersection_step();
    EXPECT_EQ(mock_shift_register_value, PATTERN_NSgEWr);

    mock_tick = t1;
    intersection_step();
    EXPECT_EQ(mock_shift_register_value, PATTERN_NSgrEWr);

    // State: NSgrEWr
    mock_tick = t2 - 1;
    intersection_step();
    EXPECT_EQ(mock_shift_register_value, PATTERN_NSgrEWr);

    mock_tick = t2;
    intersection_step();
    EXPECT_EQ(mock_shift_register_value, PATTERN_NSrEWg);

    // State: NSrEWg
    mock_tick = t3 - 1;
    intersection_step();
    EXPECT_EQ(mock_shift_register_value, PATTERN_NSrEWg);

    mock_tick = t3;
    intersection_step();
    EXPECT_EQ(mock_shift_register_value, PATTERN_NSrEWgr);

    // State: NSrEWgr
    mock_tick = t4 - 1;
    intersection_step();
    EXPECT_EQ(mock_shift_register_value, PATTERN_NSrEWgr);

    mock_tick = t4;
    intersection_step();
    EXPECT_EQ(mock_shift_register_value, PATTERN_NSgEWr);
}

TEST_F(IntersectionTest, EmergencyTrigger) {
    uint32_t trigger_time = 5000;
    mock_tick = trigger_time;
    intersection_trigger_emergency();

    // Verification: immediate shift register update
    EXPECT_EQ(mock_shift_register_value, PATTERN_NSrEWr);

    intersection_step();
    EXPECT_EQ(mock_shift_register_value, PATTERN_NSrEWr);

    // All Red state lasts DURATION_NSrEWr
    mock_tick = trigger_time + DURATION_NSrEWr - 1;
    intersection_step();
    EXPECT_EQ(mock_shift_register_value, PATTERN_NSrEWr);

    mock_tick = trigger_time + DURATION_NSrEWr;
    intersection_step();
    EXPECT_EQ(mock_shift_register_value, PATTERN_NSgEWr);
}
