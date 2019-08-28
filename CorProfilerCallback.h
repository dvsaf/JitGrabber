#pragma once

namespace JitGrabber
{
	static const CLSID CLSID_CorProfilerCallback = { 0x7834a07a, 0xbec2, 0x460c, { 0x72, 0x9b, 0x48, 0x1c, 0x16, 0x2a, 0x7c, 0x70 } };

    class CorProfilerCallback :
        public ICorProfilerCallback3
    {
    public:

        CorProfilerCallback()
            : m_cRef(0)
        { }

        virtual ~CorProfilerCallback() {}

        static ULONG AllRefCount()
        {
			scoped_lock(m_mutexRef);

            return m_scRef;
        }

#pragma region IUnknown methods

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ _COM_Outptr_ void **ppvObject);

        virtual ULONG STDMETHODCALLTYPE AddRef()
        {
			scoped_lock(m_mutexRef);

            ++m_scRef;
            return ++m_cRef;
        }

        virtual ULONG STDMETHODCALLTYPE Release()
        {
			scoped_lock(m_mutexRef);

            --m_scRef;
			--m_cRef;

            if (m_cRef == 0)
                delete this;

            return m_cRef;
        }

#pragma endregion

#pragma region ICorProfilerCallback methods

        virtual HRESULT STDMETHODCALLTYPE Initialize(
            /* [in] */ IUnknown *pICorProfilerInfoUnk);

        virtual HRESULT STDMETHODCALLTYPE Shutdown(void);

        virtual HRESULT STDMETHODCALLTYPE AppDomainCreationStarted(
            /* [in] */ AppDomainID appDomainId);

        virtual HRESULT STDMETHODCALLTYPE AppDomainCreationFinished(
            /* [in] */ AppDomainID appDomainId,
            /* [in] */ HRESULT hrStatus);

        virtual HRESULT STDMETHODCALLTYPE AppDomainShutdownStarted(
            /* [in] */ AppDomainID appDomainId);

        virtual HRESULT STDMETHODCALLTYPE AppDomainShutdownFinished(
            /* [in] */ AppDomainID appDomainId,
            /* [in] */ HRESULT hrStatus);

        virtual HRESULT STDMETHODCALLTYPE AssemblyLoadStarted(
            /* [in] */ AssemblyID assemblyId);

        virtual HRESULT STDMETHODCALLTYPE AssemblyLoadFinished(
            /* [in] */ AssemblyID assemblyId,
            /* [in] */ HRESULT hrStatus);

        virtual HRESULT STDMETHODCALLTYPE AssemblyUnloadStarted(
            /* [in] */ AssemblyID assemblyId);

        virtual HRESULT STDMETHODCALLTYPE AssemblyUnloadFinished(
            /* [in] */ AssemblyID assemblyId,
            /* [in] */ HRESULT hrStatus);

        virtual HRESULT STDMETHODCALLTYPE ModuleLoadStarted(
            /* [in] */ ModuleID moduleId);

        virtual HRESULT STDMETHODCALLTYPE ModuleLoadFinished(
            /* [in] */ ModuleID moduleId,
            /* [in] */ HRESULT hrStatus);

        virtual HRESULT STDMETHODCALLTYPE ModuleUnloadStarted(
            /* [in] */ ModuleID moduleId);

        virtual HRESULT STDMETHODCALLTYPE ModuleUnloadFinished(
            /* [in] */ ModuleID moduleId,
            /* [in] */ HRESULT hrStatus);

        virtual HRESULT STDMETHODCALLTYPE ModuleAttachedToAssembly(
            /* [in] */ ModuleID moduleId,
            /* [in] */ AssemblyID AssemblyId);

        virtual HRESULT STDMETHODCALLTYPE ClassLoadStarted(
            /* [in] */ ClassID classId);

        virtual HRESULT STDMETHODCALLTYPE ClassLoadFinished(
            /* [in] */ ClassID classId,
            /* [in] */ HRESULT hrStatus);

        virtual HRESULT STDMETHODCALLTYPE ClassUnloadStarted(
            /* [in] */ ClassID classId);

        virtual HRESULT STDMETHODCALLTYPE ClassUnloadFinished(
            /* [in] */ ClassID classId,
            /* [in] */ HRESULT hrStatus);

        virtual HRESULT STDMETHODCALLTYPE FunctionUnloadStarted(
            /* [in] */ FunctionID functionId);

        virtual HRESULT STDMETHODCALLTYPE JITCompilationStarted(
            /* [in] */ FunctionID functionId,
            /* [in] */ BOOL fIsSafeToBlock);

        virtual HRESULT STDMETHODCALLTYPE JITCompilationFinished(
            /* [in] */ FunctionID functionId,
            /* [in] */ HRESULT hrStatus,
            /* [in] */ BOOL fIsSafeToBlock);

        virtual HRESULT STDMETHODCALLTYPE JITCachedFunctionSearchStarted(
            /* [in] */ FunctionID functionId,
            /* [out] */ BOOL *pbUseCachedFunction);

