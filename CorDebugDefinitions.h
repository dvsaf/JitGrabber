#pragma once

struct COR_IL_MAP
{
	ULONG32 oldOffset;
	ULONG32 newOffset;
	BOOL fAccurate;
};

struct COR_DEBUG_IL_TO_NATIVE_MAP
{
	ULONG32 ilOffset;
	ULONG32 nativeStartOffset;
	ULONG32 nativeEndOffset;
};
