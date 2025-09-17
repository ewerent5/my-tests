// Dll for implementation in processes

/*

My injector

*/
#include <Windows.h>
#include <iostream>
 
BOOL WINAPI  point(HMODULE hm){ //<-- òî÷êà çàïóñêà | start point
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, false, GetCurrentProcessId()); // <--- process id

	char x1 = 254;

	if (!process)
		std::cout << "Process erroe!" << std::endl;

	else {
		Sleep(50);
		while (true) {							//  			   |ÿ÷åéêà | cell
												//				   \/			  \/çíà÷åíèå | value
			int memoryWindows = WriteProcessMemory(process, (LPVOID)0x128212550, &x1, (DWORD)sizeof(x1), NULL);
			//int memoryWindows2 = WriteProcessMemory(process, (LPVOID)0x0000022F5784EEE0, &value2, (DWORD)sizeof(value), NULL);
			//int memoryWindows3 = WriteProcessMemory(process, (LPVOID)0x000000E6C0D5F6E0, &value3, (DWORD)sizeof(value), NULL);
		}

		Sleep(10);
	}
		
		

	return true;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD Attach, LPVOID lp) {
	switch (Attach){
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(module);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)point, 0, 0, 0);
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}