        virtual HRESULT STDMETHODCALLTYPE JITCachedFunctionSearchFinished(
            /* [in] */ FunctionID functionId,
            /* [in] */ COR_PRF_JIT_CACHE result);

        virtual HRESULT STDMETHODCALLTYPE JITFunctionPitched(
            /* [in] */ FunctionID functionId);

        virtual HRESULT STDMETHODCALLTYPE JITInlining(
            /* [in] */ FunctionID callerId,
            /* [in] */ FunctionID calleeId,
            /* [out] */ BOOL *pfShouldInline);

        virtual HRESULT STDMETHODCALLTYPE ThreadCreated(
            /* [in] */ ThreadID threadId);

        virtual HRESULT STDMETHODCALLTYPE ThreadDestroyed(
            /* [in] */ ThreadID threadId);

        virtual HRESULT STDMETHODCALLTYPE ThreadAssignedToOSThread(
            /* [in] */ ThreadID managedThreadId,
            /* [in] */ DWORD osThreadId);

        virtual HRESULT STDMETHODCALLTYPE RemotingClientInvocationStarted(void);

        virtual HRESULT STDMETHODCALLTYPE RemotingClientSendingMessage(
            /* [in] */ GUID *pCookie,
            /* [in] */ BOOL fIsAsync);

        virtual HRESULT STDMETHODCALLTYPE RemotingClientReceivingReply(
            /* [in] */ GUID *pCookie,
            /* [in] */ BOOL fIsAsync);

        virtual HRESULT STDMETHODCALLTYPE RemotingClientInvocationFinished(void);

        virtual HRESULT STDMETHODCALLTYPE RemotingServerReceivingMessage(
            /* [in] */ GUID *pCookie,
            /* [in] */ BOOL fIsAsync);

        virtual HRESULT STDMETHODCALLTYPE RemotingServerInvocationStarted(void);

        virtual HRESULT STDMETHODCALLTYPE RemotingServerInvocationReturned(void);

        virtual HRESULT STDMETHODCALLTYPE RemotingServerSendingReply(
            /* [in] */ GUID *pCookie,
            /* [in] */ BOOL fIsAsync);

        virtual HRESULT STDMETHODCALLTYPE UnmanagedToManagedTransition(
            /* [in] */ FunctionID functionId,
            /* [in] */ COR_PRF_TRANSITION_REASON reason);

        virtual HRESULT STDMETHODCALLTYPE ManagedToUnmanagedTransition(
            /* [in] */ FunctionID functionId,
            /* [in] */ COR_PRF_TRANSITION_REASON reason);

        virtual HRESULT STDMETHODCALLTYPE RuntimeSuspendStarted(
            /* [in] */ COR_PRF_SUSPEND_REASON suspendReason);

        virtual HRESULT STDMETHODCALLTYPE RuntimeSuspendFinished(void);

        virtual HRESULT STDMETHODCALLTYPE RuntimeSuspendAborted(void);

        virtual HRESULT STDMETHODCALLTYPE RuntimeResumeStarted(void);

        virtual HRESULT STDMETHODCALLTYPE RuntimeResumeFinished(void);

        virtual HRESULT STDMETHODCALLTYPE RuntimeThreadSuspended(
            /* [in] */ ThreadID threadId);

        virtual HRESULT STDMETHODCALLTYPE RuntimeThreadResumed(
            /* [in] */ ThreadID threadId);

        virtual HRESULT STDMETHODCALLTYPE MovedReferences(
            /* [in] */ ULONG cMovedObjectIDRanges,
            /* [size_is][in] */ ObjectID oldObjectIDRangeStart[],
            /* [size_is][in] */ ObjectID newObjectIDRangeStart[],
            /* [size_is][in] */ ULONG cObjectIDRangeLength[]);

        virtual HRESULT STDMETHODCALLTYPE ObjectAllocated(
            /* [in] */ ObjectID objectId,
            /* [in] */ ClassID classId);

        virtual HRESULT STDMETHODCALLTYPE ObjectsAllocatedByClass(
            /* [in] */ ULONG cClassCount,
            /* [size_is][in] */ ClassID classIds[],
            /* [size_is][in] */ ULONG cObjects[]);

        virtual HRESULT STDMETHODCALLTYPE ObjectReferences(
            /* [in] */ ObjectID objectId,
            /* [in] */ ClassID classId,
            /* [in] */ ULONG cObjectRefs,
            /* [size_is][in] */ ObjectID objectRefIds[]);

        virtual HRESULT STDMETHODCALLTYPE RootReferences(
            /* [in] */ ULONG cRootRefs,
            /* [size_is][in] */ ObjectID rootRefIds[]);

        virtual HRESULT STDMETHODCALLTYPE ExceptionThrown(
            /* [in] */ ObjectID thrownObjectId);

        virtual HRESULT STDMETHODCALLTYPE ExceptionSearchFunctionEnter(
            /* [in] */ FunctionID functionId);

