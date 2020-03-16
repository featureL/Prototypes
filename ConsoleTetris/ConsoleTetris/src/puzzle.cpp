#include <Puzzle.h>
#include <Input.h>

#include <iostream>
#include <cassert>

namespace game_time
{
	extern std::chrono::duration<float> deltaTime;
	extern std::chrono::high_resolution_clock::time_point lastTick;
	extern std::chrono::high_resolution_clock::time_point start;

	void Init();
	void Update();
}

void Puzzle::Update()
{
	if (m_coolDownForPlayerMove == std::chrono::duration<float>::zero())
	{
		// Movement input
		if (Input::GetKeyDown('D'))
		{
			Move(Pair<int, int>(m_playerMoveSpeedX, 0));
			m_coolDownForPlayerMove = std::chrono::duration<float>(m_maxCoolDownForPlayerMove);
		}
		if (Input::GetKeyDown('A'))
		{
			Move(Pair<int, int>(-m_playerMoveSpeedX, 0));
			m_coolDownForPlayerMove = std::chrono::duration<float>(m_maxCoolDownForPlayerMove);
		}
		if (Input::GetKeyDown('W'))
		{
			Move(Pair<int, int>(0, -m_playerMoveSpeedY));
			m_coolDownForPlayerMove = std::chrono::duration<float>(m_maxCoolDownForPlayerMove);
		}
		if (Input::GetKeyDown('S'))
		{
			Move(Pair<int, int>(0, m_playerMoveSpeedY));
			m_coolDownForPlayerMove = std::chrono::duration<float>(m_maxCoolDownForPlayerMove);
		}
	}
	else
	{
		DecreaseCoolDown(m_coolDownForPlayerMove);
	}

	if (m_coolDownForRotation == std::chrono::duration<float>::zero())
	{
		// Rotation input
		if (Input::GetKeyDown('E'))
		{
			m_shape = RotateClockwise();
			m_coolDownForRotation = std::chrono::duration<float>(m_maxCoolDownForRotation);
		}
		if (Input::GetKeyDown('Q'))
		{
			m_shape = RotateCounterClockwise();
			m_coolDownForRotation = std::chrono::duration<float>(m_maxCoolDownForRotation);
		}
	}
	else
	{
		DecreaseCoolDown(m_coolDownForRotation);
	}

	MoveDownByGravity();
}

void Puzzle::Draw()
{
	for (int y = -m_shapeSize.y / 2; y <= m_shapeSize.y / 2; ++y)
	{
		for (int x = -m_shapeSize.x / 2; x <= m_shapeSize.x / 2; ++x)
		{
			int cy = y + m_shapeSize.y / 2;
			int cx = x + m_shapeSize.x / 2;

			if (m_shape[cy * m_shapeSize.x + cx] == 0x2588)
			{
				m_buffer->Set(0x2588, m_coord.x + x, m_coord.y + y);
			}
		}
	}
}

types::Shape Puzzle::GetShape() const { return m_shape; }

void Puzzle::SetBuffer(Buffer *buffer) { m_buffer = buffer; }

void Puzzle::SetGame(Game *game)
{
	m_game = game;
}

void Puzzle::SetBounds(types::Bounds &bounds)
{
	m_bounds = bounds;
}

types::Bounds Puzzle::GetBounds() const
{
	return m_bounds;
}

Game *Puzzle::GetGame() const
{
	return m_game;
}

void Puzzle::SetShape(types::Shape shape) { m_shape = shape; }

Pair<int, int> Puzzle::GetCoord() const { return m_coord; }

void Puzzle::SetCoord(const Pair<int, int> &coord) { m_coord = coord; }

void Puzzle::Move(const Pair<int, int> &move)
{
	m_coord.x += move.x;
	m_coord.y += move.y;
}

void Puzzle::SetShapeSize(const Pair<int, int> &s)
{
	m_shapeSize = s;
}

Pair<int, int> Puzzle::GetShapeSzie() const
{
	return m_shapeSize;
}

int Puzzle::GetId() const
{
	return m_id;
}

void Puzzle::SetId(int val)
{
	m_id = val;
}

types::Shape Puzzle::RotateClockwise()
{
	wchar_t *tmp = new wchar_t[m_shapeSize.x * m_shapeSize.y];
	for (int i = 0; i < m_shapeSize.x * m_shapeSize.y; ++i)
	{
		tmp[i] = m_shape[i];
	}

	for (int y = -m_shapeSize.y / 2; y <= m_shapeSize.y / 2; ++y)
	{
		for (int x = -m_shapeSize.x / 2; x <= m_shapeSize.x / 2; ++x)
		{
			int cx = x + m_shapeSize.x / 2;
			int cy = y + m_shapeSize.y / 2;

			int nx = -y;
			int ny = x;

			int cnx = nx + m_shapeSize.x / 2;
			int cny = ny + m_shapeSize.y / 2;

			std::cout << cx << ' ' << cy << ' ' << cnx << ' ' << cny << '\n';

			m_shape[cy * m_shapeSize.x + cx] = tmp[cny * m_shapeSize.x + cnx];
		}
	}

	delete[] tmp;

	return m_shape;
}

types::Shape Puzzle::RotateCounterClockwise()
{
	wchar_t *tmp = new wchar_t[m_shapeSize.x * m_shapeSize.y];
	for (int i = 0; i < m_shapeSize.x * m_shapeSize.y; ++i)
	{
		tmp[i] = m_shape[i];
	}

	for (int y = -m_shapeSize.y / 2; y <= m_shapeSize.y / 2; ++y)
	{
		for (int x = -m_shapeSize.x / 2; x <= m_shapeSize.x / 2; ++x)
		{
			int cx = x + m_shapeSize.x / 2;
			int cy = y + m_shapeSize.y / 2;

			int nx = y;
			int ny = -x;

			int cnx = nx + m_shapeSize.x / 2;
			int cny = ny + m_shapeSize.y / 2;

			std::cout << cx << ' ' << cy << ' ' << cnx << ' ' << cny << '\n';

			m_shape[cy * m_shapeSize.x + cx] = tmp[cny * m_shapeSize.x + cnx];
		}
	}

	delete[] tmp;

	return m_shape;
}

void Puzzle::MoveDownByGravity()
{
	if (m_coolDownMoveDownByGravity == std::chrono::duration<float>::zero())
	{
		Move(Pair<int, int>{0, m_GRAVITY});
		m_coolDownMoveDownByGravity = std::chrono::duration<float>(m_MAX_COOL_DOWN_FOR_MOVE_BY_GRAVITY);
	}
	else
	{
		DecreaseCoolDown(m_coolDownMoveDownByGravity);
	}
}

void Puzzle::DecreaseCoolDown(std::chrono::duration<float> &coolDown)
{
	coolDown -= game_time::deltaTime;
	if (coolDown.count() <= 0.0f)
	{
		coolDown = std::chrono::duration<float>::zero();
	}
}
