#include "godotmation_converter.hpp"
#include "godotmation_resource.hpp"
#include "godotmation_state.hpp"

GodotMation_Converter::GodotMation_Converter(){};

GodotMation_Converter::~GodotMation_Converter(){};

bool GodotMation_Converter::trigger(){
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
        for(auto r : output_resources){
            r->trigger();
        }
        for(auto s : trigger_states){
            s->end_node->trigger();
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

int GodotMation_Converter::can_push(int value) const{
    return value;
}

