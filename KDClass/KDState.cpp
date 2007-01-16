#include "stdafx.h"

#include "KDState.h"

CKDState::CKDState()
{
	InitState();
}

bool CKDState::SetState(UINT uState, bool bEnable/* = true*/)
{
	if (bEnable) {
		m_uState |= uState;
	} else {
		UINT uMask;
		int i;
		for (i=0 ; i<(sizeof(UINT)<<3) ; i++) {
			if (1 == (uState >> i))
				break;
		}
		uMask = 1 << i;
		m_uState &= ~uMask;
	}

	return bEnable;
}
