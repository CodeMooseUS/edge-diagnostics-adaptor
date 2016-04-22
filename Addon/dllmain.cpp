//
// Copyright (C) Microsoft. All rights reserved.
//

#include "stdafx.h"
#include "dllmain.h"
#include <Helpers.h>

extern "C" int GetEdgeInstances(_Inout_opt_count_(length) DWORD ids[], DWORD length)
{
    ::MessageBox(nullptr, L"Attach", L"Attach", 0);

    vector<DWORD> instances;
    
    Helpers::EnumWindowsHelper([&](HWND hwndTop) -> BOOL
	{
		Helpers::EnumChildWindowsHelper(hwndTop, [&](HWND hwnd) -> BOOL
		{
			if (Helpers::IsWindowClass(hwnd, L"Internet Explorer_Server"))
			{
				bool isEdgeContentProcess = false;
                
				DWORD processId;
				::GetWindowThreadProcessId(hwnd, &processId);
				CHandle handle(::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId));
				if (handle)
				{
					CString processName;
                    DWORD length = ::GetModuleFileNameEx(handle, nullptr, processName.GetBufferSetLength(MAX_PATH), MAX_PATH);
                    processName.ReleaseBuffer(length);
                    isEdgeContentProcess = (processName.Find(L"MicrosoftEdgeCP.exe") == processName.GetLength() - 19);
				}

                if (isEdgeContentProcess)
                {
                    instances.push_back(reinterpret_cast<DWORD>(hwnd));
                }
			}

			return TRUE;
		});

		return TRUE;
	});

    int copied = 0;

    if (ids != nullptr)
    {
        for (size_t i = 0; i < length && i < instances.size(); i++)
        {
            ids[i] = instances[i];
            copied++;
        }
    }
    else
    {
        copied = instances.size();
    }
    
    return copied;
}