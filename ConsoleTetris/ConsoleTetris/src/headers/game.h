#pragma once

#include <interfaces/ibuilder.h>
#include <interfaces/idrawable.h>
#include <interfaces/ielement.h>
#include <interfaces/ipage.h>

#include <unordered_map>
#include <memory>

class MainPage;
class Buffer;
class Game
{
public:
	Game();
	Game(IBuilder *puzzleBuilder, Buffer *buffer);
	~Game();

	void Run();
	void Spawn();
	void GameOver();

	void AddElementToScene(IElement *element);
	void RemoveElementFromScene(IElement *element);

	void AddPuzzle(IElement *element);
	void RemovePuzzle(IElement *element);

	void FillCells(IElement *element);

	bool IsGameOver() const;
	void SetGameOver(bool value);

	void SetCurrentPage(IPage *value);
	void StartGame();
private:
	const int ESC = 27;

	const int ScoresForRow = 5;

	Pair<std::string, int> m_playerStats;
	bool m_isInGame;

	IPage *m_currentPage;

	MainPage *m_mainPage;

	bool m_gameOver;
	IBuilder *m_puzzleBuilder;

	Buffer *m_buffer;
	std::vector<IElement *> m_puzzles;
	std::unordered_map<int, IElement *> m_updateables;
	std::unordered_map<int, IDrawable *> m_drawables;

	std::vector<int> m_elementsToBeRemovedIds;

	void RemoveElements();
	bool IsRowFilled(int row) const;
	void DeleteFilledRows();
	void DrawPlayerInfo();
};