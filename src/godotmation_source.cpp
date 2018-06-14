#include "godotmation_source.hpp"
#include "godotmation_resource.hpp"
#include "godotmation_state.hpp"

GodotMation_Source::GodotMation_Source(){};

GodotMation_Source::~GodotMation_Source(){};

bool GodotMation_Source::trigger(){
    if(!active) return false;

    for(auto r : output_resources){
        r->end_node->pull_resources(r);
    }

    for(auto s : trigger_states){
        s->end_node->trigger();
    }

    return true;
}

int GodotMation_Source::can_push(int value) const{
    return value;
}

void GodotMation_Source::apply_state(){
    active = true;
    for(auto s : input_conditional_states){
        s->trigger();
    }
}