#include "stdafx.h"
#include "CorProfilerCallback.h"

namespace JitGrabber
{

    ULONG CorProfilerCallback::m_scRef = 0;
    mutex CorProfilerCallback::m_mutexRef;

    wstring CorProfilerCallback::GetFunctionName(FunctionID funcID)
    {
        //auto it = g_funcNames.find(funcID);
        //if (it != g_funcNames.end())
        //    return (*it).second;

        wstring sResult;
        ClassID classId;
        ModuleID moduleId;
        mdToken token;
        if (FAILED(m_pCorProfilerInfo->GetFunctionInfo(funcID, &classId, &moduleId, &token)))
        {
            wcerr << L"[CorProfilerCallback::GetFunctionName]" << L" FAILED(m_pCorProfilerInfo->GetFunctionInfo())" << endl;
            return (wstringstream() << L"<func_" << funcID << L">").str();
        }

        IMetaDataImport* pMetaDataImport;
        if (FAILED(m_pCorProfilerInfo->GetModuleMetaData(moduleId, ofRead, IID_IMetaDataImport, (IUnknown**)&pMetaDataImport)))
        {
            wcerr << L"[CorProfilerCallback::GetFunctionName]" << L" FAILED(m_pCorProfilerInfo->GetModuleMetaData())" << endl;
            return (wstringstream() << L"<func_" << funcID << L">").str();
        }

		mdTypeDef tokenClass;
        WCHAR szMethodName[4096];
        ULONG chMethod;
        DWORD dwAttr;
        PCCOR_SIGNATURE pvSigBlob;
        ULONG cbSigBlob;
        ULONG ulCodeRVA;
        DWORD dwImplFlags;
		if (SUCCEEDED(pMetaDataImport->GetMethodProps(token, &tokenClass, szMethodName, 4096, &chMethod, &dwAttr, &pvSigBlob, &cbSigBlob, &ulCodeRVA, &dwImplFlags)))
        {
            WCHAR szName[4096];
            ULONG chTypeDef;
            DWORD dwTypeDefFlags;
            mdToken tkExtends;
            if (SUCCEEDED(pMetaDataImport->GetTypeDefProps(tokenClass, szName, 4096, &chTypeDef, &dwTypeDefFlags, &tkExtends)))
            {
                sResult = szName;
                sResult += L".";
            }
            else
            {
                wcerr << L"[CorProfilerCallback::GetFunctionName]" << L" FAILED(pMetaDataImport->GetTypeDefProps())" << endl;
                return (wstringstream() << L"<func_" << funcID << L">").str();
            }

            sResult += szMethodName;
        }
        else
        {
            wcerr << L"[CorProfilerCallback::GetFunctionName]" << L" FAILED(pMetaDataImport->GetMethodProps())" << endl;
            return (wstringstream() << L"<func_" << funcID << L">").str();
        }

        //g_funcNames[funcID] = sResult;
        return sResult;
    }


#pragma region IUnknown methods

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::QueryInterface(
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ /* _COM_Outptr_ */ void **ppvObject)
    {
        wcerr << L"[CorProfilerCallback::QueryInterface]" << L" " << setw(8) << setfill(L'0') << hex << riid.Data1 << endl;

        HRESULT     hr;

        // Avoid confusion.
        *ppvObject = nullptr;

        // Pick the right v-table based on the IID passed in.
        if (riid == IID_IUnknown)
            *ppvObject = (IUnknown *)this;
        else if (riid == IID_ICorProfilerCallback)
            *ppvObject = (ICorProfilerCallback *)this;
        else if (riid == IID_ICorProfilerCallback2)
            *ppvObject = (ICorProfilerCallback2 *)this;
        else if (riid == IID_ICorProfilerCallback3)
            *ppvObject = (ICorProfilerCallback3 *)this;

        // If successful, add a reference for out pointer and return.
        if (*ppvObject)
        {
            hr = S_OK;
            AddRef();
        }
        else
            hr = E_NOINTERFACE;

        return hr;
    }

#pragma endregion

#pragma region ICorProfilerCallback methods

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::Initialize(
        /* [in] */ IUnknown *pICorProfilerInfoUnk)
    {
        wcerr << L"[CorProfilerCallback::Initialize]" << endl;

        pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo3, (void**)&m_pCorProfilerInfo);

