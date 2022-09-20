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
				hTab = CreateWindowExW( 0, WC_TABCONTROLW, 0, WS_CHILD | WS_VISIBLE /*|TCS_FIXEDWIDTH*/,
					0, 0, 544, 375, window, 0, process, NULL );
				
				if constexpr (DEBUG)
				// ERROR HANDLING
					if (hTab == NULL) debug::LogError("Window not created!");
					
				/// For fixedwidth to set the fixedwidth
				//SendMessage(hTab, TCM_SETITEMSIZE, 0, MAKELPARAM(150, 20));
				
				TCITEMW tci1, tci2;
				
				array<winapi::wchar, 15> text1 ( L"Ten Użytkownik" );
				array<winapi::wchar, 20> text2 ( L"Wszyscy Użytkownicy" );
				
				tci1.mask = TCIF_TEXT;
				tci2.mask = TCIF_TEXT;
				tci1.pszText = text1.Pointer();
				tci2.pszText = text2.Pointer();
				tci1.cchTextMax = text1.Length();
				tci2.cchTextMax = text2.Length();
				
				SendMessage(hTab, TCM_INSERTITEMW, (WPARAM)ID_TAB_0, (LPARAM)(const TC_ITEMW *)(&tci1));
				SendMessage(hTab, TCM_INSERTITEMW, (WPARAM)ID_TAB_1, (LPARAM)(const TC_ITEMW *)(&tci2));
				
				/// TabControl Kontrolka Inner
				{
					innerTab = CreateWindowExW(0, WC_TABCONTROLW, 0, WS_CHILD | WS_VISIBLE, 10, 23, 544, 375, window, 0, process, NULL);
					//SetWindowSubclass(innerTab, (SUBCLASSPROC)&InnerTabProcedure, 50, 0);
					
					if constexpr (DEBUG)
					// ERROR HANDLING
						if (innerTab == NULL) debug::LogError("Window not created!");
						
					/// For fixedwidth to set the fixedwidth
					//SendMessage(innerTab, TCM_SETITEMSIZE, 0, MAKELPARAM(150, 20));
					
					TCITEMW atci1, atci2, atci3, atci4;
					
					array<winapi::wchar, 7>	 atext1 ( L"Folder" );
					array<winapi::wchar, 11> atext2 ( L"Biblioteka" );
					array<winapi::wchar, 5>  atext3 ( L"Plik" );
					array<winapi::wchar, 10> atext4 ( L"Plik Typu" );
					
					atci1.mask = TCIF_TEXT;
					atci2.mask = TCIF_TEXT;
					atci3.mask = TCIF_TEXT;
					atci4.mask = TCIF_TEXT;
					atci1.pszText = atext1.Pointer();
					atci2.pszText = atext2.Pointer();
					atci3.pszText = atext3.Pointer();
					atci4.pszText = atext4.Pointer();
					atci1.cchTextMax = atext1.Length();
					atci2.cchTextMax = atext2.Length();
					atci3.cchTextMax = atext3.Length();
					atci4.cchTextMax = atext4.Length();
					
					SendMessage(innerTab, TCM_INSERTITEMW, (WPARAM)ID_TAB_I_0, (LPARAM)(const TC_ITEMW *)(&atci1));
					SendMessage(innerTab, TCM_INSERTITEMW, (WPARAM)ID_TAB_I_1, (LPARAM)(const TC_ITEMW *)(&atci2));
					SendMessage(innerTab, TCM_INSERTITEMW, (WPARAM)ID_TAB_I_2, (LPARAM)(const TC_ITEMW *)(&atci3));
					SendMessage(innerTab, TCM_INSERTITEMW, (WPARAM)ID_TAB_I_3, (LPARAM)(const TC_ITEMW *)(&atci4));
					
					SetWindowPos(
						innerTab,
						HWND_TOP, // get to the top of z-order
						NULL,
						NULL,
						NULL,
						NULL,
						SWP_NOMOVE | SWP_NOSIZE // x, y offset ans size doesn't metter
					);
				}
				
			}
				
			return window;
		}
	}
	
}
