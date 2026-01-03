#include "die_zone.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/node.hpp>

using namespace godot;

void DieZone::_bind_methods() {
    // Важно: имя метода в D_METHOD должно совпадать с именем в C++
    ClassDB::bind_method(D_METHOD("_on_body_entered", "body"), &DieZone::_on_body_entered);
}

DieZone::DieZone() {}
DieZone::~DieZone() {}

void DieZone::_on_body_entered(Node* body) {
    if (body == nullptr) return;

    // Проверка: ваш класс игрока называется GDExample, а не Player
    if (body->get_name() == String("Player") || body->is_class("GDExample")) {
        UtilityFunctions::print("Игрок упал! Перезагрузка...");

        SceneTree* tree = get_tree();
        if (tree) {
            tree->reload_current_scene();
        }
    }
}
