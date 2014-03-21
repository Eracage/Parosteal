#pragma once
#ifndef INPUT_H_UTH
#define INPUT_H_UTH

#include <UtH/Platform/Singleton.hpp>
#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/Configuration.hpp>

#if defined(UTH_SYSTEM_ANDROID)
	//#include <UtH/Platform/Android/InputCommon.hpp>
	//#include <UtH/Platform/Android/InputKeyboard.hpp>
	//#include <UtH/Platform/Android/InputMouse.hpp>
	//#include <UtH/Platform/Android/InputTouch.hpp>
#elif defined(UTH_SYSTEM_WINDOWS)
	#include <UtH/Platform/Win32/InputCommon.hpp>
	#include <UtH/Platform/Win32/InputKeyboard.hpp>
	#include <UtH/Platform/Win32/InputMouse.hpp>
	#include <UtH/Platform/Win32/InputTouch.hpp>
#elif defined(UTH_SYSTEM_LINUX)
    #include <UtH/Platform/Win32/InputCommon.hpp>
    #include <UtH/Platform/Win32/InputKeyboard.hpp>
    #include <UtH/Platform/Win32/InputMouse.hpp>
    #include <UtH/Platform/Win32/InputTouch.hpp>
#else
	#error No input for such platform
#endif

#define UTHInput uth::Input::getInstance()

namespace uth
{
	class Input : public Singleton<Input>
	{
		Input();
		~Input();
		friend class Singleton<Input>;
	public:
		MouseInput Mouse;
		TouchInput Touch;
		KeyboardInput Keyboard;
		CommonInput Common;

		void Update();
		void SetWindow(void *windowHandle);
	private:
		void *m_windowHandle;
		friend class UtHEngine;
	};
}

#endif