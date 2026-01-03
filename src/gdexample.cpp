#include "gdexample.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void GDExample::_bind_methods() {
    // Здесь можно регистрировать методы и свойства для Godot
}

GDExample::GDExample() {
    speed = 20.0;
    jump_velocity = 10.0;
}

GDExample::~GDExample() {}

void GDExample::_physics_process(double p_delta) {
    Input* input = Input::get_singleton();
    Vector3 velocity = get_velocity();
    float delta = (float)p_delta;
    if (!is_on_floor()) {
        velocity.y -= 11.0f * delta;
    }
    if (input->is_action_just_pressed("ui_accept") && is_on_floor()) {
        velocity.y = (float)jump_velocity;
    }

    Vector2 input_dir = input->get_vector("ui_left", "ui_right", "ui_up", "ui_down");

    if (input_dir == Vector2(0, 0)) {
        if (input->is_key_pressed(Key::KEY_W)) input_dir.y -= 1.0f;
        if (input->is_key_pressed(Key::KEY_S)) input_dir.y += 1.0f;
        if (input->is_key_pressed(Key::KEY_A)) input_dir.x -= 1.0f;
        if (input->is_key_pressed(Key::KEY_D)) input_dir.x += 1.0f;
    }

    Basis basis = get_global_transform().get_basis();
    Vector3 direction = (basis.get_column(2) * input_dir.y + basis.get_column(0) * input_dir.x).normalized();

    if (direction != Vector3(0, 0, 0)) {
        velocity.x = direction.x * (float)speed;
        velocity.z = direction.z * (float)speed;
    }
    else {
        float friction = (float)speed * delta * 10.0f;
        velocity.x = Math::move_toward((float)velocity.x, 0.0f, friction);
        velocity.z = Math::move_toward((float)velocity.z, 0.0f, friction);
    }

    // Выполнение движения
    set_velocity(velocity);
    move_and_slide();
}
