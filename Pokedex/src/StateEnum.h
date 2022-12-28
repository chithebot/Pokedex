#ifndef SFML_GUI_PROJECT_STATE_ENUMS_H
#define SFML_GUI_PROJECT_STATE_ENUMS_H

enum StateEnum
{
	HIDDEN,		// if object is hidden
	FOCUS,		// if object is focused
	PRESSED,	// if object is pressed
	HOVER,		// if mouse is hovered over object
	BLINK,		// if object is in state of blink
	BLINK_ON,	// helper state: if object blink state is on
	UNSORTED,	// if object is unsorted
	NUM_STATES
};

#endif // SFML_GUI_PROJECT_STATE_ENUMS_H
