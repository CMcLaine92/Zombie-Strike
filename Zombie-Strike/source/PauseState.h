#pragma once
#include "IGameState.h"



class PauseState : public IGameState
{
public:

	static PauseState* GetInstance(void);


	virtual void	Enter(void)				override;
	virtual void	Exit(void)				override;

	virtual bool	Input(void)				override;
	virtual void	Update(float elapsedTime)	override;
	virtual void	Render(void)				override;


private:

	PauseState(void) = default;
	virtual ~PauseState(void) = default;

	PauseState(const PauseState&) = delete;
	PauseState& operator= (const PauseState&) = delete;




	int m_nCursor = 0;

};