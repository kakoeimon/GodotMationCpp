#include "godotmation_end_condition.hpp"
#include "godotmation_resource.hpp"
#include "godotmation_state.hpp"
#include "godotmation.hpp"

GodotMation_End_Condition::GodotMation_End_Condition(){};

GodotMation_End_Condition::~GodotMation_End_Condition(){};

bool GodotMation_End_Condition::trigger(){
    if(!active) return false;
    return true;
}

void GodotMation_End_Condition::apply_state(){
    if(input_conditional_states.size()) active = true;
    for(auto s : input_conditional_states){
        s->trigger();
    }
    if(active){
        if(!signaller){
            if(parent->timer != nullptr){
                //parent->timer->disconnect("timeout", *parent, "tick");
                parent->timer->stop();
                //parent->timer->queue_free();
            }
        }
        //emit_signal("reached_condition");
    }
}