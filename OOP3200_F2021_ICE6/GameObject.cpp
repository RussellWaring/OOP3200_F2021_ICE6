/* @file	OOP3200_F2021_ICE6 - GameObject.cpp
 * @author	Russell Waring
 * @stuID	100528426
 * @date	2021-10-20
 * @desc	A modified version of the provided GameObject class.
 */
#include "GameObject.h"

#include <utility>

GameObject::GameObject(): m_id(0), m_name("not set"), m_position(Vector2D<float>()) // added m_name to default constructor
{
}

GameObject::GameObject(const int id, const float x, const float y)
{
	SetID(id);
	SetName("not set");
	SetPosition(x, y);
}

GameObject::GameObject(const int id, const Vector2D<float>& position)
{
	SetID(id);
	SetPosition(position);
}

GameObject::GameObject(std::string name, const int id, const float x, const float y) // name should be const, and reference
	:m_id(id), m_name(std::move(name)), m_position(Vector2D<float>(x, y))
{
}

GameObject::GameObject(std::string name, const int id, const Vector2D<float>& position) // id should be const
	: m_id(id), m_name(std::move(name)), m_position(position) // is already a Vector2D, pass in
{
}

std::string GameObject::GetName() const // should be const
{;
	return m_name;
}

void GameObject::SetName(const std::string& name) // const and by reference
{
	m_name = name; // can search for object by name, oppose to id
}

GameObject::~GameObject()
= default;

GameObject::GameObject(const GameObject& other_object)
{
	SetID(other_object.m_id);
	SetPosition(other_object.m_position);
}

GameObject& GameObject::operator=(const GameObject& other_object)
{
	SetID(other_object.m_id);
	SetPosition(other_object.m_position);
	return (*this);
}

Vector2D<float> GameObject::GetPosition() const
{
	return m_position;
}

int GameObject::GetID() const
{
	return m_id;
}

void GameObject::SetID(const int id)
{
	m_id = id;
}

void GameObject::SetPosition(const float x, const float y)
{
	m_position.Set(x, y);
}

void GameObject::SetPosition(const Vector2D<float>& new_position)
{
	m_position = new_position;
}

std::string GameObject::ToString() const
{
	std::string output_string;
	output_string += "ID       : " + std::to_string(GetID()) + "\n";
	output_string += "Position : " + GetPosition().ToString() + "\n";
	return output_string;
}
