#pragma once

namespace windows::windowRight {
	
	winapi::rect previousWindowPosition;
	
	proceeded stdcall Procedure(
		winapi::windowHandle window,
		input message,
		winapi::messageW wArgument,
		winapi::messageL lArgument
	) {
		switch (message) { 
				
			case input::Create: {
				DEBUG logger::Info("(CALL) Window-Right:Event-Create");
				return proceeded::True;
			}
			
			default:
				return (proceeded)DefWindowProcW(window, (uint32)message, wArgument, lArgument);
		}
	}
	
	namespace inner {
		proceeded stdcall Pprocedure(
			winapi::windowHandle window,
			input message,
			winapi::messageW wArgument,
			winapi::messageL lArgument
		) {
			switch (message) { 
					
				case input::Create: {
					DEBUG logger::Info("(CALL) Window-Inner:Event-Create");
					return proceeded::True;
				}
				
				default:
					return (proceeded)DefWindowProcW(window, (uint32)message, wArgument, lArgument);
			}
		}
	}
	
}