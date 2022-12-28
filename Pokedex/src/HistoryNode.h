#ifndef SFML_GUI_PROJECT_HISTORY_NODE_H
#define SFML_GUI_PROJECT_HISTORY_NODE_H

#include "GUIComponent.h"

struct HistoryNode
{
	HistoryNode() : snapshot(nullptr), component(nullptr) { }
	HistoryNode(Snapshot* snapshot, GUIComponent* component) : snapshot(snapshot), component(component) { }
	~HistoryNode() { delete snapshot; }
	Snapshot* snapshot;
	GUIComponent* component;
};

#endif // SFML_GUI_PROJECT_HISTORY_NODE_H