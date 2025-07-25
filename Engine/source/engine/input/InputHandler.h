#pragma once
#include "../interface/InterfaceEngine.h"

class InputHandler {
public:
	explicit InputHandler(InterfaceEngine& uiEngine) : m_uiEngine(uiEngine) {}

	void HandleKey(int key, int action, int mods) const;

private:
	InterfaceEngine& m_uiEngine;

};