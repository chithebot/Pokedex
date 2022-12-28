#ifndef SFML_GUI_PROJECT_HISTORY_H
#define SFML_GUI_PROJECT_HISTORY_H

#include <stack>
#include <cassert>
#include "Tools.h"
#include "HistoryNode.h"

class History
{
public:
	static HistoryNode& topHistory();
	static bool emptyHistory();
	static void pushHistory(Snapshot* snapshot, GUIComponent* component);
	static void popHistory();
	static void eventHandler(const sf::RenderWindow& window, sf::Event event);
private:
	static std::stack<HistoryNode> stack;
};

#endif // SFML_GUI_PROJECT_HISTORY_H
