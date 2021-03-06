/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#pragma once

#include "VisualEffectBlock.h"
#include <EASTL\vector.h>

using namespace eastl;

namespace Swarm
{
	namespace Components
	{
		class VisualEffect
		{
		public:
			VisualEffect();

			/* 00h */	int flags;
			/* 04h */	int componentAppFlagsMask;
			/* 08h */	unsigned long notifyMessageID;
			/* 0Ch */	float screenSizeRange[2];
			/* 14h */	float cursorActiveDistance;
			/* 18h */	char cursorButton;
			/* 1Ch */	vector<float> lodDistances;
			/* 30h */	float extendedLodWeights[3];
			float field_3C;
			/* 40h */	int seed;
			/* 44h */	vector<VisualEffectBlock> blocks;
		};

		static_assert(sizeof(VisualEffect) == 0x58, "sizeof(VisualEffect) == 58h");
	}
}