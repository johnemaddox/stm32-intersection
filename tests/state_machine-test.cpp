#include "gtest/gtest.h"
extern "C" {
#include "state_machine.h"
}

namespace {

static sm_state_t dummy_callback_executed = 999;

static sm_state_t dummy_callback(sm_handle_t *self, void *context) {
    (void)self;
    int *count = static_cast<int*>(context);
    if (count) {
        (*count)++;
    }
    return dummy_callback_executed;
}

TEST(StateMachineTest, BasicTransition) {
    static const sm_state_config_t state_table[2] = {
        { dummy_callback, 1 }, // State 0 -> State 1
        { nullptr,        0 }  // State 1 -> State 0
    };

    int count = 0;
    sm_handle_t handle;
    handle.cur_state = 0;
    handle.state_table = state_table;
    handle.num_states = 2;
    handle.context = &count;

    // Run first step (transitions to state 1)
    dummy_callback_executed = 10;
    sm_result_t res = sm_run(&handle);
    EXPECT_EQ(res.status, SM_OK);
    EXPECT_EQ(res.state, 10);
    EXPECT_EQ(handle.cur_state, 1);
    EXPECT_EQ(count, 1);

    // Run second step (no callback, transitions to state 0)
    res = sm_run(&handle);
    EXPECT_EQ(res.status, SM_OK);
    EXPECT_EQ(res.state, 1); // Returns cur_state which was 1
    EXPECT_EQ(handle.cur_state, 0);
    EXPECT_EQ(count, 1);
}

TEST(StateMachineTest, NullSafety) {
    EXPECT_EQ(sm_run(nullptr).status, SM_ERR_NULLPTR);

    sm_handle_t handle;
    handle.cur_state = 0;
    handle.state_table = nullptr;
    handle.num_states = 2;
    handle.context = nullptr;

    EXPECT_EQ(sm_run(&handle).status, SM_ERR_NULLPTR);
}

TEST(StateMachineTest, InvalidState) {
    static const sm_state_config_t state_table[2] = {
        { nullptr, 1 },
        { nullptr, 0 }
    };

    sm_handle_t handle;
    handle.cur_state = 5; // Invalid (>= num_states)
    handle.state_table = state_table;
    handle.num_states = 2;
    handle.context = nullptr;

    EXPECT_EQ(sm_run(&handle).status, SM_ERR_INVALID_STATE);
}

} // namespace
