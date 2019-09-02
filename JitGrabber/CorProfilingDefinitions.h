#pragma once

typedef UINT_PTR ProcessID;
typedef UINT_PTR AssemblyID;
typedef UINT_PTR AppDomainID;
typedef UINT_PTR ModuleID;
typedef UINT_PTR ClassID;
typedef UINT_PTR ThreadID;
typedef UINT_PTR ContextID;
typedef UINT_PTR FunctionID;
typedef UINT_PTR ObjectID;
typedef UINT_PTR GCHandleID;
typedef UINT_PTR COR_PRF_ELT_INFO;
typedef UINT_PTR ReJITID;


union FunctionIDOrClientID
{
	FunctionID functionID;
	UINT_PTR clientID;
};

typedef UINT_PTR FunctionIDMapper(
	FunctionID funcId,
	BOOL* pbHookFunction);

typedef UINT_PTR FunctionIDMapper2(
	FunctionID funcId,
	void* clientData,
	BOOL* pbHookFunction);

typedef UINT_PTR COR_PRF_FRAME_INFO;

struct COR_PRF_FUNCTION_ARGUMENT_RANGE
{
	UINT_PTR startAddress;
	ULONG length;
};

struct COR_PRF_FUNCTION_ARGUMENT_INFO
{
	ULONG numRanges;
	ULONG totalArgumentSize;
	COR_PRF_FUNCTION_ARGUMENT_RANGE ranges[1];
};

struct COR_PRF_CODE_INFO
{
	UINT_PTR startAddress;
	SIZE_T size;
};

enum COR_PRF_STATIC_TYPE
{
	COR_PRF_FIELD_NOT_A_STATIC = 0,
	COR_PRF_FIELD_APP_DOMAIN_STATIC = 0x1,
	COR_PRF_FIELD_THREAD_STATIC = 0x2,
	COR_PRF_FIELD_CONTEXT_STATIC = 0x4,
	COR_PRF_FIELD_RVA_STATIC = 0x8
};

struct COR_PRF_FUNCTION
{
	FunctionID functionId;
	ReJITID reJitId;
};

typedef void FunctionEnter(
	FunctionID funcID);

typedef void FunctionLeave(
	FunctionID funcID);

typedef void FunctionTailcall(
	FunctionID funcID);

typedef void FunctionEnter2(
	FunctionID funcId,
	UINT_PTR clientData,
	COR_PRF_FRAME_INFO func,
	COR_PRF_FUNCTION_ARGUMENT_INFO* argumentInfo);

typedef void FunctionLeave2(
	FunctionID funcId,
	UINT_PTR clientData,
	COR_PRF_FRAME_INFO func,
	COR_PRF_FUNCTION_ARGUMENT_RANGE* retvalRange);

typedef void FunctionTailcall2(
	FunctionID funcId,
	UINT_PTR clientData,
	COR_PRF_FRAME_INFO func);

typedef void FunctionEnter3(
	FunctionIDOrClientID functionIDOrClientID);

typedef void FunctionLeave3(
	FunctionIDOrClientID functionIDOrClientID);

typedef void FunctionTailcall3(
	FunctionIDOrClientID functionIDOrClientID);

typedef void FunctionEnter3WithInfo(
	FunctionIDOrClientID functionIDOrClientID,
	COR_PRF_ELT_INFO eltInfo);

typedef void FunctionLeave3WithInfo(
	FunctionIDOrClientID functionIDOrClientID,
	COR_PRF_ELT_INFO eltInfo);

typedef void FunctionTailcall3WithInfo(
	FunctionIDOrClientID functionIDOrClientID,
	COR_PRF_ELT_INFO eltInfo);

typedef HRESULT STDMETHODCALLTYPE StackSnapshotCallback(
	FunctionID funcId,
	UINT_PTR ip,
	COR_PRF_FRAME_INFO frameInfo,
	ULONG32 contextSize,
	BYTE context[],
	void* clientData);

