/**
	@file
	@brief CKDSysCtrl header file
	@author tsaikd <tsaikd@gmail.com>
	@date 2007/01/16
	@attention http://svn.tsaikd.org/tsaikd/KDLib/KDClass/KDSysCtrl.h
**/

#pragma once

#ifdef KD_ENABLE_EXPORT
#include "ExportDef.h"
#endif //KD_ENABLE_EXPORT

#ifndef DLL_EXP
#define DLL_EXP
#endif //DLL_EXP

#include <shlwapi.h>

/**
	@brief Control system interface
**/
class DLL_EXP CKDSysCtrl
{
public:
	/**
		@brief Cconstructor
	**/
	CKDSysCtrl();

	/**
		@brief Add environment variable PATH at tail
		@param lpPath IN: the path you want to add
	**/
	void AddEnvPath(LPCTSTR lpPath);
	/**
		@brief Insert environment variable PATH at head
		@param lpPath IN: the path you want to insert
	**/
	void InsertEnvPath(LPCTSTR lpPath);
};