// dllmain.h : Declaration of module class.

class CFileMgrComponentModule : public ATL::CAtlDllModuleT< CFileMgrComponentModule >
{
public :
	DECLARE_LIBID(LIBID_FileMgrComponentLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FILEMGRCOMPONENT, "{5A24A414-7683-4934-8A7A-4A221EFDAAC3}")
};

extern class CFileMgrComponentModule _AtlModule;
