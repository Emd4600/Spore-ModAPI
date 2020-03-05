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

#include <Spore\MathUtils.h>
#include <Spore\Transform.h>
#include <Spore\Graphics\IRenderTargetManager.h>
#include <d3d9types.h>

using namespace Math;

namespace App
{
	class cViewer
	{
	public:
		bool Initialize(bool);

		///
		/// Clears one or more surfaces such as the render target, the depth buffer or the stencil buffer.
		/// This calls the IDirect3DDevice9::Clear() method using this Viewer background color.
		/// It will also call IDirect3DDevice9::SetViewport() if the current viewport is not that from the viewer.
		/// @param flags A combination of flags in the D3DCLEAR enum.
		/// @returns true If the operation was carried out successfully.
		bool ClearScene(int8_t flags);

		bool LoadTransformations();

		///
		/// Sets the background color that is shown in the background of the scene.
		/// More exactly, this is the color used to clear the scene.
		/// @param color
		void SetBackgroundColor(const Math::ColorRGBA& color);

		float GetNearPlane() const;
		float GetFarPlane() const;

		void SetNearPlane(float fValue);
		void SetFarPlane(float fValue);

		void SetAspectRatio(float fValue);

		void SetCameraMaterialLODs(const Vector4& values);
		Vector4 GetCameraMaterialLODs() const;

		void SetRenderType(int renderType, bool = 0);

		/// Sets the camera position and direction.
		/// @param transform The transform applied to the camera.
		void SetCameraTransform(const Transform& transform);

		Transform GetViewTransform() const;

		///
		/// Just calls GetCameraToPoint() for the current mouse coordinates.
		/// @param cameraPosition [Output]
		/// @param direction [Output]
		bool GetCameraToMouse(Vector3& cameraPosition, Vector3& direction) const;

		///
		///
		/// @param x
		/// @param y
		/// @param cameraPosition [Output]
		/// @param direction [Output]
		// direction is a normalized vector
		bool GetCameraToPoint(float x, float y, Vector3& cameraPosition, Vector3& direction) const;

		D3DVIEWPORT9 GetViewport() const;

	public:
		struct Camera
		{
		public:
			/* 00h */	Matrix4 worldToCameraTranspose;
			/* 40h */	Graphics::RTT* renderTargets[4];
			/* 50h */	Graphics::RTT* depthStencilSurface;
			/* 54h */	char _padding_54[0x8];
			/* 5Ch */	float field_5C;
			/* 60h */	float field_60;
			/* 64h */	float scaleX;
			/* 68h */	float scaleY;
			/* 6Ch */	int field_6C;  // 1 2 or 3, used to set projection matrix
			/* 70h */	float nearPlane;
			/* 74h */	float farPlane;
			/* 78h */	D3DVIEWPORT9 viewport;
			/* 90h */	int field_90;
			/* 94h */	int stencilBitDepth;
		};

		/* 00h */	Matrix4 viewTransform;
		/* 40h */	Matrix4 field_40;
		/* 80h */	Matrix4 field_80;
		/* C0h */	Matrix4 field_C0;
		/* 100h */	Matrix4 field_100;
		/* 140h */	ColorRGBA backgroundColor;
		/* 150h */	int renderType;  // 0xF -> hologram!
		/* 154h */	bool field_154;  // related to renderType, a char/bool?
		/* 158h */	int field_158;  // this points to a structure made of field_154 and renderType, it's used in shader const 0x201 (used when selecting shaders)
		/* 15Ch */	float cameraMaterialLODs[4];
		/* 16Ch */	bool field_16C;
		/* 170h */	Camera* pCamera;

	private:
		// renamed to SetCameraTransform();
		void SetViewTransform(const Transform& transform);
	};

	inline void cViewer::SetCameraTransform(const Transform& transform) {
		SetViewTransform(transform);
	}

	inline D3DVIEWPORT9 cViewer::GetViewport() const
	{
		return pCamera->viewport;
	}

	namespace Addresses(cViewer)
	{
		DeclareAddress(SetViewTransform);
		DeclareAddress(GetViewTransform);
		DeclareAddress(Initialize);
		DeclareAddress(ClearScene);
		DeclareAddress(LoadTransformations);
		DeclareAddress(SetBackgroundColor);
		DeclareAddress(GetNearPlane);
		DeclareAddress(GetFarPlane);
		DeclareAddress(SetNearPlane);
		DeclareAddress(SetFarPlane);
		DeclareAddress(SetAspectRatio);
		DeclareAddress(SetCameraMaterialLODs);
		DeclareAddress(GetCameraMaterialLODs);
		DeclareAddress(SetRenderType);
		DeclareAddress(GetCameraToMouse);
		DeclareAddress(GetCameraToPoint);
	}
}