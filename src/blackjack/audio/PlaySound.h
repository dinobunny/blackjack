#include <windows.h>
#include <Dshow.h>
#include <stdio.h>

#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "Strmiids.lib" )

void PlaySoundNew_Impl(const TCHAR* file);


DWORD WINAPI PlaySoundNew_ThreadProc(LPVOID lpThreadParameter);


void PlaySoundNew(const TCHAR* file, bool async);

//Example usage
//int main(int argc, char* argv[])
//{
//    HRESULT hr = CoInitialize(NULL);
//    if (FAILED(hr))
//    {
//        printf("ERROR - Could not initialize COM library");
//        return 1;
//    }
//
//    PlaySoundNew(L"C:\\Music\\Sound1.wav", true);
//    Sleep(2000);
//    PlaySoundNew(L"C:\\Music\\Sound2.wav", true);
//
//    getchar();
//    CoUninitialize();
//    return 0;
//}