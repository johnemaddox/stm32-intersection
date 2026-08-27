#include "state_machine.h"

sm_result_t sm_run(sm_handle_t *self)
{
    sm_result_t result;
    if (self == NULL || self->state_table == NULL)
    {
        result.status = SM_ERR_NULLPTR;
        result.state = 0;
        return result;
    }

    if (self->cur_state >= self->num_states)
    {
        result.status = SM_ERR_INVALID_STATE;
        result.state = 0;
        return result;
    }

    const sm_state_config_t *state = &self->state_table[self->cur_state];
    sm_state_t rtn = self->cur_state;

    if (state->event != NULL)
    {
        rtn = state->event(self, self->context);
    }

    self->cur_state = state->next_state;
    
    result.status = SM_OK;
    result.state = rtn;
    return result;
}
