#include "godotmation_gate.hpp"
#include "godotmation_resource.hpp"
#include "godotmation_state.hpp"

GodotMation_Gate::GodotMation_Gate(){};

GodotMation_Gate::~GodotMation_Gate(){};

bool GodotMation_Gate::trigger(){
    if(!active) return false;

    if(pull_mode != 1){
        for(auto r : input_resources){
            if(!r->trigger()){
                satisfied = false;
            }
        }
    } else if(pull_mode == 1){
        for(auto r : input_resources){
            if(!r->can_push_all()){
                satisfied = false;
                break;
            }
        }
        if(satisfied){
            for(auto r : input_resources){
                r->trigger();
            }
        }
    }

    if(satisfied){
        for(auto r : input_resources){
            r->update_flow();
        }
        for(auto s : trigger_states){
            s->end_node->trigger();
        }
    }
    if(gate_type == 0 && output_resources.size()){
        int number_type = output_resources[0]->object_number->type;
        if(number_type == 0){
            while(output_resources[output_i]->trigger()){
                //godot::Godot::print(godot::String::num(resource_type));
                output_resources[output_i]->update_flow();
                output_resources[output_i]->used = false;
                ++output_i;
                if(output_i > output_resources.size() - 1) output_i = 0;
            }
        } else if(number_type == 1){
            
        }
    }
    for(auto r : input_resources){
        if(!r->satisfied){
            for(auto s : reverse_trigger_states){
                s->end_node->trigger();
            }
            break;
        }
    }
}

void GodotMation_Gate::change_input_state(int value){
    number += value;
    trigger();
    for(auto s : output_states){
        s->trigger();
    }
}

void GodotMation_Gate::change_output_state(int value){
    number += value;
    trigger();
    for(auto s : output_states){
        s->trigger();
    }
}
