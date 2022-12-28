#ifndef SFML_GUI_PROJECT_GUI_COMPONENT_H
#define SFML_GUI_PROJECT_GUI_COMPONENT_H

#include "EventHandler.h"
#include "SnapshotInterface.h"
#include "States.h"

class GUIComponent : public sf::Drawable, public sf::Transformable, public EventHandler, public SnapshotInterface, public States
{
public:
	virtual void eventHandler(const sf::RenderWindow& window, sf::Event event) = 0;
	virtual void update() = 0;
	virtual Snapshot& getSnapshot() = 0;
	virtual void applySnapshot(const Snapshot& snapshot) = 0;
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

#endif // SFML_GUI_PROJECT_GUI_COMPONENT_H