        if (FAILED(m_pCorProfilerInfo->SetEventMask(COR_PRF_MONITOR_JIT_COMPILATION)))
        {
            wcerr << L"[CorProfilerCallback::Initialize]" << L" FAILED(m_pCorProfilerInfo->SetEventMask())" << endl;
            return E_FAIL;
        }

        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::Shutdown(void)
    {
        wcerr << L"[CorProfilerCallback::Shutdown]" << endl;

        m_pCorProfilerInfo->Release();

        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::AppDomainCreationStarted(
        /* [in] */ AppDomainID appDomainId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::AppDomainCreationFinished(
        /* [in] */ AppDomainID appDomainId,
        /* [in] */ HRESULT hrStatus)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::AppDomainShutdownStarted(
        /* [in] */ AppDomainID appDomainId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::AppDomainShutdownFinished(
        /* [in] */ AppDomainID appDomainId,
        /* [in] */ HRESULT hrStatus)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::AssemblyLoadStarted(
        /* [in] */ AssemblyID assemblyId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::AssemblyLoadFinished(
        /* [in] */ AssemblyID assemblyId,
        /* [in] */ HRESULT hrStatus)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::AssemblyUnloadStarted(
        /* [in] */ AssemblyID assemblyId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::AssemblyUnloadFinished(
        /* [in] */ AssemblyID assemblyId,
        /* [in] */ HRESULT hrStatus)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ModuleLoadStarted(
        /* [in] */ ModuleID moduleId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ModuleLoadFinished(
        /* [in] */ ModuleID moduleId,
        /* [in] */ HRESULT hrStatus)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ModuleUnloadStarted(
        /* [in] */ ModuleID moduleId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ModuleUnloadFinished(
        /* [in] */ ModuleID moduleId,
        /* [in] */ HRESULT hrStatus)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ModuleAttachedToAssembly(
        /* [in] */ ModuleID moduleId,
        /* [in] */ AssemblyID AssemblyId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ClassLoadStarted(
        /* [in] */ ClassID classId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ClassLoadFinished(
        /* [in] */ ClassID classId,
        /* [in] */ HRESULT hrStatus)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ClassUnloadStarted(
        /* [in] */ ClassID classId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ClassUnloadFinished(
        /* [in] */ ClassID classId,
        /* [in] */ HRESULT hrStatus)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::FunctionUnloadStarted(
        /* [in] */ FunctionID functionId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::JITCompilationStarted(
        /* [in] */ FunctionID functionId,
        /* [in] */ BOOL fIsSafeToBlock)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::JITCompilationFinished(
        /* [in] */ FunctionID functionId,
        /* [in] */ HRESULT hrStatus,
        /* [in] */ BOOL fIsSafeToBlock)
    {
        //wcerr << L"1[CorProfilerCallback::JITCompilationFinished]" << L" " << GetFunctionName(functionId) << endl;

        COR_PRF_CODE_INFO codeInfos[512];
        ULONG32 cCodeInfos = 0;
        m_pCorProfilerInfo->GetCodeInfo2(functionId, 512, &cCodeInfos, codeInfos);

        for (ULONG32 i = 0; i < cCodeInfos; i++)
        {
            wcerr << L"2[CorProfilerCallback::JITCompilationFinished]" << L" codeInfo #" << i << " address=" << setw(16) << setfill(L'0') << hex
                << codeInfos[i].startAddress << L" size=" << codeInfos[i].size << L" code: ";

            for (size_t j = 0; j < codeInfos[i].size; j++)
                wcerr << setw(2) << setfill(L'0') << hex << *(BYTE*)(codeInfos[i].startAddress + j) << L" ";

            wcerr << endl;

            csh handle;
            cs_insn *insn;
            size_t count;

            if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK)
                continue;
            count = cs_disasm(handle, (BYTE*)(codeInfos[i].startAddress), codeInfos[i].size, codeInfos[i].startAddress, 0, &insn);
            if (count > 0)
            {
                size_t j;
                for (j = 0; j < count; j++)
                {
                    wcerr << L"3[CorProfilerCallback::JITCompilationFinished]" << L" " << setw(16) << setfill(L'0') << hex << insn[j].address << L": ";
                    cerr << setw(16) << setiosflags(ios::left) << setfill(' ') << insn[j].mnemonic;
                    cerr << insn[j].op_str << endl;
                }
                cs_free(insn, count);
            }
            else
                continue;
            cs_close(&handle);
        }

        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::JITCachedFunctionSearchStarted(
        /* [in] */ FunctionID functionId,
        /* [out] */ BOOL *pbUseCachedFunction)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::JITCachedFunctionSearchFinished(
        /* [in] */ FunctionID functionId,
        /* [in] */ COR_PRF_JIT_CACHE result)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::JITFunctionPitched(
        /* [in] */ FunctionID functionId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::JITInlining(
        /* [in] */ FunctionID callerId,
        /* [in] */ FunctionID calleeId,
        /* [out] */ BOOL *pfShouldInline)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ThreadCreated(
        /* [in] */ ThreadID threadId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ThreadDestroyed(
        /* [in] */ ThreadID threadId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ThreadAssignedToOSThread(
        /* [in] */ ThreadID managedThreadId,
        /* [in] */ DWORD osThreadId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RemotingClientInvocationStarted(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RemotingClientSendingMessage(
        /* [in] */ GUID *pCookie,
        /* [in] */ BOOL fIsAsync)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RemotingClientReceivingReply(
        /* [in] */ GUID *pCookie,
        /* [in] */ BOOL fIsAsync)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RemotingClientInvocationFinished(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RemotingServerReceivingMessage(
        /* [in] */ GUID *pCookie,
        /* [in] */ BOOL fIsAsync)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RemotingServerInvocationStarted(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RemotingServerInvocationReturned(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RemotingServerSendingReply(
        /* [in] */ GUID *pCookie,
        /* [in] */ BOOL fIsAsync)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::UnmanagedToManagedTransition(
        /* [in] */ FunctionID functionId,
        /* [in] */ COR_PRF_TRANSITION_REASON reason)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ManagedToUnmanagedTransition(
        /* [in] */ FunctionID functionId,
        /* [in] */ COR_PRF_TRANSITION_REASON reason)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RuntimeSuspendStarted(
        /* [in] */ COR_PRF_SUSPEND_REASON suspendReason)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RuntimeSuspendFinished(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RuntimeSuspendAborted(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RuntimeResumeStarted(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RuntimeResumeFinished(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RuntimeThreadSuspended(
        /* [in] */ ThreadID threadId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RuntimeThreadResumed(
        /* [in] */ ThreadID threadId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::MovedReferences(
        /* [in] */ ULONG cMovedObjectIDRanges,
        /* [size_is][in] */ ObjectID oldObjectIDRangeStart[],
        /* [size_is][in] */ ObjectID newObjectIDRangeStart[],
        /* [size_is][in] */ ULONG cObjectIDRangeLength[])
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ObjectAllocated(
        /* [in] */ ObjectID objectId,
        /* [in] */ ClassID classId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ObjectsAllocatedByClass(
        /* [in] */ ULONG cClassCount,
        /* [size_is][in] */ ClassID classIds[],
        /* [size_is][in] */ ULONG cObjects[])
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ObjectReferences(
        /* [in] */ ObjectID objectId,
        /* [in] */ ClassID classId,
        /* [in] */ ULONG cObjectRefs,
        /* [size_is][in] */ ObjectID objectRefIds[])
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RootReferences(
        /* [in] */ ULONG cRootRefs,
        /* [size_is][in] */ ObjectID rootRefIds[])
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionThrown(
        /* [in] */ ObjectID thrownObjectId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionSearchFunctionEnter(
        /* [in] */ FunctionID functionId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionSearchFunctionLeave(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionSearchFilterEnter(
        /* [in] */ FunctionID functionId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionSearchFilterLeave(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionSearchCatcherFound(
        /* [in] */ FunctionID functionId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionOSHandlerEnter(
        /* [in] */ UINT_PTR __unused)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionOSHandlerLeave(
        /* [in] */ UINT_PTR __unused)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionUnwindFunctionEnter(
        /* [in] */ FunctionID functionId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionUnwindFunctionLeave(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionUnwindFinallyEnter(
        /* [in] */ FunctionID functionId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionUnwindFinallyLeave(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionCatcherEnter(
        /* [in] */ FunctionID functionId,
        /* [in] */ ObjectID objectId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionCatcherLeave(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::COMClassicVTableCreated(
        /* [in] */ ClassID wrappedClassId,
        /* [in] */ REFGUID implementedIID,
        /* [in] */ void *pVTable,
        /* [in] */ ULONG cSlots)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::COMClassicVTableDestroyed(
        /* [in] */ ClassID wrappedClassId,
        /* [in] */ REFGUID implementedIID,
        /* [in] */ void *pVTable)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionCLRCatcherFound(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ExceptionCLRCatcherExecute(void)
    {
        return E_NOTIMPL;
    }

#pragma endregion

#pragma region ICorProfilerCallback2 methods

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ThreadNameChanged(
        /* [in] */ ThreadID threadId,
        /* [in] */ ULONG cchName,
        /* [annotation][in] */
        /* _In_reads_opt_(cchName) */  WCHAR name[])
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::GarbageCollectionStarted(
        /* [in] */ int cGenerations,
        /* [size_is][in] */ BOOL generationCollected[],
        /* [in] */ COR_PRF_GC_REASON reason)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::SurvivingReferences(
        /* [in] */ ULONG cSurvivingObjectIDRanges,
        /* [size_is][in] */ ObjectID objectIDRangeStart[],
        /* [size_is][in] */ ULONG cObjectIDRangeLength[])
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::GarbageCollectionFinished(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::FinalizeableObjectQueued(
        /* [in] */ DWORD finalizerFlags,
        /* [in] */ ObjectID objectID)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::RootReferences2(
        /* [in] */ ULONG cRootRefs,
        /* [size_is][in] */ ObjectID rootRefIds[],
        /* [size_is][in] */ COR_PRF_GC_ROOT_KIND rootKinds[],
        /* [size_is][in] */ COR_PRF_GC_ROOT_FLAGS rootFlags[],
        /* [size_is][in] */ UINT_PTR rootIds[])
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::HandleCreated(
        /* [in] */ GCHandleID handleId,
        /* [in] */ ObjectID initialObjectId)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::HandleDestroyed(
        /* [in] */ GCHandleID handleId)
    {
        return E_NOTIMPL;
    }

#pragma endregion

#pragma region ICorProfilerCallback3 methods

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::InitializeForAttach(
        /* [in] */ IUnknown *pCorProfilerInfoUnk,
        /* [in] */ void *pvClientData,
        /* [in] */ UINT cbClientData)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ProfilerAttachComplete(void)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE CorProfilerCallback::ProfilerDetachSucceeded(void)
    {
        return E_NOTIMPL;
    }

#pragma endregion

}
