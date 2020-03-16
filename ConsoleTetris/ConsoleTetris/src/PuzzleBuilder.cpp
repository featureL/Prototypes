#include <PuzzleBuilder.h>

PuzzleBuilder::PuzzleBuilder(Buffer *buffer, const Pair<int, int> &shapeSize) :
	m_buffer(buffer)
	, m_shapeSize(shapeSize)
{}

Puzzle *PuzzleBuilder::Build(
	types::Shape shape
	, const Pair<int, int> &coord)
{
	Puzzle *p = new Puzzle();
	p->SetBuffer(m_buffer);
	p->SetCoord(coord);
	p->SetShape(shape);
	p->SetShapeSize(m_shapeSize);
	p->SetBoundingRect(p->CalculateBoundingRectByShape(shape));
	p->SetId(m_puzzleCount++);
	p->SetGame(m_game);
	++m_puzzleCount;

	return p;
}

void PuzzleBuilder::Destroy(IElement *element)
{
	--m_puzzleCount;
	delete element;
}

void PuzzleBuilder::SetGame(Game *game)
{
	m_game = game;
}

Game *PuzzleBuilder::GetGame() const
{
	return m_game;
}



