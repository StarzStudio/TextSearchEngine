// Client.cpp : Defines the entry point for the console application.
//


#include "Client.h"




int main()
{
	
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (!SUCCEEDED(hr))
	{
		std::wcout << L"\n  could not initialize COM";
	}

	try
	{
		HRESULT hr;
		CComQIPtr<ICComFileMgr> pFileMgrComponent;
		pFileMgrComponent.CoCreateInstance(CLSID_CComFileMgr);
		if (!pFileMgrComponent)
		{
			std::wcout << "\n  failed to create file manager component";
			return -1;
		}
		else {
			CComBSTR path(L"..");
			CComBSTR pattern1(L"*.h");
			CComBSTR pattern2(L"*.cpp");

			VARIANT_BOOL result = 0;
			hr = pFileMgrComponent->addPath(path);

			if (SUCCEEDED(hr))
			{
				std::wcout << L"\n    init file manager component successful\n\n";
				hr = pFileMgrComponent->addPattern(pattern1);
				if (SUCCEEDED(hr))
				{
					std::wcout << L"\n   add pattern 1 successful\n\n";
					hr = pFileMgrComponent->addPattern(pattern2);
					if (SUCCEEDED(hr))
					{
						std::wcout << L"\n    add pattern 2 successful\n\n";
						pFileMgrComponent->search();

					}
				}
			}
			else {
				std::wcout << L"\n     init  file manager component failed\n\n";
			}

			

		}
	}
	catch (std::exception& ex)
	{
		std::wcout << L"\n  " << ex.what() << L"\n\n";
		return -1;
	}
	std::wcout << L"\n\n";


	int i;
	std::cin >> i ;
	//CoUninitialize();
    return 0;
}

