#include "InputManager.h"
#include "../Logger/Logger.h"
#include <iostream>

std::unordered_map<KeyCode, bool> InputManager::keys =
{
	{ KeyCode::A, false },
	{ KeyCode::B, false },
	{ KeyCode::C, false },
	{ KeyCode::D, false },
	{ KeyCode::E, false },
	{ KeyCode::F, false },
	{ KeyCode::G, false },
	{ KeyCode::H, false },
	{ KeyCode::I, false },
	{ KeyCode::J, false },
	{ KeyCode::K, false },
	{ KeyCode::L, false },
	{ KeyCode::M, false },
	{ KeyCode::N, false },
	{ KeyCode::Ñ, false },
	{ KeyCode::O, false },
	{ KeyCode::P, false },
	{ KeyCode::Q, false },
	{ KeyCode::R, false },
	{ KeyCode::S, false },
	{ KeyCode::T, false },
	{ KeyCode::U, false },
	{ KeyCode::V, false },
	{ KeyCode::W, false },
	{ KeyCode::X, false },
	{ KeyCode::Y, false },
	{ KeyCode::Z, false }
};

glm::vec2 InputManager::mouse_position = glm::vec2(0);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Setting the keys' states
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputManager::SetKey(KeyCode key_code, bool value)
{
	auto key = keys.find(key_code);

	if (key == keys.end()) {
		Logger::Error("The key couldn't be found!!!");
		return;
	}

	key->second = value;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Getting the keys' states
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputManager::GetKey(KeyCode key_code)
{
	auto key = keys.find(key_code);

	if (key == keys.end()) {
		Logger::Error("The key couldn't be found!!!");
		return false;
	}

	return key->second;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Setting and getting mouse position
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputManager::SetMousePosition(glm::vec2 mouse_pos)
{
	mouse_position = mouse_pos;
}

glm::vec2 InputManager::GetMousePosition()
{
	return mouse_position;
}
