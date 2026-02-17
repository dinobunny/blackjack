
#include <Dshow.h>
#include <cstdio>

#include "PlaySound.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Strmiids.lib")


namespace
{
    void PlaySoundNew_Impl(const TCHAR* file)
    {
        IGraphBuilder* pGraph = nullptr;
        IMediaControl* pControl = nullptr;
        IMediaEvent* pEvent = nullptr;

        // Create the filter graph manager and query for interfaces.
        HRESULT hr = CoCreateInstance(
            CLSID_FilterGraph,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_IGraphBuilder,
            reinterpret_cast<void**>(&pGraph));

        if (FAILED(hr) || pGraph == nullptr)
        {
            std::printf("ERROR - Could not create the Filter Graph Manager.");
            return;
        }

        hr = pGraph->QueryInterface(IID_IMediaControl,
                                    reinterpret_cast<void**>(&pControl));
        hr = pGraph->QueryInterface(IID_IMediaEvent,
                                    reinterpret_cast<void**>(&pEvent));

        // Build the graph.
        hr = pGraph->RenderFile(file, nullptr);
        if (SUCCEEDED(hr))
        {
            // Run the graph.
            hr = pControl->Run();
            if (SUCCEEDED(hr))
            {
                // Wait for completion.
                long evCode = 0;
                pEvent->WaitForCompletion(INFINITE, &evCode);
            }
        }
        else
        {
            std::printf("RenderFile error 0x%x",
                        static_cast<unsigned int>(hr));
        }

        if (pControl != nullptr)
        {
            pControl->Release();
        }
        if (pEvent != nullptr)
        {
            pEvent->Release();
        }
        if (pGraph != nullptr)
        {
            pGraph->Release();
        }
    }

    DWORD WINAPI PlaySoundNew_ThreadProc(LPVOID lpThreadParameter)
    {
        // function for background thread

        const HRESULT hr = CoInitialize(nullptr); // the background thread also needs COM initialization
        if (FAILED(hr))
        {
            std::printf("ERROR - Could not initialize COM library");
            return 1;
        }

        const auto* file = static_cast<const TCHAR*>(lpThreadParameter);
        PlaySoundNew_Impl(file);

        CoUninitialize();
        return 0;
    }
}

void blackjack::PlaySoundNew(const TCHAR* file, bool async)
{
    // playing a file via DirectShow

    if (!async)
    {
        PlaySoundNew_Impl(file); // synchronously
        return;
    }

    // asynchronously
    CreateThread(nullptr, 0, PlaySoundNew_ThreadProc, const_cast<TCHAR*>(file), 0, nullptr);
}
