// dllmain.h : Declaration of module class.

class CATLProject3Module : public ATL::CAtlDllModuleT< CATLProject3Module >
{
public :
	DECLARE_LIBID(LIBID_ATLProject3Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROJECT3, "{78DCAB93-F383-46B0-881D-9647EE2A61BE}")
};

extern class CATLProject3Module _AtlModule;
