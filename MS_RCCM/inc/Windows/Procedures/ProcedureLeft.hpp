#pragma once

namespace windows::windowLeft {
	
	///Outter
	winapi::windowHandle hTab;
	/// Must start from 0
	#define ID_TAB_0 0
	#define ID_TAB_1 1
	
	///Inner
	winapi::windowHandle innerTab;
	/// Must start from 0
	#define ID_TAB_I_0 0
	#define ID_TAB_I_1 1
	#define ID_TAB_I_2 2
	#define ID_TAB_I_3 3
	
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
				LPNMHDR notyfication ( (LPNMHDR)lArgument );
				if (notyfication->code == TCN_SELCHANGE) {
					if (notyfication->hwndFrom == hTab) {						/// Sprawdza, czy uchwyt pochodzi od hTab
						const int index ( SendMessage(hTab, TCM_GETCURSEL, 0, 0) ); /// Indeks aktualnej kontrolki, Get Current Selected
						switch( index ) { 															
							case ID_TAB_0:
								if constexpr (DEBUG) debug::LogInfo("(TABEVENT) ID_TAB_0");
								//ShowWindow( hEdit, SW_SHOW );
								//ShowWindow( hRadioButton, SW_HIDE );
								break;
							case ID_TAB_1:
								if constexpr (DEBUG) debug::LogInfo("(TABEVENT) ID_TAB_1");
								//ShowWindow( hEdit, SW_HIDE );
								//ShowWindow( hRadioButton, SW_SHOW );
								break;
								//itd.
						}
					} else if (notyfication->hwndFrom == innerTab) {
						const int index ( SendMessage(innerTab, TCM_GETCURSEL, 0, 0) ); /// Indeks aktualnej kontrolki, Get Current Selected
						switch( index ) { 
							case ID_TAB_I_0:
								if constexpr (DEBUG) debug::LogInfo("(TABEVENT) ID_TAB_I_0");
								//ShowWindow( hEdit, SW_SHOW );
								//ShowWindow( hRadioButton, SW_HIDE );
								break;
							case ID_TAB_I_1:
								if constexpr (DEBUG) debug::LogInfo("(TABEVENT) ID_TAB_I_1");
								//ShowWindow( hEdit, SW_HIDE );
								//ShowWindow( hRadioButton, SW_SHOW );
								break;
								//itd.
							case ID_TAB_I_2:
								if constexpr (DEBUG) debug::LogInfo("(TABEVENT) ID_TAB_I_2");
								//ShowWindow( hEdit, SW_SHOW );
								//ShowWindow( hRadioButton, SW_HIDE );
								break;
							case ID_TAB_I_3:
								if constexpr (DEBUG) debug::LogInfo("(TABEVENT) ID_TAB_I_3");
								//ShowWindow( hEdit, SW_HIDE );
								//ShowWindow( hRadioButton, SW_SHOW );
								break;
								//itd.
						}
					}
				}
				return proceeded::False;
			}
			
			default:
				return (proceeded)DefWindowProcW(window, (uint32)message, wArgument, lArgument);
		}
	}
	
}
