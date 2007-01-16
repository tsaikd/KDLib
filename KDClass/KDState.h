#pragma once

#include "ExportDef.h"

class DLL_EXP CKDState
{
public:
	CKDState();

	inline void InitState() { m_uState = 0; }
	inline bool HasState(UINT uState) { return (uState == (uState & m_uState)) ? true : false; }

protected:
	bool SetState(UINT uState, bool bEnable = true);

	/*
	enum {
		STATE_OK					= (1 << 0),
		STATE_EXAMPLE				= (1 << 1) | STATE_OK, // means STATE_OK imply STATE_EXAMPLE
		STATE_MAX					= UINT_MAX
	};
	*/

	UINT m_uState;
};