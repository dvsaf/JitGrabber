#pragma once

#define S_OK                                   ((HRESULT)0L)
#define S_FALSE                                ((HRESULT)1L)

//
// Generic test for success on any status value (non-negative numbers
// indicate success).
//

#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)

//
// and the inverse
//

#define FAILED(hr) (((HRESULT)(hr)) < 0)

//
// MessageId: E_NOTIMPL
//
// MessageText:
//
// Not implemented
//
#define E_NOTIMPL                        ((HRESULT)0x80004001L)

//
// MessageId: E_NOINTERFACE
//
// MessageText:
//
// No such interface supported
//
#define E_NOINTERFACE                    ((HRESULT)0x80004002L)

//
// MessageId: E_FAIL
//
// MessageText:
//
// Unspecified error
//
#define E_FAIL                           ((HRESULT)0x80004005L)

//
// MessageId: CLASS_E_NOAGGREGATION
//
// MessageText:
//
// Class does not support aggregation (or class object is remote)
//
#define CLASS_E_NOAGGREGATION            ((HRESULT)0x80040110L)

//
// MessageId: CLASS_E_CLASSNOTAVAILABLE
//
// MessageText:
//
// ClassFactory cannot supply requested class
//
#define CLASS_E_CLASSNOTAVAILABLE        ((HRESULT)0x80040111L)

//
// MessageId: E_OUTOFMEMORY
//
// MessageText:
//
// Ran out of memory
//
#define E_OUTOFMEMORY                    ((HRESULT)0x8007000EL)
