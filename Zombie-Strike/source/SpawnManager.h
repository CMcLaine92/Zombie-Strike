#pragma once
#include <vector>
#include "Timer.h"

class Spawner;

class SpawnManager
{
public:
	static SpawnManager* GetInstance(void);

	bool		Initialize(void);
	bool		Terminate(void);

	std::vector<Spawner*>& GetSpawnVector() { return spawners; }

	void Update(float dt);

	void ShutDown();


	unsigned int GetNumWaves(void) const { return m_nNumWaves; }
	int GetEnemyType(void) const { return m_nZombieType; }
	int GetNumEnemies(void) const { return m_nNumEnemies; }
	int GetNumWaveEnemies(void) const { return m_nWaveEnemies; }
	int GetEnemiesKilled(void) const { return m_nEnemiesKilled; }
	int GetCurrWave(void) const { return m_nCurrWave; }
	bool GetGameWon(void) const { return isGameWon; }

	void SetNumWaves(unsigned int nwaves) { m_nNumWaves = nwaves; }
	void SetEnemiesKilled(int ekilled) { m_nEnemiesKilled = ekilled; }
	void SetCurrWave(int wave) { m_nCurrWave = wave; }

	void SetEnemyType(int enemyType){ m_nZombieType = enemyType; }
	void SetNumEnemies(int enemyNum) { m_nNumEnemies = enemyNum; }
	void SetWaveEnemies(int waveEnemies) { m_nWaveEnemies = waveEnemies; }
	void Activate(void) { isActive = true; }
	void Deactivate(void) { isActive = false; }
	void LoadFromFile(const char * fpath);
	void SetGameWon(bool gamewon) { isGameWon = gamewon; }

private:

	SpawnManager() = default;
	~SpawnManager() = default;

	SpawnManager(const SpawnManager&) = delete;
	SpawnManager&	operator=	(const SpawnManager&) = delete;

	int m_nWaveEnemies = 1;
	int m_nNumEnemies = 0;
	int m_nCurrWave = 0;
	int m_nZombieType = 0;
	int m_nEnemiesKilled = 0;
	Timer m_fSpawnTimer;
	unsigned int m_nNumWaves = 0;
	bool isActive = false;
	bool isGameWon = false;

	std::vector<Spawner*> spawners;
	std::vector<int> m_vEnemyWaves;
};

