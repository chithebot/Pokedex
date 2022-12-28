#include "History.h"

std::stack<HistoryNode> History::stack;

HistoryNode& History::topHistory()
{
	assert(!stack.empty() && "History is empty.");
	return stack.top();
}

bool History::emptyHistory() { return stack.empty(); }

void History::pushHistory(Snapshot* snapshot, GUIComponent* component) { stack.emplace(snapshot, component); }

void History::popHistory() 
{
	if (!stack.empty())
		stack.pop();
}

void History::eventHandler(const sf::RenderWindow& window, sf::Event event) { }
