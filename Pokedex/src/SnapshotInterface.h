#ifndef SFML_GUI_PROJECT_SNAPSHOT_INTERFACE_H
#define SFML_GUI_PROJECT_SNAPSHOT_INTERFACE_H

#include "Snapshot.h"

class SnapshotInterface
{
public:
	virtual Snapshot& getSnapshot() = 0;
	virtual void applySnapshot(const Snapshot& snapshot) = 0;
};

#endif // SFML_GUI_PROJECT_SNAPSHOT_INTERFACE_H
