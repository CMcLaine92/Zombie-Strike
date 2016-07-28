#pragma once

#include "Map.h"

#include "IBase.h"
#include "Graph.h"
#include "GamerProfile.h"
#include "Game.h"
#include <string>
#include <vector>
#include <map>

#define NUM_LEVELS 6
using namespace std;
class BaseObject;
class EntityManager;
class Player;
class EnemyUnit;
class BarbedWire;
class SandBag;
class LandMine;


struct TileSets
{
	Tile pTiles;
	Tile edges;
	Layer layers;
	SGD::Size tileSize;
	Map map;
};


class MapManager : public IBase
{
	TileSets tStruct;
	SGD::HTexture tileTexture = SGD::INVALID_HANDLE;
	std::string levels[NUM_LEVELS];
	int startRow, startCol, endRow, endCol;

	std::vector<SandBag*> sandBags;
	std::vector<BarbedWire*> barbedWires;
	std::vector<LandMine*> landMines;

	GamerProfile profile;

	unsigned int currMine = 0;
	unsigned int currBarbWire = 0;
	unsigned int currSandBag = 0;

	
public:

	static MapManager * GetInstance(void);

	BaseObject*				LoadLevel		( GamerProfile& currProfile, EntityManager* );
	void					UnloadLevel		(void);

	virtual void			Render			(void)							override;
	virtual void			Update			(float elapsedTime)				override;
	virtual void			HandleCollision	(const IBase* pOther)			override;
	virtual int				GetType			(void)					const	override	{ return 10; }
	virtual SGD::Rectangle	GetRect			(void)					const	override	{ return SGD::Rectangle(0.0f, 0.0f, 0.0f, 0.0f); }
	virtual void			AddRef			(void)							override	{};
	virtual void			Release			(void)							override	{};

	std::vector<SandBag*>& GetSandBags(void) { return sandBags; }
	std::vector<LandMine*>& GetLandMines(void) { return landMines; }
	std::vector<BarbedWire*>& GetBaredWire(void) { return barbedWires; }


	SGD::HTexture			GetMapTexture	(void)					{ return tileTexture; }
	void					SetMapTexture	(SGD::HTexture hText)	{ tileTexture = hText; }

	void					UnloadTexture	(SGD::HTexture);
	void					LoadLevelPaths	(void);


	Player* CreatePlayer(int type, SGD::Point pos, EntityManager*);
	void CreateLandMine(SGD::Point pos,  EntityManager* entities);
	void CreateSandBags(SGD::Point pos, EntityManager* entities);
	void CreateBarbedWire(SGD::Point pos, EntityManager* entities);
	void CreateEnvironment(SGD::Point pos, EntityManager* entities, int type);
	void CreateSpawner(SGD::Point pos, EntityManager* entities);

	void CreateHouse(SGD::Point pos, EntityManager* entities);



};