enum COR_PRF_MONITOR
{
	COR_PRF_MONITOR_NONE = 0,
	COR_PRF_MONITOR_FUNCTION_UNLOADS = 0x1,
	COR_PRF_MONITOR_CLASS_LOADS = 0x2,
	COR_PRF_MONITOR_MODULE_LOADS = 0x4,
	COR_PRF_MONITOR_ASSEMBLY_LOADS = 0x8,
	COR_PRF_MONITOR_APPDOMAIN_LOADS = 0x10,
	COR_PRF_MONITOR_JIT_COMPILATION = 0x20,
	COR_PRF_MONITOR_EXCEPTIONS = 0x40,
	COR_PRF_MONITOR_GC = 0x80,
	COR_PRF_MONITOR_OBJECT_ALLOCATED = 0x100,
	COR_PRF_MONITOR_THREADS = 0x200,
	COR_PRF_MONITOR_REMOTING = 0x400,
	COR_PRF_MONITOR_CODE_TRANSITIONS = 0x800,
	COR_PRF_MONITOR_ENTERLEAVE = 0x1000,
	COR_PRF_MONITOR_CCW = 0x2000,
	COR_PRF_MONITOR_REMOTING_COOKIE = (0x4000 | COR_PRF_MONITOR_REMOTING),
	COR_PRF_MONITOR_REMOTING_ASYNC = (0x8000 | COR_PRF_MONITOR_REMOTING),
	COR_PRF_MONITOR_SUSPENDS = 0x10000,
	COR_PRF_MONITOR_CACHE_SEARCHES = 0x20000,
	COR_PRF_ENABLE_REJIT = 0x40000,
	COR_PRF_ENABLE_INPROC_DEBUGGING = 0x80000,
	COR_PRF_ENABLE_JIT_MAPS = 0x100000,
	COR_PRF_DISABLE_INLINING = 0x200000,
	COR_PRF_DISABLE_OPTIMIZATIONS = 0x400000,
	COR_PRF_ENABLE_OBJECT_ALLOCATED = 0x800000,
	COR_PRF_MONITOR_CLR_EXCEPTIONS = 0x1000000,
	COR_PRF_MONITOR_ALL = 0x107ffff,
	COR_PRF_ENABLE_FUNCTION_ARGS = 0x2000000,
	COR_PRF_ENABLE_FUNCTION_RETVAL = 0x4000000,
	COR_PRF_ENABLE_FRAME_INFO = 0x8000000,
	COR_PRF_ENABLE_STACK_SNAPSHOT = 0x10000000,
	COR_PRF_USE_PROFILE_IMAGES = 0x20000000,
	COR_PRF_DISABLE_TRANSPARENCY_CHECKS_UNDER_FULL_TRUST = 0x40000000,
	COR_PRF_DISABLE_ALL_NGEN_IMAGES = 0x80000000,
	COR_PRF_ALL = 0x8fffffff,
	COR_PRF_REQUIRE_PROFILE_IMAGE = ((COR_PRF_USE_PROFILE_IMAGES | COR_PRF_MONITOR_CODE_TRANSITIONS) | COR_PRF_MONITOR_ENTERLEAVE),
	COR_PRF_ALLOWABLE_AFTER_ATTACH = (((((((((COR_PRF_MONITOR_THREADS | COR_PRF_MONITOR_MODULE_LOADS) | COR_PRF_MONITOR_ASSEMBLY_LOADS) | COR_PRF_MONITOR_APPDOMAIN_LOADS) | COR_PRF_ENABLE_STACK_SNAPSHOT) | COR_PRF_MONITOR_GC) | COR_PRF_MONITOR_SUSPENDS) | COR_PRF_MONITOR_CLASS_LOADS) | COR_PRF_MONITOR_EXCEPTIONS) | COR_PRF_MONITOR_JIT_COMPILATION),
	COR_PRF_MONITOR_IMMUTABLE = (((((((((((((((COR_PRF_MONITOR_CODE_TRANSITIONS | COR_PRF_MONITOR_REMOTING) | COR_PRF_MONITOR_REMOTING_COOKIE) | COR_PRF_MONITOR_REMOTING_ASYNC) | COR_PRF_ENABLE_REJIT) | COR_PRF_ENABLE_INPROC_DEBUGGING) | COR_PRF_ENABLE_JIT_MAPS) | COR_PRF_DISABLE_OPTIMIZATIONS) | COR_PRF_DISABLE_INLINING) | COR_PRF_ENABLE_OBJECT_ALLOCATED) | COR_PRF_ENABLE_FUNCTION_ARGS) | COR_PRF_ENABLE_FUNCTION_RETVAL) | COR_PRF_ENABLE_FRAME_INFO) | COR_PRF_USE_PROFILE_IMAGES) | COR_PRF_DISABLE_TRANSPARENCY_CHECKS_UNDER_FULL_TRUST) | COR_PRF_DISABLE_ALL_NGEN_IMAGES)
};

enum COR_PRF_HIGH_MONITOR
{
	COR_PRF_HIGH_MONITOR_NONE = 0,
	COR_PRF_HIGH_ADD_ASSEMBLY_REFERENCES = 0x1,
	COR_PRF_HIGH_IN_MEMORY_SYMBOLS_UPDATED = 0x2,
	COR_PRF_HIGH_MONITOR_DYNAMIC_FUNCTION_UNLOADS = 0x4,
	COR_PRF_HIGH_REQUIRE_PROFILE_IMAGE = 0,
	COR_PRF_HIGH_ALLOWABLE_AFTER_ATTACH = (COR_PRF_HIGH_IN_MEMORY_SYMBOLS_UPDATED | COR_PRF_HIGH_MONITOR_DYNAMIC_FUNCTION_UNLOADS),
	COR_PRF_HIGH_MONITOR_IMMUTABLE = 0
};

