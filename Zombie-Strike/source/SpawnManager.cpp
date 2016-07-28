#include "SpawnManager.h"
#include "Spawner.h"
#include <fstream>
#include "GameplayState.h"
#include "HTPGameState.h"

using namespace std;

/*static*/ SpawnManager* SpawnManager::GetInstance(void)
{
	static SpawnManager s_Instance;	// stored in global memory once
	return &s_Instance;
}

void SpawnManager::Update(float dt)
{
	if (GameplayState::GetInstance()->GetShopState() == true && m_nNumWaves <= m_vEnemyWaves.size())
	{
		GameplayState::GetInstance()->SetShopState(false);

		m_nCurrWave++;

		m_nEnemiesKilled = 0;

		m_nNumEnemies = 0;

		if (m_nCurrWave < (int)m_vEnemyWaves.size() && Game::GetInstance()->GetCurrState() == GameplayState::GetInstance())
		{
			m_nWaveEnemies = m_vEnemyWaves[m_nCurrWave];
		}

		else
		{
			isGameWon = true;
		}
	}



	if (isActive == true) // if its on
	{
		if (m_fSpawnTimer.Update(dt)) // an the spawn timer is up
		{
			if (m_nNumEnemies < m_nWaveEnemies) // an we havent already hit the right number of enemies
			{
				int pickedSpawner = rand() % spawners.size(); // pick on of the spawners at random

				m_nZombieType = rand() % 100 + 1; // get a random number to decide type

				if (m_nZombieType % 20 == 0)				 //5% changes
					m_nZombieType = BaseObject::OBJ_TANK_ZOMBIE;
				else if (m_nZombieType % 10 == 0)				 //10% chance
					m_nZombieType = BaseObject::OBJ_FAT_ZOMBIE;

				else if (m_nZombieType % 5 == 0)						//20% chance
					m_nZombieType = BaseObject::OBJ_EXPLODING_ZOMBIE;

				else if (m_nZombieType % 2 == 0)						//20% chance
					m_nZombieType = BaseObject::OBJ_FAST_ZOMBIE;
				else
					m_nZombieType = BaseObject::OBJ_SLOW_ZOMBIE; //if its not a special, its normal


				spawners[pickedSpawner]->SpawnEnemy(m_nZombieType); // spawn it
				m_nNumEnemies++;

				float newSpawnTime = (float)(rand() % 1000) + 1.0f; // get a random spawn time
				newSpawnTime *= 0.001f; // scale it to a 0=>1.5s decimal value

				m_fSpawnTimer.AddTime(newSpawnTime); // add the time
			}
		}
	}
}
void SpawnManager::LoadFromFile(const char * fpath)
{
	int numEnemies;

	fstream lfile(fpath,ios_base::in);

	if (lfile.is_open())
	{
		while (!lfile.eof())
		{
			lfile >> numEnemies;
			m_vEnemyWaves.push_back(numEnemies);
		}

		lfile.close();
	}

	m_nNumWaves = m_vEnemyWaves.size();

	m_nWaveEnemies = m_vEnemyWaves[0];

	m_nCurrWave = 0;

	//m_vEnemyWaves.push_back(10);
	//m_vEnemyWaves.push_back(20);

}

void SpawnManager::ShutDown()
{
	spawners.clear();
	m_vEnemyWaves.clear();
	m_nWaveEnemies = 1;
	m_nNumEnemies = 0;
	m_nCurrWave = 0;
	m_nZombieType = 0;
	m_nEnemiesKilled = 0;
	m_nNumWaves = 0;
	 isActive = false;
	 isGameWon = false;
	
}



