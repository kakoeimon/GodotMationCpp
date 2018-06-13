#ifndef GODOTMATION_DICE_H
#define GODOTMATION_DICE_H

#include "godotmation_base_number.hpp"




class GodotMation_Dice: public GodotMation_Base_Number{

public:
    GodotMation_Dice();
    ~GodotMation_Dice();
    godot::String label = "D6";
    bool plus = true;
    int number_of_dices = 0;
    int number_of_sides = 0;
    int other_number = 0;
    void set_from_string(godot::String);
    int get_number() const;

};

#endif