enum COR_PRF_JIT_CACHE
{
	COR_PRF_CACHED_FUNCTION_FOUND = 0,
	COR_PRF_CACHED_FUNCTION_NOT_FOUND = (COR_PRF_CACHED_FUNCTION_FOUND + 1)
};

enum COR_PRF_TRANSITION_REASON
{
	COR_PRF_TRANSITION_CALL = 0,
	COR_PRF_TRANSITION_RETURN = (COR_PRF_TRANSITION_CALL + 1)
};

enum COR_PRF_SUSPEND_REASON
{
	COR_PRF_SUSPEND_OTHER = 0,
	COR_PRF_SUSPEND_FOR_GC = 1,
	COR_PRF_SUSPEND_FOR_APPDOMAIN_SHUTDOWN = 2,
	COR_PRF_SUSPEND_FOR_CODE_PITCHING = 3,
	COR_PRF_SUSPEND_FOR_SHUTDOWN = 4,
	COR_PRF_SUSPEND_FOR_INPROC_DEBUGGER = 6,
	COR_PRF_SUSPEND_FOR_GC_PREP = 7,
	COR_PRF_SUSPEND_FOR_REJIT = 8
};

enum COR_PRF_RUNTIME_TYPE
{
	COR_PRF_DESKTOP_CLR = 0x1,
	COR_PRF_CORE_CLR = 0x2
};


static const IID IID_ICorProfilerCallback = { 0x176fbed1, 0xa55c, 0x4796, { 0x98, 0xca, 0xa9, 0xda, 0x0e, 0xf8, 0x83, 0xe7 } };

struct ICorProfilerCallback : public IUnknown
{

public:

	virtual HRESULT STDMETHODCALLTYPE Initialize(
		IUnknown* pICorProfilerInfoUnk) = 0;

