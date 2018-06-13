#include "godotmation_dice.hpp"


GodotMation_Dice::GodotMation_Dice(){}

GodotMation_Dice::~GodotMation_Dice(){}

void GodotMation_Dice::set_from_string(godot::String value) {
    label = value;
    if(label[0] == '-'){
        plus = false;
        value = value.right(1);
    }
    int pos = value.find("D",0);
    
    number_of_dices = value.left(pos).to_int();
    number_of_sides = value.right(pos+1).to_int();

    printf("\nDices : %d \nSides : %d\n", number_of_dices, number_of_sides);
    godot::Godot::print("ok");
}

int GodotMation_Dice::get_number() const{
    int output = 0;
    if(plus){
        for(int i = 0; i < number_of_dices; i++){
            //output += Random::get(1, number_of_sides);
        }
    } else{
        for(int i = 0; i < number_of_dices; i++){
            //output -= Random::get(1, number_of_sides);
        }
    }
    if(other_object_number) output += other_object_number->get_number();
    return output;
}
