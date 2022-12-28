#include "PokemonEntryList.h"

PokemonEntryList::PokemonEntryList() : PokemonEntryList({0.f, 0.f}, 0, 0, 0) { }

PokemonEntryList::PokemonEntryList(const sf::Vector2f& size, unsigned entriesPerRow, float horizontalPadding, float verticalPadding, unsigned characterSize)
	: Container(size), entriesPerRow(entriesPerRow), horizontalPadding(horizontalPadding), 
	verticalPadding(verticalPadding), characterSize(characterSize)
{
	setFillColor(sf::Color::Transparent);
	SortState::setSortState(NUMERIC);
}

PokemonEntryList::~PokemonEntryList()
{
	// Deallocating memory for all pokemon entries
	for (PokemonEntry*& entry_ptr : entries)
		delete entry_ptr;
}

float PokemonEntryList::getEntryHeight() const
{
	if (entries.empty())
		return 0.f;
	return entries.front()->getSize().y;
}

unsigned PokemonEntryList::getCharacterSize() const { return characterSize; }

unsigned PokemonEntryList::getNumEntriesPerRow() const { return entriesPerRow; }

float PokemonEntryList::getHorizonalPadding() const { return horizontalPadding; }

float PokemonEntryList::getVerticalPadding() const { return verticalPadding; }

void PokemonEntryList::setSize(const sf::Vector2f& size)
{
	Container::setSize(size);
	resizeEntries();
	resizeContainer();
	repositionEntries();
}

void PokemonEntryList::setEntryHeight(float height)
{
	// Setting new height for each entry
	for (PokemonEntry*& entry_ptr : entries)
		entry_ptr->setSize({entry_ptr->getSize().x, height});
}

void PokemonEntryList::setCharacterSize(unsigned size)
{
	// Setting character size of text in each pokemon entry
	for (PokemonEntry*& entry_ptr : entries)
		(*entry_ptr).setCharacterSize(size);
}

void PokemonEntryList::setNumEntriesPerRow(unsigned numEntries) { entriesPerRow = numEntries; }

void PokemonEntryList::setHorizonalPadding(float padding)
{
	assert((padding * (entriesPerRow + 1)) < getSize().x && "Padding exceeds the size of the container.");
	horizontalPadding = padding;
}

void PokemonEntryList::setVerticalPadding(float padding)  { verticalPadding = padding; }

void PokemonEntryList::addEntriesFromFile(const std::string& filename, const std::string& textureDirectoryPath)
{
	std::ifstream inputFile;
	inputFile.open(filename);
	assert(!inputFile.fail() && "File could not open properly.");

	// Creating entries based on data read
	inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// Ignores header line
	while (!inputFile.eof())
	{
		// Extracting pokemon information from a line
		std::string pokemonInfo;
		std::getline(inputFile, pokemonInfo);
		std::stringstream ss(pokemonInfo);

		// Extracting pokemon name, number, and type from extracted pokemon information
		std::string name;
		std::string number;
		std::string type_token;

		ss >> name;
		ss >> number;
		ss >> type_token;

		// Extracting types
		std::vector<std::string> types;
		ss.str(type_token);
		while (std::getline(ss, type_token, ','))
			types.push_back(type_token);
		
		// Creating PokemonEntry
		std::string texturePath = textureDirectoryPath + name + std::string(".png");
		entries.emplace_back(new PokemonEntry(Images::get(texturePath), sf::String(name), sf::String(number), types));
	}
	inputFile.close();

	// Sorting, resizing, and repositioning entries
	resizeEntries();
	resizeContainer();
	repositionEntries();
}

void PokemonEntryList::setSortState(SortStateEnum type)
{
	if (getSortState() != type)
	{
		SortState::setSortState(type);
		enableState(UNSORTED);
	}
}

void PokemonEntryList::setSortDirection(SortStateEnum direction)
{
	if (getSortDirection() != direction)
	{
		SortState::setSortDirection(direction);
		enableState(UNSORTED);
	}
}

void PokemonEntryList::search(const sf::String& target)
{
	// Handles empty target
	if (target.isEmpty())
	{
		setAllVisible();
	}
	// Handles non-empty target
	else
	{
		// Handles case where target is a number
		try
		{
			unsigned targetNum = std::stoi(target.toAnsiString());

			// Checking against each entry's number
			for (PokemonEntry*& entry_ptr : entries)
			{
				// Sets entry as hidden if it does not contain target; visible, otherwise
				if (targetNum != std::stoi(entry_ptr->getNumber().toAnsiString()))
					entry_ptr->enableState(HIDDEN);
				else
					entry_ptr->disableState(HIDDEN);
			}
		}
		// Handles case where target is text
		catch (std::invalid_argument exception)
		{
			// Checking against each entry's name
			for (PokemonEntry*& entry_ptr : entries)
			{
				// Sets entry as hidden if it does not contain target; visible, otherwise
				if (!contains(entry_ptr, target))
					entry_ptr->enableState(HIDDEN);
				else
					entry_ptr->disableState(HIDDEN);
			}
		}
	}
	repositionEntries();
}

void PokemonEntryList::eventHandler(const sf::RenderWindow& window, sf::Event event)
{
	// Handling events for PokemonEntry buttons
	for (PokemonEntry*& entry_ptr : entries)
	{
		// Only event handles for buttons that are not marked as hidden
		if (!entry_ptr->checkState(HIDDEN))
			entry_ptr->eventHandler(window, event);
	}
}