        virtual HRESULT STDMETHODCALLTYPE ExceptionSearchFunctionLeave(void);

        virtual HRESULT STDMETHODCALLTYPE ExceptionSearchFilterEnter(
            /* [in] */ FunctionID functionId);

        virtual HRESULT STDMETHODCALLTYPE ExceptionSearchFilterLeave(void);

        virtual HRESULT STDMETHODCALLTYPE ExceptionSearchCatcherFound(
            /* [in] */ FunctionID functionId);

        virtual HRESULT STDMETHODCALLTYPE ExceptionOSHandlerEnter(
            /* [in] */ UINT_PTR __unused);

        virtual HRESULT STDMETHODCALLTYPE ExceptionOSHandlerLeave(
            /* [in] */ UINT_PTR __unused);

        virtual HRESULT STDMETHODCALLTYPE ExceptionUnwindFunctionEnter(
            /* [in] */ FunctionID functionId);

        virtual HRESULT STDMETHODCALLTYPE ExceptionUnwindFunctionLeave(void);

        virtual HRESULT STDMETHODCALLTYPE ExceptionUnwindFinallyEnter(
            /* [in] */ FunctionID functionId);

        virtual HRESULT STDMETHODCALLTYPE ExceptionUnwindFinallyLeave(void);

        virtual HRESULT STDMETHODCALLTYPE ExceptionCatcherEnter(
            /* [in] */ FunctionID functionId,
            /* [in] */ ObjectID objectId);

        virtual HRESULT STDMETHODCALLTYPE ExceptionCatcherLeave(void);

        virtual HRESULT STDMETHODCALLTYPE COMClassicVTableCreated(
            /* [in] */ ClassID wrappedClassId,
            /* [in] */ REFGUID implementedIID,
            /* [in] */ void *pVTable,
            /* [in] */ ULONG cSlots);

        virtual HRESULT STDMETHODCALLTYPE COMClassicVTableDestroyed(
            /* [in] */ ClassID wrappedClassId,
            /* [in] */ REFGUID implementedIID,
            /* [in] */ void *pVTable);

        virtual HRESULT STDMETHODCALLTYPE ExceptionCLRCatcherFound(void);

        virtual HRESULT STDMETHODCALLTYPE ExceptionCLRCatcherExecute(void);

#pragma endregion

#pragma region ICorProfilerCallback methods

        virtual HRESULT STDMETHODCALLTYPE ThreadNameChanged(
            /* [in] */ ThreadID threadId,
            /* [in] */ ULONG cchName,
            /* [annotation][in] */
            _In_reads_opt_(cchName)  WCHAR name[]);

        virtual HRESULT STDMETHODCALLTYPE GarbageCollectionStarted(
            /* [in] */ int cGenerations,
            /* [size_is][in] */ BOOL generationCollected[],
            /* [in] */ COR_PRF_GC_REASON reason);

        virtual HRESULT STDMETHODCALLTYPE SurvivingReferences(
            /* [in] */ ULONG cSurvivingObjectIDRanges,
            /* [size_is][in] */ ObjectID objectIDRangeStart[],
            /* [size_is][in] */ ULONG cObjectIDRangeLength[]);

        virtual HRESULT STDMETHODCALLTYPE GarbageCollectionFinished(void);

        virtual HRESULT STDMETHODCALLTYPE FinalizeableObjectQueued(
            /* [in] */ DWORD finalizerFlags,
            /* [in] */ ObjectID objectID);

        virtual HRESULT STDMETHODCALLTYPE RootReferences2(
            /* [in] */ ULONG cRootRefs,
            /* [size_is][in] */ ObjectID rootRefIds[],
            /* [size_is][in] */ COR_PRF_GC_ROOT_KIND rootKinds[],
            /* [size_is][in] */ COR_PRF_GC_ROOT_FLAGS rootFlags[],
            /* [size_is][in] */ UINT_PTR rootIds[]);

        virtual HRESULT STDMETHODCALLTYPE HandleCreated(
            /* [in] */ GCHandleID handleId,
            /* [in] */ ObjectID initialObjectId);

        virtual HRESULT STDMETHODCALLTYPE HandleDestroyed(
            /* [in] */ GCHandleID handleId);

#pragma endregion

#pragma region ICorProfilerCallback3 methods

        virtual HRESULT STDMETHODCALLTYPE InitializeForAttach(
            /* [in] */ IUnknown *pCorProfilerInfoUnk,
            /* [in] */ void *pvClientData,
            /* [in] */ UINT cbClientData);

        virtual HRESULT STDMETHODCALLTYPE ProfilerAttachComplete(void);

        virtual HRESULT STDMETHODCALLTYPE ProfilerDetachSucceeded(void);

#pragma endregion

    private:

        wstring GetFunctionName(FunctionID funcID);

        ULONG m_cRef;         // Число ссылок на конкретный объект
        static ULONG m_scRef; // Число ссылок на все объекты класса

		mutex m_mutexRef;

        ICorProfilerInfo3* m_pCorProfilerInfo = nullptr;

    };

}
