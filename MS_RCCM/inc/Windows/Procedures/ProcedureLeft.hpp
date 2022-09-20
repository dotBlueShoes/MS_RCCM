#pragma once

namespace windows::windowLeft {
	
	HWND hTab;
	
	#define ID_TAB_ZW 1
	#define ID_TAB_ST 0
	
	proceeded stdcall Procedure(
		winapi::windowHandle window,
		input message,
		winapi::messageW wArgument,
		winapi::messageL lArgument
	) {
		switch (message) { 
		
			case input::Create: {
				//windows::CreateEditor(mainProcess, window);
				if constexpr (DEBUG) debug::LogInfo("(CALL) Window-Left:Event-Create");
				return proceeded::True;
			}
				
			case (winapi::window::input)WM_NOTIFY: {
				LPNMHDR n = (LPNMHDR)lArgument;
				if (n->code == TCN_SELCHANGE && n->hwndFrom == hTab) { // Sprawdza, czy uchwyt pochodzi od hTab
					int index = TabCtrl_GetCurSel(hTab);
					switch( index ) { // indeks aktualnej kontrolki
						case ID_TAB_ST:
							if constexpr (DEBUG) debug::LogInfo("(TABEVENT) ID_TAB_ST");
							//ShowWindow( hEdit, SW_SHOW );
							//ShowWindow( hRadioButton, SW_HIDE );
							break;
						case ID_TAB_ZW:
							if constexpr (DEBUG) debug::LogInfo("(TABEVENT) ID_TAB_ZW");
							//ShowWindow( hEdit, SW_HIDE );
							//ShowWindow( hRadioButton, SW_SHOW );
							break;
							//itd.
					}
				}
				return proceeded::False;
			}
			
			default:
				return (proceeded)DefWindowProcW(window, (uint32)message, wArgument, lArgument);
		}
	}
	
}
