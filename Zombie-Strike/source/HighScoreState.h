
#pragma once
#include "../SGD Wrappers/SGD_Handle.h"
#include "../SGD Wrappers/SGD_String.h"
#include "IGameState.h"
#include <vector>

#include "Timer.h"

/**************************************************************/
// MainMenuState class
//	- handles the main menu
//	- SINGLETON (statically allocated, not dynamic)
class HighScoreState : public IGameState
{
public:
	/**********************************************************/
	// Singleton Accessor
	static HighScoreState* GetInstance(void);

	struct HighScore
	{
		SGD::String intials;
		unsigned int waves;

		bool operator==(const HighScore& comp)
		{
			if (this->waves > comp.waves)
				return true;
			return false;
		}
	};

	/**********************************************************/
	// IGameState Interface:
	virtual void	Enter(void)				override;	// load resources
	virtual void	Exit(void)				override;	// unload resources

	virtual bool	Input(void)				override;	// handle user input
	virtual void	Update(float elapsedTime)	override;	// update entites
	virtual void	Render(void)				override;	// render entities / menu
	void SortByScore();

private:
	/**********************************************************/
	// SINGLETON!
	HighScoreState(void) = default;
	virtual ~HighScoreState(void) = default;

	HighScoreState(const HighScoreState&) = delete;
	HighScoreState& operator= (const HighScoreState&) = delete;

	//SGD::HTexture background = SGD::INVALID_HANDLE;

	SGD::HAudio themeSong = SGD::INVALID_HANDLE;
	



	/**********************************************************/
	// Cursor Index
	
	int m_nMusicVol = 0;
	std::vector<HighScore> scores;
	Timer highscoreTimer;
	
};