void PokemonEntryList::update()
{
	// Sorts the entry list to match the sort type and direction
	if (checkState(UNSORTED))
	{
		repositionEntries();
		disableState(UNSORTED);
	}

	// Updating all PokemonEntry buttons
	for (PokemonEntry*& entry_ptr : entries)
		entry_ptr->update();
}

void PokemonEntryList::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Container::draw(target, states);

	// Drawing each all entries
	for (const PokemonEntry* p : entries)
	{
		if (!p->checkState(HIDDEN))
			target.draw(*p);
	}
}

void PokemonEntryList::onClickDetailPanel()
{
	// Applies the on click function on every entry that was pressed
	for (PokemonEntry*& entry_ptr : entries)
	{
		int pokemonNumber = std::stoi(entry_ptr->getNumber().toAnsiString());
		entry_ptr->onClick(PokemonDetailWindow::runDetailWindow, PokemonMap::get(pokemonNumber));
		entry_ptr->disableState(PRESSED);
	}

}

void PokemonEntryList::make_heap(std::vector<PokemonEntry*>& source) const
{
	unsigned state = getSortState();
	unsigned direction = getSortDirection();

	// Performs a sort based on the sort state of the entry list
	switch (state)
	{
	case LEXOGRAPHIC:
		switch (direction)
		{
		case ASCENDING:
			std::make_heap(source.begin(), source.end(), PokemonEntryLexographicA());
			break;
		case DESCENDING:
			std::make_heap(source.begin(), source.end(), PokemonEntryLexographicD());
			break;
		}
		break;
	case NUMERIC:
		switch (direction)
		{
		case ASCENDING:
			std::make_heap(source.begin(), source.end(), PokemonEntryNumericA());
			break;
		case DESCENDING:
			std::make_heap(source.begin(), source.end(), PokemonEntryNumericD());
			break;
		}
		break;
	}
}

void PokemonEntryList::pop_heap(std::vector<PokemonEntry*>& source) const
{
	unsigned state = getSortState();
	unsigned direction = getSortDirection();

	// Performs a sort based on the sort state of the entry list
	switch (state)
	{
	case LEXOGRAPHIC:
		switch (direction)
		{
		case ASCENDING:
			std::pop_heap(source.begin(), source.end(), PokemonEntryLexographicA());
			break;
		case DESCENDING:
			std::pop_heap(source.begin(), source.end(), PokemonEntryLexographicD());
			break;
		}
		break;
	case NUMERIC:
		switch (direction)
		{
		case ASCENDING:
			std::pop_heap(source.begin(), source.end(), PokemonEntryNumericA());
			break;
		case DESCENDING:
			std::pop_heap(source.begin(), source.end(), PokemonEntryNumericD());
			break;
		}
		break;
	}
}

void PokemonEntryList::resizeEntries()
{
	float widthOfAllEntryPerRow = getSize().x - (entriesPerRow + 1) * horizontalPadding;
	float widthPerEntry = widthOfAllEntryPerRow / entriesPerRow;

	// Resizes entries according to the number of entries per row
	for (PokemonEntry*& entry_ptr : entries)
		entry_ptr->setSize({ widthPerEntry, entry_ptr->getSize().y });
}

void PokemonEntryList::resizeContainer()
{
	if (!entries.empty())
	{
		unsigned row = (entries.size() / entriesPerRow) + (entries.size() % entriesPerRow > 0);
		float entryHeight = entries.at(0)->getSize().y;
		float containerHeight = (entryHeight * row) + (verticalPadding * (row + 1));
		Container::setSize({ getSize().x, containerHeight });
	}
}

void PokemonEntryList::repositionEntries()
{
	// Only repositions if there are entries
	if (entries.size() > 0)
	{
		std::vector<PokemonEntry*> heap(entries);
		make_heap(heap);

		unsigned entriesPositioned = 0;									// Tracks number of entries drawn
		float y = getPosition().y + verticalPadding;					// Tracks the starting y-position of entries on each row
		float x = getPosition().x + horizontalPadding;					// Tracks the starting x-position
		float nextX = entries.front()->getSize().x + horizontalPadding;	// Contains the distance from one entry's x-position to another's
		
		while (!heap.empty())
		{
			PokemonEntry*& entry_ptr = heap.front();

			// Only repositions the entry if it is visible
			if (!entry_ptr->checkState(HIDDEN))
			{
				entry_ptr->setPosition({ x + nextX * (entriesPositioned % entriesPerRow), y });
				++entriesPositioned;

				// Moves to the next row if number of entries on a row has been maxed out
				if (entriesPositioned % entriesPerRow == 0)
					y = entry_ptr->getPosition().y + entry_ptr->getSize().y + verticalPadding;
			}

			// Popping from the heap
			pop_heap(heap);
			heap.pop_back();
		}
	}
}

bool PokemonEntryList::contains(PokemonEntry*& source, const sf::String& target) const
{
	return source->getName().find(target) != sf::String::InvalidPos;
}

void PokemonEntryList::setAllVisible()
{
	// Sets all entries visible
	for (PokemonEntry*& entry_ptr : entries)
		entry_ptr->disableState(HIDDEN);
}