	virtual HRESULT STDMETHODCALLTYPE Shutdown(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE AppDomainCreationStarted(
		AppDomainID appDomainId) = 0;

	virtual HRESULT STDMETHODCALLTYPE AppDomainCreationFinished(
		AppDomainID appDomainId,
		HRESULT hrStatus) = 0;

	virtual HRESULT STDMETHODCALLTYPE AppDomainShutdownStarted(
		AppDomainID appDomainId) = 0;

	virtual HRESULT STDMETHODCALLTYPE AppDomainShutdownFinished(
		AppDomainID appDomainId,
		HRESULT hrStatus) = 0;

	virtual HRESULT STDMETHODCALLTYPE AssemblyLoadStarted(
		AssemblyID assemblyId) = 0;

	virtual HRESULT STDMETHODCALLTYPE AssemblyLoadFinished(
		AssemblyID assemblyId,
		HRESULT hrStatus) = 0;

	virtual HRESULT STDMETHODCALLTYPE AssemblyUnloadStarted(
		AssemblyID assemblyId) = 0;

	virtual HRESULT STDMETHODCALLTYPE AssemblyUnloadFinished(
		AssemblyID assemblyId,
		HRESULT hrStatus) = 0;

	virtual HRESULT STDMETHODCALLTYPE ModuleLoadStarted(
		ModuleID moduleId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ModuleLoadFinished(
		ModuleID moduleId,
		HRESULT hrStatus) = 0;

	virtual HRESULT STDMETHODCALLTYPE ModuleUnloadStarted(
		ModuleID moduleId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ModuleUnloadFinished(
		ModuleID moduleId,
		HRESULT hrStatus) = 0;

	virtual HRESULT STDMETHODCALLTYPE ModuleAttachedToAssembly(
		ModuleID moduleId,
		AssemblyID AssemblyId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ClassLoadStarted(
		ClassID classId) = 0;
	virtual HRESULT STDMETHODCALLTYPE ClassLoadFinished(
		ClassID classId,
		HRESULT hrStatus) = 0;

	virtual HRESULT STDMETHODCALLTYPE ClassUnloadStarted(
		ClassID classId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ClassUnloadFinished(
		ClassID classId,
		HRESULT hrStatus) = 0;

	virtual HRESULT STDMETHODCALLTYPE FunctionUnloadStarted(
		FunctionID functionId) = 0;

	virtual HRESULT STDMETHODCALLTYPE JITCompilationStarted(
		FunctionID functionId,
		BOOL fIsSafeToBlock) = 0;

	virtual HRESULT STDMETHODCALLTYPE JITCompilationFinished(
		FunctionID functionId,
		HRESULT hrStatus,
		BOOL fIsSafeToBlock) = 0;

	virtual HRESULT STDMETHODCALLTYPE JITCachedFunctionSearchStarted(
		FunctionID functionId,
		BOOL* pbUseCachedFunction) = 0;

	virtual HRESULT STDMETHODCALLTYPE JITCachedFunctionSearchFinished(
		FunctionID functionId,
		COR_PRF_JIT_CACHE result) = 0;

	virtual HRESULT STDMETHODCALLTYPE JITFunctionPitched(
		FunctionID functionId) = 0;

	virtual HRESULT STDMETHODCALLTYPE JITInlining(
		FunctionID callerId,
		FunctionID calleeId,
		BOOL* pfShouldInline) = 0;

	virtual HRESULT STDMETHODCALLTYPE ThreadCreated(
		ThreadID threadId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ThreadDestroyed(
		ThreadID threadId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ThreadAssignedToOSThread(
		ThreadID managedThreadId,
		DWORD osThreadId) = 0;

	virtual HRESULT STDMETHODCALLTYPE RemotingClientInvocationStarted(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE RemotingClientSendingMessage(
		GUID* pCookie,
		BOOL fIsAsync) = 0;

	virtual HRESULT STDMETHODCALLTYPE RemotingClientReceivingReply(
		GUID* pCookie,
		BOOL fIsAsync) = 0;

	virtual HRESULT STDMETHODCALLTYPE RemotingClientInvocationFinished(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE RemotingServerReceivingMessage(
		GUID* pCookie,
		BOOL fIsAsync) = 0;

	virtual HRESULT STDMETHODCALLTYPE RemotingServerInvocationStarted(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE RemotingServerInvocationReturned(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE RemotingServerSendingReply(
		GUID* pCookie,
		BOOL fIsAsync) = 0;

	virtual HRESULT STDMETHODCALLTYPE UnmanagedToManagedTransition(
		FunctionID functionId,
		COR_PRF_TRANSITION_REASON reason) = 0;

	virtual HRESULT STDMETHODCALLTYPE ManagedToUnmanagedTransition(
		FunctionID functionId,
		COR_PRF_TRANSITION_REASON reason) = 0;

	virtual HRESULT STDMETHODCALLTYPE RuntimeSuspendStarted(
		COR_PRF_SUSPEND_REASON suspendReason) = 0;

	virtual HRESULT STDMETHODCALLTYPE RuntimeSuspendFinished(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE RuntimeSuspendAborted(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE RuntimeResumeStarted(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE RuntimeResumeFinished(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE RuntimeThreadSuspended(
		ThreadID threadId) = 0;

	virtual HRESULT STDMETHODCALLTYPE RuntimeThreadResumed(
		ThreadID threadId) = 0;

	virtual HRESULT STDMETHODCALLTYPE MovedReferences(
		ULONG cMovedObjectIDRanges,
		ObjectID oldObjectIDRangeStart[],
		ObjectID newObjectIDRangeStart[],
		ULONG cObjectIDRangeLength[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE ObjectAllocated(
		ObjectID objectId,
		ClassID classId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ObjectsAllocatedByClass(
		ULONG cClassCount,
		ClassID classIds[],
		ULONG cObjects[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE ObjectReferences(
		ObjectID objectId,
		ClassID classId,
		ULONG cObjectRefs,
		ObjectID objectRefIds[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE RootReferences(
		ULONG cRootRefs,
		ObjectID rootRefIds[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionThrown(
		ObjectID thrownObjectId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionSearchFunctionEnter(
		FunctionID functionId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionSearchFunctionLeave(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionSearchFilterEnter(
		FunctionID functionId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionSearchFilterLeave(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionSearchCatcherFound(
		FunctionID functionId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionOSHandlerEnter(
		UINT_PTR __unused) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionOSHandlerLeave(
		UINT_PTR __unused) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionUnwindFunctionEnter(
		FunctionID functionId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionUnwindFunctionLeave(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionUnwindFinallyEnter(
		FunctionID functionId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionUnwindFinallyLeave(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionCatcherEnter(
		FunctionID functionId,
		ObjectID objectId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionCatcherLeave(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE COMClassicVTableCreated(
		ClassID wrappedClassId,
		const GUID& implementedIID,
		void* pVTable,
		ULONG cSlots) = 0;

	virtual HRESULT STDMETHODCALLTYPE COMClassicVTableDestroyed(
		ClassID wrappedClassId,
		const GUID& implementedIID,
		void* pVTable) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionCLRCatcherFound(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE ExceptionCLRCatcherExecute(void) = 0;

};

enum COR_PRF_GC_ROOT_KIND
{
	COR_PRF_GC_ROOT_STACK = 1,
	COR_PRF_GC_ROOT_FINALIZER = 2,
	COR_PRF_GC_ROOT_HANDLE = 3,
	COR_PRF_GC_ROOT_OTHER = 0
};

enum COR_PRF_GC_ROOT_FLAGS
{
	COR_PRF_GC_ROOT_PINNING = 0x1,
	COR_PRF_GC_ROOT_WEAKREF = 0x2,
	COR_PRF_GC_ROOT_INTERIOR = 0x4,
	COR_PRF_GC_ROOT_REFCOUNTED = 0x8
};

enum COR_PRF_GC_GENERATION
{
	COR_PRF_GC_GEN_0 = 0,
	COR_PRF_GC_GEN_1 = 1,
	COR_PRF_GC_GEN_2 = 2,
	COR_PRF_GC_LARGE_OBJECT_HEAP = 3
};

struct COR_PRF_GC_GENERATION_RANGE
{
	COR_PRF_GC_GENERATION generation;
	ObjectID rangeStart;
	UINT_PTR rangeLength;
	UINT_PTR rangeLengthReserved;
};

enum COR_PRF_CLAUSE_TYPE
{
	COR_PRF_CLAUSE_NONE = 0,
	COR_PRF_CLAUSE_FILTER = 1,
	COR_PRF_CLAUSE_CATCH = 2,
	COR_PRF_CLAUSE_FINALLY = 3
};

struct COR_PRF_EX_CLAUSE_INFO
{
	COR_PRF_CLAUSE_TYPE clauseType;
	UINT_PTR programCounter;
	UINT_PTR framePointer;
	UINT_PTR shadowStackPointer;
};

enum COR_PRF_GC_REASON
{
	COR_PRF_GC_INDUCED = 1,
	COR_PRF_GC_OTHER = 0
};


static const IID IID_ICorProfilerCallback2 = { 0x8a8cc829, 0xccf2, 0x49fe, { 0xbb, 0xae, 0x0f, 0x02, 0x22, 0x28, 0x07, 0x1a } };

struct ICorProfilerCallback2 : public ICorProfilerCallback
{

public:

	virtual HRESULT STDMETHODCALLTYPE ThreadNameChanged(
		ThreadID threadId,
		ULONG cchName,
		WCHAR name[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GarbageCollectionStarted(
		int cGenerations,
		BOOL generationCollected[],
		COR_PRF_GC_REASON reason) = 0;

	virtual HRESULT STDMETHODCALLTYPE SurvivingReferences(
		ULONG cSurvivingObjectIDRanges,
		ObjectID objectIDRangeStart[],
		ULONG cObjectIDRangeLength[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GarbageCollectionFinished(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE FinalizeableObjectQueued(
		DWORD finalizerFlags,
		ObjectID objectID) = 0;

	virtual HRESULT STDMETHODCALLTYPE RootReferences2(
		ULONG cRootRefs,
		ObjectID rootRefIds[],
		COR_PRF_GC_ROOT_KIND rootKinds[],
		COR_PRF_GC_ROOT_FLAGS rootFlags[],
		UINT_PTR rootIds[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE HandleCreated(
		GCHandleID handleId,
		ObjectID initialObjectId) = 0;

	virtual HRESULT STDMETHODCALLTYPE HandleDestroyed(
		GCHandleID handleId) = 0;

};


static const IID IID_ICorProfilerCallback3 = { 0x4fd2ed52, 0x7731, 0x4b8d, { 0x94, 0x69, 0x03, 0xd2, 0xcc, 0x30, 0x86, 0xc5 } };

struct ICorProfilerCallback3 : public ICorProfilerCallback2
{

public:

	virtual HRESULT STDMETHODCALLTYPE InitializeForAttach(
		IUnknown* pCorProfilerInfoUnk,
		void* pvClientData,
		UINT cbClientData) = 0;

	virtual HRESULT STDMETHODCALLTYPE ProfilerAttachComplete(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE ProfilerDetachSucceeded(void) = 0;

};


static const IID IID_IMethodMalloc = { 0xa0efb28b, 0x6ee2, 0x4d7b, { 0xb9, 0x83, 0xa7, 0x5e, 0xf7, 0xbe, 0xed, 0xb8 } };

struct IMethodMalloc : public IUnknown
{

public:

	virtual PVOID STDMETHODCALLTYPE Alloc(
		/* [in] */ ULONG cb) = 0;

};

static const IID IID_ICorProfilerInfo = { 0x28b5557d, 0x3f3f, 0x48b4, { 0x90, 0xb2, 0x5f, 0x9e, 0xea, 0x2f, 0x6c, 0x48 } };

struct ICorProfilerInfo : public IUnknown
{

public:

	virtual HRESULT STDMETHODCALLTYPE GetClassFromObject(
		ObjectID objectId,
		ClassID* pClassId) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetClassFromToken(
		ModuleID moduleId,
		mdTypeDef typeDef,
		ClassID* pClassId) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCodeInfo(
		FunctionID functionId,
		LPCBYTE* pStart,
		ULONG* pcSize) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetEventMask(
		DWORD* pdwEvents) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFunctionFromIP(
		LPCBYTE ip,
		FunctionID* pFunctionId) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFunctionFromToken(
		ModuleID moduleId,
		mdToken token,
		FunctionID* pFunctionId) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetHandleFromThread(
		ThreadID threadId,
		HANDLE* phThread) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetObjectSize(
		ObjectID objectId,
		ULONG* pcSize) = 0;

	virtual HRESULT STDMETHODCALLTYPE IsArrayClass(
		ClassID classId,
		CorElementType* pBaseElemType,
		ClassID* pBaseClassId,
		ULONG* pcRank) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetThreadInfo(
		ThreadID threadId,
		DWORD* pdwWin32ThreadId) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentThreadID(
		ThreadID* pThreadId) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetClassIDInfo(
		ClassID classId,
		ModuleID* pModuleId,
		mdTypeDef* pTypeDefToken) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFunctionInfo(
		FunctionID functionId,
		ClassID* pClassId,
		ModuleID* pModuleId,
		mdToken* pToken) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetEventMask(
		DWORD dwEvents) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetEnterLeaveFunctionHooks(
		FunctionEnter* pFuncEnter,
		FunctionLeave* pFuncLeave,
		FunctionTailcall* pFuncTailcall) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetFunctionIDMapper(
		FunctionIDMapper* pFunc) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTokenAndMetaDataFromFunction(
		FunctionID functionId,
		const IID& riid,
		IUnknown** ppImport,
		mdToken* pToken) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetModuleInfo(
		ModuleID moduleId,
		LPCBYTE* ppBaseLoadAddress,
		ULONG cchName,
		ULONG* pcchName,
		WCHAR szName[],
		AssemblyID* pAssemblyId) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetModuleMetaData(
		ModuleID moduleId,
		DWORD dwOpenFlags,
		const IID& riid,
		IUnknown** ppOut) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetILFunctionBody(
		ModuleID moduleId,
		mdMethodDef methodId,
		LPCBYTE* ppMethodHeader,
		ULONG* pcbMethodSize) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetILFunctionBodyAllocator(
		ModuleID moduleId,
		IMethodMalloc** ppMalloc) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetILFunctionBody(
		ModuleID moduleId,
		mdMethodDef methodid,
		LPCBYTE pbNewILMethodHeader) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAppDomainInfo(
		AppDomainID appDomainId,
		ULONG cchName,
		ULONG* pcchName,
		WCHAR szName[],
		ProcessID* pProcessId) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAssemblyInfo(
		AssemblyID assemblyId,
		ULONG cchName,
		ULONG* pcchName,
		WCHAR szName[],
		AppDomainID* pAppDomainId,
		ModuleID* pModuleId) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetFunctionReJIT(
		FunctionID functionId) = 0;

	virtual HRESULT STDMETHODCALLTYPE ForceGC(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetILInstrumentedCodeMap(
		FunctionID functionId,
		BOOL fStartJit,
		ULONG cILMapEntries,
		COR_IL_MAP rgILMapEntries[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetInprocInspectionInterface(
		IUnknown** ppicd) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetInprocInspectionIThisThread(
		IUnknown** ppicd) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetThreadContext(
		ThreadID threadId,
		ContextID* pContextId) = 0;

	virtual HRESULT STDMETHODCALLTYPE BeginInprocDebugging(
		BOOL fThisThreadOnly,
		DWORD* pdwProfilerContext) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndInprocDebugging(
		DWORD dwProfilerContext) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetILToNativeMapping(
		FunctionID functionId,
		ULONG32 cMap,
		ULONG32* pcMap,
		COR_DEBUG_IL_TO_NATIVE_MAP map[]) = 0;

};


static const IID IID_ICorProfilerObjectEnum = { 0x2c6269bd, 0x2d13, 0x4321, { 0xae, 0x12, 0x66, 0x86, 0x36, 0x5f, 0xd6, 0xaf } };

struct ICorProfilerObjectEnum : public IUnknown
{

public:

	virtual HRESULT STDMETHODCALLTYPE Skip(
		/* [in] */ ULONG celt) = 0;

	virtual HRESULT STDMETHODCALLTYPE Reset(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE Clone(
		/* [out] */ ICorProfilerObjectEnum** ppEnum) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCount(
		/* [out] */ ULONG* pcelt) = 0;

	virtual HRESULT STDMETHODCALLTYPE Next(
		/* [in] */ ULONG celt,
		/* [length_is][size_is][out] */ ObjectID objects[],
		/* [out] */ ULONG* pceltFetched) = 0;

};


static const IID IID_ICorProfilerFunctionEnum = { 0xff71301a, 0xb994, 0x429d, { 0xa1, 0x0b, 0xb3, 0x45, 0xa6, 0x52, 0x80, 0xef } };

struct ICorProfilerFunctionEnum : public IUnknown
{

public:

	virtual HRESULT STDMETHODCALLTYPE Skip(
		/* [in] */ ULONG celt) = 0;

	virtual HRESULT STDMETHODCALLTYPE Reset(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE Clone(
		/* [out] */ ICorProfilerFunctionEnum** ppEnum) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCount(
		/* [out] */ ULONG* pcelt) = 0;

	virtual HRESULT STDMETHODCALLTYPE Next(
		/* [in] */ ULONG celt,
		/* [length_is][size_is][out] */ COR_PRF_FUNCTION ids[],
		/* [out] */ ULONG* pceltFetched) = 0;

};


static const IID IID_ICorProfilerModuleEnum = { 0xb0266d75, 0x2081,0x4493, { 0xaf, 0x7f, 0x02, 0x8b, 0xa3, 0x4d, 0xb8, 0x91 } };

struct ICorProfilerModuleEnum : public IUnknown
{

public:

	virtual HRESULT STDMETHODCALLTYPE Skip(
		/* [in] */ ULONG celt) = 0;

	virtual HRESULT STDMETHODCALLTYPE Reset(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE Clone(
		/* [out] */ ICorProfilerModuleEnum** ppEnum) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCount(
		/* [out] */ ULONG* pcelt) = 0;

	virtual HRESULT STDMETHODCALLTYPE Next(
		/* [in] */ ULONG celt,
		/* [length_is][size_is][out] */ ModuleID ids[],
		/* [out] */ ULONG* pceltFetched) = 0;

};


static const IID IID_ICorProfilerInfo2 = { 0xcc0935cd, 0xa518, 0x487d, { 0xb0, 0xbb, 0xa9, 0x32, 0x14, 0xe6, 0x54, 0x78 } };

struct ICorProfilerInfo2 : public ICorProfilerInfo
{

public:

	virtual HRESULT STDMETHODCALLTYPE DoStackSnapshot(
		ThreadID thread,
		StackSnapshotCallback* callback,
		ULONG32 infoFlags,
		void* clientData,
		BYTE context[],
		ULONG32 contextSize) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetEnterLeaveFunctionHooks2(
		FunctionEnter2* pFuncEnter,
		FunctionLeave2* pFuncLeave,
		FunctionTailcall2* pFuncTailcall) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFunctionInfo2(
		FunctionID funcId,
		COR_PRF_FRAME_INFO frameInfo,
		ClassID* pClassId,
		ModuleID* pModuleId,
		mdToken* pToken,
		ULONG32 cTypeArgs,
		ULONG32* pcTypeArgs,
		ClassID typeArgs[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetStringLayout(
		ULONG* pBufferLengthOffset,
		ULONG* pStringLengthOffset,
		ULONG* pBufferOffset) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetClassLayout(
		ClassID classID,
		COR_FIELD_OFFSET rFieldOffset[],
		ULONG cFieldOffset,
		ULONG* pcFieldOffset,
		ULONG* pulClassSize) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetClassIDInfo2(
		ClassID classId,
		ModuleID* pModuleId,
		mdTypeDef* pTypeDefToken,
		ClassID* pParentClassId,
		ULONG32 cNumTypeArgs,
		ULONG32* pcNumTypeArgs,
		ClassID typeArgs[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCodeInfo2(
		FunctionID functionID,
		ULONG32 cCodeInfos,
		ULONG32* pcCodeInfos,
		COR_PRF_CODE_INFO codeInfos[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetClassFromTokenAndTypeArgs(
		ModuleID moduleID,
		mdTypeDef typeDef,
		ULONG32 cTypeArgs,
		ClassID typeArgs[],
		ClassID* pClassID) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFunctionFromTokenAndTypeArgs(
		ModuleID moduleID,
		mdMethodDef funcDef,
		ClassID classId,
		ULONG32 cTypeArgs,
		ClassID typeArgs[],
		FunctionID* pFunctionID) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumModuleFrozenObjects(
		ModuleID moduleID,
		ICorProfilerObjectEnum** ppEnum) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetArrayObjectInfo(
		ObjectID objectId,
		ULONG32 cDimensions,
		ULONG32 pDimensionSizes[],
		int pDimensionLowerBounds[],
		BYTE** ppData) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetBoxClassLayout(
		ClassID classId,
		ULONG32* pBufferOffset) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetThreadAppDomain(
		ThreadID threadId,
		AppDomainID* pAppDomainId) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetRVAStaticAddress(
		ClassID classId,
		mdFieldDef fieldToken,
		void** ppAddress) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAppDomainStaticAddress(
		ClassID classId,
		mdFieldDef fieldToken,
		AppDomainID appDomainId,
		void** ppAddress) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetThreadStaticAddress(
		ClassID classId,
		mdFieldDef fieldToken,
		ThreadID threadId,
		void** ppAddress) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetContextStaticAddress(
		ClassID classId,
		mdFieldDef fieldToken,
		ContextID contextId,
		void** ppAddress) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetStaticFieldInfo(
		ClassID classId,
		mdFieldDef fieldToken,
		COR_PRF_STATIC_TYPE* pFieldInfo) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetGenerationBounds(
		ULONG cObjectRanges,
		ULONG* pcObjectRanges,
		COR_PRF_GC_GENERATION_RANGE ranges[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetObjectGeneration(
		ObjectID objectId,
		COR_PRF_GC_GENERATION_RANGE* range) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNotifiedExceptionClauseInfo(
		COR_PRF_EX_CLAUSE_INFO* pinfo) = 0;
};


static const IID IID_ICorProfilerInfo3 = { 0xb555ed4f, 0x452a, 0x4e54, { 0x8b, 0x39, 0xb5, 0x36, 0x0b, 0xad, 0x32, 0xa0 } };

struct ICorProfilerInfo3 : public ICorProfilerInfo2
{

public:

	virtual HRESULT STDMETHODCALLTYPE EnumJITedFunctions(
		ICorProfilerFunctionEnum** ppEnum) = 0;

	virtual HRESULT STDMETHODCALLTYPE RequestProfilerDetach(
		DWORD dwExpectedCompletionMilliseconds) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetFunctionIDMapper2(
		FunctionIDMapper2* pFunc,
		void* clientData) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetStringLayout2(
		ULONG* pStringLengthOffset,
		ULONG* pBufferOffset) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetEnterLeaveFunctionHooks3(
		FunctionEnter3* pFuncEnter3,
		FunctionLeave3* pFuncLeave3,
		FunctionTailcall3* pFuncTailcall3) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetEnterLeaveFunctionHooks3WithInfo(
		FunctionEnter3WithInfo* pFuncEnter3WithInfo,
		FunctionLeave3WithInfo* pFuncLeave3WithInfo,
		FunctionTailcall3WithInfo* pFuncTailcall3WithInfo) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFunctionEnter3Info(
		FunctionID functionId,
		COR_PRF_ELT_INFO eltInfo,
		COR_PRF_FRAME_INFO* pFrameInfo,
		ULONG* pcbArgumentInfo,
		COR_PRF_FUNCTION_ARGUMENT_INFO* pArgumentInfo) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFunctionLeave3Info(
		FunctionID functionId,
		COR_PRF_ELT_INFO eltInfo,
		COR_PRF_FRAME_INFO* pFrameInfo,
		COR_PRF_FUNCTION_ARGUMENT_RANGE* pRetvalRange) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFunctionTailcall3Info(
		FunctionID functionId,
		COR_PRF_ELT_INFO eltInfo,
		COR_PRF_FRAME_INFO* pFrameInfo) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumModules(
		ICorProfilerModuleEnum** ppEnum) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetRuntimeInformation(
		USHORT* pClrInstanceId,
		COR_PRF_RUNTIME_TYPE* pRuntimeType,
		USHORT* pMajorVersion,
		USHORT* pMinorVersion,
		USHORT* pBuildNumber,
		USHORT* pQFEVersion,
		ULONG cchVersionString,
		ULONG* pcchVersionString,
		WCHAR szVersionString[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetThreadStaticAddress2(
		ClassID classId,
		mdFieldDef fieldToken,
		AppDomainID appDomainId,
		ThreadID threadId,
		void** ppAddress) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAppDomainsContainingModule(
		ModuleID moduleId,
		ULONG32 cAppDomainIds,
		ULONG32* pcAppDomainIds,
		AppDomainID appDomainIds[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetModuleInfo2(
		ModuleID moduleId,
		LPCBYTE* ppBaseLoadAddress,
		ULONG cchName,
		ULONG* pcchName,
		WCHAR szName[],
		AssemblyID* pAssemblyId,
		DWORD* pdwModuleFlags) = 0;

};
