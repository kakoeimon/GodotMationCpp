#include "godotmation_pool.hpp"
#include "godotmation_resource.hpp"
#include "godotmation_state.hpp"

GodotMation_Pool::GodotMation_Pool(){}

GodotMation_Pool::~GodotMation_Pool(){}


bool GodotMation_Pool::trigger()
{
    if (!active) return false;
    if (pull_mode == 0){
        for (auto r : input_resources){
            if(!r->trigger()){
                satisfied = false;
            }
        }
    } else if (pull_mode == 1){
        for (auto r : input_resources){
            if(!r->can_push_all()){
                satisfied = false;
                break;
            }
        }
        if (satisfied){
            for (auto r : input_resources){
                r->trigger();
            }
        }
    } else if (pull_mode == 2){
        for (auto r : output_resources){
            r->end_node->pull_resources(r);
        }
    } else if (pull_mode == 3){
        for (auto r : output_resources){
            if (!r->can_push_all()){
                satisfied = false;
                break;
            }
        }
        if (satisfied){
            for (auto r : output_resources){
                r->end_node->pull_resources(r);
            }
        }
    }

    if(satisfied){
        for(auto r : input_resources) r->update_flow();
        for(auto s : trigger_states) s->end_node->trigger();
    }
    for(auto r : input_resources){
        if(!r->satisfied){
            for(auto s : reverse_trigger_states){
                s->end_node->trigger();
            }
        }
    }

    return true;
}

void GodotMation_Pool::pull_resources(GodotMation_Resource* r){
    if(!active) return;
    pushed = true;
    if (!r->trigger()){
        satisfied = false;
    }
}



int GodotMation_Pool::can_push(int value) const{
    if (value <= number + output_number){
        return value;
    } else if (number + output_number > 0){
        return number + output_number;
    } else{
        return 0;
    }
}



void GodotMation_Pool::change_input_state(int value)
{
    input_number += value;
    for (auto s : output_states){
        s->trigger(value);
    }
}

void GodotMation_Pool::change_output_state(int value)
{
    if (value > number + output_number){
        godot::Godot::print("pool change output state value > number + output_number");
    }
    output_number += value;
    for (auto s : output_states){
        s->trigger(value);
    }
}

int GodotMation_Pool::get_input_number() const{
    return number + input_number;
}

int GodotMation_Pool::get_output_number() const{
    return number + output_number;
}

int GodotMation_Pool::get_changed_number() const{
    return number + output_number + input_number;
}

void GodotMation_Pool::apply_state(){
    if (output_number || input_number){
        //printf("POOOL CHANGED");
        number += output_number + input_number;

        //if (emit_state_changed) owner->emit_signal("state_changed", number);
        output_number = 0;
        input_number = 0;
    }
    satisfied = true;
    active = true;
    for (auto s : input_conditional_states){
        s->trigger();
    }
}

void GodotMation_Pool::force_number(int value){
    number = value;
}
