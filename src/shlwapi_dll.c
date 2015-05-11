/**
  * Win32 UTF-8 wrapper
  *
  * ----
  *
  * shlwapi.dll functions.
  */

#include <Shlwapi.h>
#include "win32_utf8.h"
#include "wrappers.h"

const w32u8_pair_t shlwapi_pairs[] = {
	{"PathFileExistsA", PathFileExistsU},
	{"PathMatchSpecA", PathMatchSpecU},
	{"PathRemoveFileSpecA", PathRemoveFileSpecU},
	NULL
};

BOOL STDAPICALLTYPE PathFileExistsU(
	LPCSTR pszPath
)
{
	return Wrap1P((Wrap1PFunc_t)PathFileExistsW, pszPath);
}

BOOL STDAPICALLTYPE PathMatchSpecU(
	LPCSTR pszFile,
	LPCSTR pszSpec
)
{
	BOOL ret;
	WCHAR_T_DEC(pszFile);
	WCHAR_T_DEC(pszSpec);
	WCHAR_T_CONV_VLA(pszFile);
	WCHAR_T_CONV_VLA(pszSpec);
	ret = PathMatchSpecW(pszFile_w, pszSpec_w);
	VLA_FREE(pszFile_w);
	VLA_FREE(pszSpec_w);
	return ret;
}

BOOL STDAPICALLTYPE PathRemoveFileSpecU(
	LPSTR pszPath
)
{
	// Hey, let's re-write the function to also handle forward slashes
	// while we're at it!
	LPSTR newPath = PathFindFileNameA(pszPath);
	if((newPath) && (newPath != pszPath)) {
		newPath[0] = TEXT('\0');
		return 1;
	}
	return 0;
}
