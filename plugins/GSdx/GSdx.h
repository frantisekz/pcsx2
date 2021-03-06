/*
 *	Copyright (C) 2007-2009 Gabest
 *	http://www.gabest.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#pragma once

#include "GSSetting.h"
#include "GS.h"

class GSdxApp
{
	std::string m_ini;
	std::string m_section;
	std::map< std::string, std::string > m_default_configuration;
#if defined(__unix__)
	std::map< std::string, std::string > m_configuration_map;
#endif
	GSRendererType m_current_renderer_type;

public:
	GSdxApp();

	void Init();
	void* GetModuleHandlePtr();

#ifdef _WIN32
 	HMODULE GetModuleHandle() {return (HMODULE)GetModuleHandlePtr();}
#endif

#if defined(__unix__)
	void BuildConfigurationMap(const char* lpFileName);
	void ReloadConfig();

	size_t GetPrivateProfileString(const char* lpAppName, const char* lpKeyName, const char* lpDefault, char* lpReturnedString, size_t nSize, const char* lpFileName);
	bool WritePrivateProfileString(const char* lpAppName, const char* lpKeyName, const char* pString, const char* lpFileName);
	int GetPrivateProfileInt(const char* lpAppName, const char* lpKeyName, int nDefault, const char* lpFileName);
#endif

	bool LoadResource(int id, std::vector<char>& buff, const char* type = nullptr);

	void SetConfig(const char* entry, const char* value);
	void SetConfig(const char* entry, int value);
	// Avoid issue with overloading
	template<typename T>
	T      GetConfigT(const char* entry) { return static_cast<T>(GetConfigI(entry)); }
	int    GetConfigI(const char* entry);
	bool   GetConfigB(const char* entry);
	string GetConfigS(const char* entry);

	void SetCurrentRendererType(GSRendererType type);
	GSRendererType GetCurrentRendererType();

	void SetConfigDir(const char* dir);

	vector<GSSetting> m_gs_renderers;
	vector<GSSetting> m_gs_interlace;
	vector<GSSetting> m_gs_aspectratio;
	vector<GSSetting> m_gs_upscale_multiplier;
	vector<GSSetting> m_gs_max_anisotropy;
	vector<GSSetting> m_gs_bifilter;
	vector<GSSetting> m_gs_trifilter;
	vector<GSSetting> m_gs_gl_ext;
	vector<GSSetting> m_gs_hack;
	vector<GSSetting> m_gs_offset_hack;
	vector<GSSetting> m_gs_hw_mipmapping;
	vector<GSSetting> m_gs_crc_level;
	vector<GSSetting> m_gs_acc_blend_level;
	vector<GSSetting> m_gs_tv_shaders;

	vector<GSSetting> m_gpu_renderers;
	vector<GSSetting> m_gpu_filter;
	vector<GSSetting> m_gpu_dithering;
	vector<GSSetting> m_gpu_aspectratio;
	vector<GSSetting> m_gpu_scale;
};

struct GSDXError {};
struct GSDXRecoverableError : GSDXError {};

extern GSdxApp theApp;
