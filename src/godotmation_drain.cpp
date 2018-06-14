#include "godotmation_drain.hpp"
#include "godotmation_resource.hpp"
#include "godotmation_state.hpp"

GodotMation_Drain::GodotMation_Drain(){};

GodotMation_Drain::~GodotMation_Drain(){};

bool GodotMation_Drain::trigger(){
    if(!active) return false;

    for(auto r : input_resources){
        if(!r->trigger()){
            satisfied = false;
        }
        r->end_node->pull_resources(r);
    }

    if(satisfied){
        for(auto r : input_resources){
            r->update_flow();
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

int GodotMation_Drain::can_push(int value) const{
    return 0;
}

void GodotMation_Drain::apply_state(){
    satisfied = true;
    active = true;
    for(auto s : input_conditional_states){
        s->trigger();
    }
}