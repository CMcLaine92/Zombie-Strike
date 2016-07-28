#pragma once
#include "BaseObject.h"
#include "Timer.h"

class Spawner : public BaseObject
{
public:
	enum EnemyTypes { SLOW_ZOMBIE, FAST_ZOMBIE, FAT_ZOMBIE };

	Spawner();
	virtual ~Spawner();


	void SpawnEnemy(int type);

	

	virtual int	GetType(void) const override { return OBJ_SPAWNER; }
	SGD::Rectangle GetRect(void) const { return SGD::Rectangle(); }

	//int GetEnemyType(void) const { return m_nEnemyType; }
	//int GetNumEnemies(void) const { return m_nNumEnemies; }
	//int GetNumWaveEnemies(void) const { return m_nWaveEnemies; }

	//void SetEnemyType(int enemyType){ m_nEnemyType = enemyType; }
	//void SetNumEnemies(int enemyNum) { m_nNumEnemies = enemyNum; }
	//void SetWaveEnemies(int waveEnemies) { m_nWaveEnemies = waveEnemies; }
	//void SetMaxSpawnedEnemies(int maxSpawned) { m_nMaxEnemies = maxSpawned; }
	//


};

