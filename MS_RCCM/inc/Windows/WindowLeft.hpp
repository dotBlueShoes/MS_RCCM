#pragma once
#include "Procedures/ProcedureLeft.hpp"

namespace windows::windowLeft {
	
	const winapi::windowHandle Create(
		const winapi::handleInstance& process,
		const winapi::windowHandle& parentWindow,
		const winapi::brushHandle& backgroundBrush,
		const vector2<uint64> & parentOffset,
		const int32& windowState
	) {	
		const array<winapi::wchar, 11> className ( L"WindowLeft" );
		const vector2<uint64> 
			windowLeftSize ( 700 - parentOffset.x, 800 - parentOffset.y),
			windowLeftOffset ( 0, 0 );
			
		if constexpr (DEBUG) debug::LogInfo("(CALL) Window-Left:Create");
				
		{
			const winapi::windowHandle window (
				CreateChildWindow (
					process, 
					parentWindow, 
					(winapi::windowProcedure)Procedure, 
					(HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED),
					className.Pointer(),
					backgroundBrush,
					windowState,
					windowLeftOffset,
					windowLeftSize
				)
			);
			
			if constexpr (DEBUG)
				// ERROR HANDLING
				if (window == NULL) debug::LogError("Window not created!");
				
			/// TabControl Kontrolka
			{
				// 
				hTab = CreateWindowExW( 0, WC_TABCONTROLW, 0, WS_CHILD | WS_VISIBLE /*|TCS_FIXEDWIDTH*/,
					0, 0, 544, 375, window, 0, process, NULL );
				
				if constexpr (DEBUG)
				// ERROR HANDLING
					if (hTab == NULL) debug::LogError("Window not created!");
					
				/// For fixedwidth to set the fixedwidth
				//SNDMSG(hTab, TCM_SETITEMSIZE, 0, MAKELPARAM(150, 20));
				
				TCITEMW tci1, tci2;
				
				array<winapi::wchar, 15> text1 ( L"Ten Użytkownik" );
				array<winapi::wchar, 20> text2 ( L"Wszyscy Użytkownicy" );
				
				tci1.mask = TCIF_TEXT;
				tci2.mask = TCIF_TEXT;
				tci1.pszText = text1.Pointer();
				tci2.pszText = text2.Pointer();
				tci1.cchTextMax = text1.Length();
				tci2.cchTextMax = text2.Length();
				
				SNDMSG(hTab, TCM_INSERTITEMW, (WPARAM)ID_TAB_ZW, (LPARAM)(const TC_ITEMW *)(&tci1));
				SNDMSG(hTab, TCM_INSERTITEMW, (WPARAM)ID_TAB_ST, (LPARAM)(const TC_ITEMW *)(&tci2));
			}
				
			return window;
		}
	}
	
}
