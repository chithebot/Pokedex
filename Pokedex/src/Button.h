#ifndef SFML_GUI_PROJECT_BUTTON_H
#define SFML_GUI_PROJECT_BUTTON_H

#include <iostream>
#include "Container.h"

class Button : public Container, public EventHandler, public States
{
public:
	Button();
	Button(const sf::Vector2f& size);
	const sf::Color& getHoverColor() const;
	void setFillColor(const sf::Color& color);
	void setHoverColor(const sf::Color& color);
	void eventHandler(const sf::RenderWindow& window, sf::Event event) override;
	void update() override;

	void onClick(void(*f)());

	template <typename T>
	void onClick(void(*f)(T&), const T& param);

	template <typename T>
	void onClick(void(*f)(const T&), const T& param);

	template <typename T>
	void onClick(void(T::*f)(), T& obj);

	template <typename T, typename S>
	void onClick(void(T::*f)(S), const S& param, T& obj);

	template <typename T, typename S>
	void onClick(void(T::*f)(S), void(T::* g)(S), const S& f_param, const S& g_param, T& obj);

private:
	sf::Color restStateColor;
	sf::Color hoverStateColor;
};

#include "ButtonTemplate.cpp"

#endif // SFML_GUI_PROJECT_BUTTON_H
