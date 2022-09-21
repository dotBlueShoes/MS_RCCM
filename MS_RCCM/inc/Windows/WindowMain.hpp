#include "Framework.hpp"

#include "Procedures/ProcedureMain.hpp"
#include "Windows/DialogWindows/WindowAbout.hpp"
#include "Windows/WindowEditor.hpp"
#include "Windows/WindowRight.hpp"
#include "Windows/WindowLeft.hpp"

namespace windows::mainWindow {

	const winapi::windowHandle Create(
		const winapi::handleInstance& process, 
		const winapi::brushHandle& backgroundBrush,
		const int32& windowState,
		const vector2<uint64>& windowMainSize
	) {
		using namespace resourceHandler;
		
		Register(
			process, 
			className.Pointer(), 
			(winapi::windowProcedure)WindowMainProcedure, 
			iconId, 
			iconSmallId, 
			menuId, 
			backgroundBrush
		);
		
		{
			const vector2<uint64> windowMainPoistion ( CW_USEDEFAULT, 0 );
			const vector2<uint64> initialClientAreaOffset (8, 59); // Honestly maybe i should just use getclienbtArea.. thats way simpler i think
			
			if constexpr (DEBUG) debug::LogInfo("(CALL) Window-Main:Create");
				
			const winapi::windowHandle window ( 
				Initialize (
					process, 
					className.Pointer(), 
					title.Pointer(), 
					windowState,
					windowMainPoistion,
					windowMainSize
				) 
			); 
			
			if constexpr (DEBUG) 
				if (window == NULL) debug::LogError("Window not created!");
		
			leftWindow = windowLeft::Create(
				mainProcess,
				window,
				brushes::primar.Get(),
				initialClientAreaOffset,
				windowState
			);
			
			rightWindow = windowRight::Create(
				mainProcess,
				window,
				brushes::second.Get(),
				initialClientAreaOffset,
				windowState
			);
			
			return window;
		}
		
	}

}