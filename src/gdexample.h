#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/node3d.hpp>

namespace godot {

    class GDExample : public CharacterBody3D {
        GDCLASS(GDExample, CharacterBody3D)

    private:
        Node3D* SpringArm3D = nullptr;
        double speed;
        double jump_velocity;
        bool mouse_captured = true;
        float mouse_sens;

    protected:
        static void _bind_methods();

    public:
        GDExample();
        ~GDExample();

        void _ready() override;
        void _physics_process(double p_delta) override;
        void _unhandled_input(const Ref<InputEvent>& event) override;
    };

}

#endif
