// dllmain.h : Declaration of module class.

class CTextSearchComponentModule : public ATL::CAtlDllModuleT< CTextSearchComponentModule >
{
public :
	DECLARE_LIBID(LIBID_TextSearchComponentLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TEXTSEARCHCOMPONENT, "{6FB4D796-FC0C-4200-A90E-D81843F58FAB}")
};

extern class CTextSearchComponentModule _AtlModule;
