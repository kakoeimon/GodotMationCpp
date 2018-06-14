#ifndef GODOTMATION_H
#define GODOTMATION_H

#include <vector>

#include "Godot.hpp"
#include "Node.hpp"
#include "JSONParseResult.hpp"
#include "Timer.hpp"
#include "godotmation_base_node.hpp"



using namespace godot;

class GodotMation : public GodotScript<Node> {
	GODOT_CLASS(GodotMation)
public:
    GodotMation();
    ~GodotMation();
    static void _register_methods();

    godot::Dictionary dict;
    float version;
    godot::String author;
    int time_mode;
    float interval;
    int actions;
    godot::String dice;
    bool autostart;
    int ticks;
    bool reverse_order = false;

    godot::Timer *timer = nullptr;

    std::vector<GodotMation_Base_Node> base_nodes;
    std::vector<GodotMation_Node*> nodes;
    std::vector<GodotMation_Node*> interactive_nodes;
    std::vector<GodotMation_Node*> automatic_nodes;
    std::vector<GodotMation_Node*> on_start_nodes;

    std::vector<GodotMation_Resource*> resources;
    std::vector<GodotMation_State*> states;


    float get_version() const;
    void set_version(float);
    godot::String get_author() const;
    void set_author(godot::String);
    int get_time_mode() const;
    void set_time_mode(int);
    float get_interval() const;
    void set_interval(float);
    int get_actions() const;
    void set_actions(int);
    godot::String get_dice() const;
    void set_dice(godot::String);
    bool get_autostart() const;
    void set_autostart(bool);
    int get_ticks() const;

    void setup();
    void start();
    void tick();

    godot::Dictionary get_dict() const;
    void set_dict(godot::Dictionary);
    

    void _clear();

    void is_godotmation();

    void _notification(int);

    
    void read_dict();
    void set_base_node(godot::Dictionary);
    
    int get_GM_number(int) const;
};

#endif