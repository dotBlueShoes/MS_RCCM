#pragma once
#include "Procedures/ProcedureRight.hpp"

namespace windows::windowRight {
	
	const winapi::windowHandle Create(
		const winapi::handleInstance& process,
		const winapi::windowHandle& parentWindow,
		const winapi::brushHandle& backgroundBrush,
		const vector2<uint64> & parentOffset,
		const int32& windowState
	) {	
		const array<winapi::wchar, 12> className ( L"WindowRight" );
		const vector2<uint64> 
			windowRightOffset ( 700 - parentOffset.x, 0 ), // no idea why -16
			windowRightSize	( 700 - parentOffset.x, 800 - parentOffset.y ); // 59 takes the nonuser with menu ? / i think i am able to get that number all the way here...
			
		if constexpr (DEBUG) debug::LogInfo("(CALL) Window-Right:Create");
				
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
					windowRightOffset,
					windowRightSize
				)
			);
			
			if constexpr (DEBUG)
				// ERROR HANDLING
				if (window == NULL) debug::LogError("Window not created!");
				
			/// Creating the inner child window.
			{
				const array<winapi::wchar, 12> classNameInner ( L"WindowPreviewInner" );
				const vector2<uint64>
					windowInnerOffset ( 15, 15 ),
					windowInnerSize	( 662, 511 ); // (200 wolnej)
				const winapi::windowHandle innerWindow (
					CreateChildWindow (
						process, 
						window, 
						(winapi::windowProcedure)windows::windowRight::inner::Pprocedure, 
						(HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED),
						classNameInner.Pointer(),
						brushes::primar.Get(),
						windowState,
						windowInnerOffset,
						windowInnerSize,
						WS_BORDER
					)
				);
				
				if constexpr (DEBUG)
					// ERROR HANDLING
					if (innerWindow == NULL) debug::LogError("Window not created!");
			}
					
			return window;
		}
	}
	
}