#include "PlaySound.h"

void PlaySoundNew_Impl(const TCHAR* file)
{ // implementation of file playback using DirectShow

    IGraphBuilder* pGraph = NULL;
    IMediaControl* pControl = NULL;
    IMediaEvent* pEvent = NULL;

    // Create the filter graph manager and query for interfaces.
    HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
                                  IID_IGraphBuilder, (void**) &pGraph);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create the Filter Graph Manager.");
        return;
    }

    hr = pGraph->QueryInterface(IID_IMediaControl, (void**) &pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void**) &pEvent);

    // Build the graph. 
    hr = pGraph->RenderFile(file, NULL);
    if (SUCCEEDED(hr))
    {
        // Run the graph.
        hr = pControl->Run();
        if (SUCCEEDED(hr))
        {
            // Wait for completion.
            long evCode;
            pEvent->WaitForCompletion(INFINITE, &evCode);
        }
    }
    else printf("RenderFile error 0x%x", (UINT) hr);

    pControl->Release();
    pEvent->Release();
    pGraph->Release();
}

DWORD PlaySoundNew_ThreadProc(LPVOID lpThreadParameter)
{ //function for background thread

    HRESULT hr = CoInitialize(NULL); //the background thread also needs COM initialization
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return 1;
    }

    const TCHAR* file = (const TCHAR*) lpThreadParameter;
    PlaySoundNew_Impl(file);

    CoUninitialize();
    return 0;
}

void PlaySoundNew(const TCHAR* file, bool async)
{ //playing a file via DirectShow

    if (async == FALSE)
    {
        PlaySoundNew_Impl(file); //synchronously        
    }
    else
    {
        CreateThread(NULL, 0, PlaySoundNew_ThreadProc, (LPVOID) file, 0, NULL); //asynchronously
    }
}
