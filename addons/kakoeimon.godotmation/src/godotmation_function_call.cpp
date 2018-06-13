#include "godotmation_function_call.hpp"
#include "godotmation_resource.hpp"
#include "godotmation_state.hpp"
#include "godotmation.hpp"

GodotMation_Function_Call::GodotMation_Function_Call(){};

GodotMation_Function_Call::~GodotMation_Function_Call(){};

bool GodotMation_Function_Call::trigger(){
    if(!active || caption.empty()) return false;
    number = parent->owner->get_parent()->call(caption);
    return true;
}

int GodotMation_Function_Call::can_push(int value) const
{
    if(value <= number){
        return value;
    }
    if(number > 0){
        return number;
    } else {
        return 0;
    }
}

void GodotMation_Function_Call::apply_state(){
    active = true;
    for(auto s : input_conditional_states){
        s->trigger();
    }
    if(active){
        trigger();
    } else {
        number = 0;
    }
}