#include "godotmation_delay.hpp"
#include "godotmation_resource.hpp"
#include "godotmation_state.hpp"

GodotMation_Delay::GodotMation_Delay(){};

GodotMation_Delay::~GodotMation_Delay(){};

bool GodotMation_Delay::trigger(){
    if(!active) return false;

    for(auto r : input_resources){
        if(!r->trigger()){
            satisfied = false;
        }
    }
    if(output_resources.size() > 0){
        output_resources[0]->trigger();
    }

    if(satisfied){
        for(auto r : input_resources){
            r->update_flow();
        }
        /*
        for(auto s : trigger_states){
            s->end_node->trigger();
        }
        */
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

int GodotMation_Delay::can_push(int value) const 
{
    if(number > 0){
        for(auto s : trigger_states){
            s->end_node->trigger();
        }
    }
    return number;
}

void GodotMation_Delay::apply_satisfaction()
{
    if(output_resources.size()){
        output_resources[0]->trigger();
    }
    pushed = false;
}

void GodotMation_Delay::apply_state()
{

    
    if(!queue){
        resources_line[interval_i] = number + output_number + input_number;
        ++interval_i;
        if(interval_i >= resources_line.size()) interval_i = 0;
        number = resources_line[interval_i];
    } else {
        resources_line[0] += output_number + input_number;
        ++interval_i;
        if(interval_i >= resources_line.size()) interval_i = 0;
        if(interval_i == 0 && resources_line[interval_i] > 0){
            number = 1;
        } else {
            number = 0;
        }
    }
    
    output_number = 0;
    input_number = 0;

    satisfied = true;
    active = true;
    for(auto s : input_conditional_states){
        s->trigger();
    }
}