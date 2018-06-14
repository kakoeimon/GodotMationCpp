#include "godotmation.hpp"
#include "Dictionary.hpp"



GodotMation::GodotMation(){}


GodotMation::~GodotMation()
{
    //godot::Godot::print("GODOTMATION DELETE");
    for(auto base_node : base_nodes){
        delete base_node.node;
    }
}


void GodotMation::_register_methods()
{
    godot::register_property((char *)"GodotMation/dict", &GodotMation::dict, godot::Dictionary());
   
    godot::register_method("is_godotmation", &GodotMation::is_godotmation);

    //godot::register_method("_notification", &GodotMation::_notification);

    godot::register_method("get_dict", &GodotMation::get_dict);
    godot::register_method("set_dict", &GodotMation::set_dict);



    godot::register_property((char *)"GodotMation/author", &GodotMation::author, godot::String(""));

    godot::register_property((char *)"GodotMation/time_mode", &GodotMation::time_mode, 0);

    godot::register_property((char *)"GodotMation/interval", &GodotMation::interval, 1.0f);


    godot::register_property((char *)"GodotMation/actions", &GodotMation::actions, 0);


    godot::register_property((char *)"GodotMation/dice", &GodotMation::dice, godot::String("D6"));


    godot::register_property((char *)"GodotMation/autostart", &GodotMation::autostart, true);


    
    godot::register_method("get_ticks", &GodotMation::get_ticks);

    godot::register_method("setup", &GodotMation::setup);
    godot::register_method("start", &GodotMation::start);

    godot::register_method("tick", &GodotMation::tick);

    godot::register_method("_clear", &GodotMation::_clear);

    godot::register_method("get_GM_number", &GodotMation::get_GM_number);
    
    
    

}


void GodotMation::is_godotmation()
{
    //this method exist only, for the plugin script to be able to identify that this is a GodotMation node
}



int GodotMation::get_ticks() const
{
	return ticks;
}

void GodotMation::setup()
{   
    read_dict();
    for(int i = 0; i < base_nodes.size(); i++) {
        GodotMation_Base_Node *child = &base_nodes[i];
        if(!child->node) godot::Godot::print("NUUUUUUUUUUULLLLLLL");
        
        int type = child->node->type;

        if (type >= 2) {
            //godot::Godot::print("TYPE 2\n");
            nodes.push_back(child->node);
            int activation_mode = child->get_activation_mode();
            if (activation_mode == 1){
                interactive_nodes.push_back(child->node);
            } else if (activation_mode == 2) {
                automatic_nodes.push_back(child->node);
            } else if (activation_mode == 3) {
                on_start_nodes.push_back(child->node);
            }
        } else if (type == 0) {
            resources.push_back( dynamic_cast<GodotMation_Resource*>(child->node) );
        } else if (type == 1) {
            states.push_back( dynamic_cast<GodotMation_State*>(child->node) );
        }
    }
    
    //nodes.shrink_to_fit();
    //interactive_nodes.shrink_to_fit();
    //automatic_nodes.shrink_to_fit();
    //on_start_nodes.shrink_to_fit();
    //resources.shrink_to_fit();
    //states.shrink_to_fit();

    
    for (auto r : resources) {
        r->convert_label();
        
        GodotMation_Base_Node *start = &base_nodes[r->start];
        start->node->output_resources.push_back( r );
        r->start_node = start->node;

        GodotMation_Base_Node *end = &base_nodes[r->end];
        end->node->input_resources.push_back( r );
        r->end_node = end->node;
    }

    for(auto s : states){
        s->convert_label();
        GodotMation_Base_Node *start = &base_nodes[s->start];
        GodotMation_Base_Node *end = &base_nodes[s->end];
        s->start_node = start->node;
        s->end_node = end->node;


        if(s->state_type == 9){
            start->node->trigger_states.push_back(s);
        } else if(s->state_type == 10){
            start->node->reverse_trigger_states.push_back(s);
        } else if(s->state_type >=4){
            end->node->input_conditional_states.push_back(s);
        } else {
            start->node->output_states.push_back(s);
            end->node->input_states.push_back(s);
        }
    }
    for(auto n : nodes){
        if(n->type == 7){
            GodotMation_Delay *d = dynamic_cast<GodotMation_Delay*>(n);
            if(n->output_resources.size()){
                for(int i = 0; i < n->output_resources[0]->object_number->get_number(); ++i){
                    d->resources_line.push_back(0);
                    n->number = 0;
                }
            }
        }
    }
    if(automatic_nodes.size()){
        timer = new godot::Timer();
        timer->set_name("GodotMation_Interval");
        timer->set_wait_time(interval);
        owner->add_child(timer);
        timer->connect("timeout", owner, "tick");
    }
}



void GodotMation::start()
{   
    
    if(timer){
        timer->start();
    }
    for (auto n : nodes) {
        n->apply_state();
    }
    for (auto r : resources) {
        r->apply_state();
    }
    for (auto s : states) {
        s->apply_state();
    }
    for (auto s : on_start_nodes) {
        s->trigger();
    }

    tick();
}

void GodotMation::tick(){
    //godot::Godot::print("tick");
    ticks++;
    if (reverse_order){
        for(int i = automatic_nodes.size()-1; i >= 0; i--){
            automatic_nodes[i]->trigger();
        }
        reverse_order = false;
    } else {
        for(auto a : automatic_nodes){
           a->trigger();
        }
        reverse_order = true;
    }

    for(auto n : nodes){
        if(n->pushed) n->apply_satisfaction();
    }
    
    for(auto n : nodes){
        n->apply_state();
    }
    for(auto r : resources){
        r->apply_state();
    }
    for(auto s : states){
        s->apply_state();
    }
    
}



