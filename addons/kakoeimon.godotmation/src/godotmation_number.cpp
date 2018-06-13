#include "godotmation_number.hpp"

GodotMation_Number::GodotMation_Number(){}

GodotMation_Number::~GodotMation_Number(){}

void GodotMation_Number::set_from_string(godot::String value) {
    label = value;
    number = float(label.to_float());
    base = int(number);
    chance = number - float(base);


    //printf("\nNumber : %f \nBase : %d \nchance : %f \n", number, base, chance);
    //godot::Godot::print(label);
    return;
}

int GodotMation_Number::get_number() const{
    int output = base;
    //if(Random::get(0.0f, 1.0f) < chance) output++;

    //if(other_object_number) output += other_object_number->get_number();

    return output;
}

void GodotMation_Number::add_number(float value){
    number += value;
    base = int(number);
    chance = number - float(base);
}
