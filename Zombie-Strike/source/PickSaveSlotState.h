#pragma once
#include "IGameState.h"
#include <ctime>
#include "GamerProfile.h"
class PickSaveSlotState : public IGameState
{
public:
	enum MenuItems { SAVE1, SAVE2, SAVE3, EXIT_2 };
	enum States { NEW_GAME, LOAD_GAME, DELETE_SAVES, EXIT_1};
	static PickSaveSlotState* GetInstance(void);



	virtual void	Enter(void);
	virtual void	Exit(void);

	virtual bool	Input(void);
	virtual void	Update(float elapsedTime);
	virtual void	Render(void);


private:

	PickSaveSlotState(void) = default;
	virtual ~PickSaveSlotState(void) = default;

	PickSaveSlotState(const PickSaveSlotState&) = delete;
	PickSaveSlotState& operator= (const PickSaveSlotState&) = delete;


	
	bool modeChosen = false;
	int currState = 0;
	int		m_nCursor = 0;

	GamerProfile profiles[3];
	tm times[3];
};

