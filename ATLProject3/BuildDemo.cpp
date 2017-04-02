// BuildDemo.cpp : Implementation of CBuildDemo

#include "stdafx.h"
#include "BuildDemo.h"
#include <iostream>

// CBuildDemo



STDMETHODIMP CBuildDemo::putString(BSTR str)
{
  std::wcout << L"\n  " << str;

  return S_OK;
}


STDMETHODIMP CBuildDemo::getString(BSTR* str)
{
  CComBSTR ccBSTR = CComBSTR("Hello from server.");
  *str = ccBSTR.Detach();
  return S_OK;
}
