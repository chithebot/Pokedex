#ifndef SFML_GUI_PROJECT_POKEMON_ENTRY_LIST_H
#define SFML_GUI_PROJECT_POKEMON_ENTRY_LIST_H

#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include "PokemonDetailWindow.h"
#include "PokemonEntryComparison.h"
#include "EntryList.h"

class PokemonEntryList : public Container, public EntryList, public EventHandler, public States
{
public:
	PokemonEntryList();
	PokemonEntryList(const sf::Vector2f& size, unsigned entriesPerRow = 4,
		float horizontalPadding = 12.5f, float verticalPadding = 25.f, unsigned characterSize = 16);
	~PokemonEntryList();

	float getEntryHeight() const;
	unsigned getCharacterSize() const;
	unsigned getNumEntriesPerRow() const;
	float getHorizonalPadding() const;
	float getVerticalPadding() const;

	void setSize(const sf::Vector2f& size);
	void setEntryHeight(float height);
	void setCharacterSize(unsigned size);
	void setNumEntriesPerRow(unsigned numEntries);
	void setHorizonalPadding(float padding);
	void setVerticalPadding(float padding);
	void addEntriesFromFile(const std::string& filename,
		const std::string& textureDirectoryPath);
	void setSortState(SortStateEnum type);
	void setSortDirection(SortStateEnum direction);
	void search(const sf::String& target);

	void eventHandler(const sf::RenderWindow& window, sf::Event event) override;
	void update() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void onClickDetailPanel();
private:
	void make_heap(std::vector<PokemonEntry*>& source) const;
	void pop_heap(std::vector<PokemonEntry*>& source) const;
	void resizeEntries();
	void resizeContainer();
	void repositionEntries();
	bool contains(PokemonEntry*& source, const sf::String& target) const;
	void setAllVisible();
private:
	std::vector<PokemonEntry*> entries;
	unsigned characterSize;
	unsigned entriesPerRow;
	float horizontalPadding;
	float verticalPadding;
};

#endif // SFML_GUI_PROJECT_POKEMON_ENTRY_LIST_H