void GodotMation::_clear(){
    if(timer){
        timer->free();
        timer = nullptr;
    } 
    for(auto base_node : base_nodes){
        delete base_node.node;
        base_node.owner->free();
    }
    base_nodes.clear();
    nodes.clear();
    interactive_nodes.clear();
    automatic_nodes.clear();
    on_start_nodes.clear();
    resources.clear();
    states.clear();
}

void GodotMation::set_dict(godot::Dictionary pd)
{
    dict = godot::Dictionary(pd);
}

godot::Dictionary GodotMation::get_dict() const
{
   return dict;
}

void GodotMation::read_dict()
{
    if(dict.has("version")){
        version = float(dict["version"]);
        author = dict["author"];
        time_mode = dict["time_mode"];
        //printf("\ntime_mode : %d\n", time_mode);
        interval = dict["interval"];
        actions = dict["actions"];
        dice = dict["dice"];
        autostart = dict["autostart"];
        godot::Array nodes = dict["nodes"];
        int nodes_size = nodes.size();
        for(int i = 0; i < nodes_size; i++){
            godot::Dictionary node = nodes[i];
            set_base_node(node);
        }
    }
}

void GodotMation::set_base_node(godot::Dictionary node){
    int type = node["type"];
    GodotMation_Base_Node base_node = GodotMation_Base_Node();
    //base_node.set_type(type);
    switch(type){
        case 0: //RESOURCE CONNECTION
            {
                base_node.node = new GodotMation_Resource();
                GodotMation_Resource *n = dynamic_cast<GodotMation_Resource*>(base_node.node);
                n->type = 0;
                n->caption = node["label"];
                n->start = node["start"];
                n->end = node["end"];
            }
            break;
        case 1: //STATE CONNECTION
            {
                base_node.node = new GodotMation_State();
                GodotMation_State *n = dynamic_cast<GodotMation_State*>(base_node.node);
                n->type = 1;
                n->caption = node["label"];
                n->start = node["start"];
                n->end = node["end"];
            }
            break;
        case 2: //POOL
            {
                base_node.node = new GodotMation_Pool();
                GodotMation_Pool *n = dynamic_cast<GodotMation_Pool*>(base_node.node);
                n->type = 2;
                n->caption = node["caption"];
                n->actions = node["actions"];
                n->activation_mode = node["activation_mode"];
                n->capacity = node["capacity"];
                n->starting_resources = node["starting_resources"];
                n->number = n->starting_resources;
            }
            break;
        case 3: //GATE
            {
                base_node.node = new GodotMation_Gate();
                GodotMation_Gate *n = dynamic_cast<GodotMation_Gate*>(base_node.node);
                n->type = 3;
                n->caption = node["caption"];
                n->actions = node["actions"];
                n->activation_mode = node["activation_mode"];
                n->gate_type = node["gate_type"];
            }
            break;
        case 4: //SOURCE
            {
                base_node.node = new GodotMation_Source();
                GodotMation_Source *n = dynamic_cast<GodotMation_Source*>(base_node.node);
                n->type = 4;
                n->caption = node["caption"];
                n->actions = node["actions"];
                n->activation_mode = node["activation_mode"];
            }
            break;
        case 5: //DRAIN
            {
                base_node.node = new GodotMation_Drain();
                GodotMation_Drain *n = dynamic_cast<GodotMation_Drain*>(base_node.node);
                n->type = 5;
                n->caption = node["caption"];
                n->actions = node["actions"];
                n->activation_mode = node["activation_mode"];
            }
            break;
        case 6: //CONVERTER
            {
                base_node.node = new GodotMation_Converter();
                GodotMation_Converter *n = dynamic_cast<GodotMation_Converter*>(base_node.node);
                n->type = 6;
                n->caption = node["caption"];
                n->actions = node["actions"];
                n->activation_mode = node["activation_mode"];
            }
            break;
        case 7:
            {
                base_node.node = new GodotMation_Delay();
                GodotMation_Delay *n = dynamic_cast<GodotMation_Delay*>(base_node.node);
                n->type = 7;
                n->caption = node["caption"];
                n->actions = node["actions"];
                n->activation_mode = node["activation_mode"];
                n->queue = node["queue"];
                
            }
            break;
        case 8:
            {
                base_node.node = new GodotMation_End_Condition();
                GodotMation_End_Condition *n = dynamic_cast<GodotMation_End_Condition*>(base_node.node);
                n->type = 8;
                n->caption = node["caption"];
                n->actions = node["actions"];
                n->activation_mode = node["activation_mode"];
                n->signaller = node["signaller"];
            }
            break;
        case 9:
            {
                base_node.node = new GodotMation_Function_Call();
                GodotMation_Function_Call *n = dynamic_cast<GodotMation_Function_Call*>(base_node.node);
                n->type = 9;
                n->caption = node["caption"];
                n->actions = node["actions"];
                n->activation_mode = node["activation_mode"];
            }
            break;


    }
    base_node.node->parent = this;
    base_nodes.push_back(base_node);

}

int GodotMation::get_GM_number(int loc) const
{
    //printf("\nloc : %d\n", loc);
    //return base_nodes.size();
    return base_nodes[loc].get_number();

}
