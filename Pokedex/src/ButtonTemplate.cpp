#ifndef SFML_GUI_PROJECT_BUTTON_TEMPLATE_CPP
#define SFML_GUI_PROJECT_BUTTON_TEMPLATE_CPP

#include "Button.h"

template <typename T>
void Button::onClick(void(*f)(T&), const T& param)
{
	if (checkState(PRESSED))
		(*f)(param);
}

template <typename T>
void Button::onClick(void(*f)(const T&), const T& param)
{
	if (checkState(PRESSED))
		(*f)(param);
}

template <typename T>
void Button::onClick(void(T::*f)(), T& obj)
{
	if (checkState(PRESSED))
		(obj.*f)();
}

template <typename T, typename S>
void Button::onClick(void(T::*f)(S), const S& param, T& obj) 
{
	if (checkState(PRESSED))
		(obj.*f)(param);
}

template <typename T, typename S>
void Button::onClick(void(T::* f)(S), void(T::*g)(S), const S& f_param, const S& g_param, T& obj)
{ 
	if (checkState(PRESSED))
	{
		(obj.*f)(f_param);
		(obj.*g)(g_param);
	}
}

#endif // SFML_GUI_PROJECT_BUTTON_TEMPLATE_CPP
