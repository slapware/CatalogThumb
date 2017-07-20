#include "COciHandle.h"

#define _ThisClass		CCOciHandle
namespace slapware 
{    // begin SlapWare namespace
    CCOciHandle::CCOciHandle(void)
    {
    }

    CCOciHandle::~CCOciHandle(void)
    {
    }

    CCOciHandle::CCOciHandle(const RWCString& _server, const RWCString _user, const RWCString _pswd) :
    RWHandleBase(new CCOciImp(_server, _user, _pswd))
    {
        //
    }

    CCOciImp& CCOciHandle::body() const
    {
        return(CCOciImp &)RWHandleBase::body();
    }

    bool CCOciHandle::check(void)
    {
        return(body().check());
    }

    bool CCOciHandle::DoSelect(const RWCString& _param1, const RWCString& _param2)
    {
        return(body().DoSelect(_param1, _param2));
    }

    RWCString CCOciHandle::GetURL()
    {
        return(body().GetURL());
    }

    RWCString CCOciHandle::GetType()
    {
        return(body().GetType());
    }

	RWDBStatus CCOciHandle::GetStatus()
	{
		return(body().GetStatus());
	}

	int CCOciHandle::GetCount(RWCString& pSql)
	{
		return(body().GetCount(pSql));
	}

	int CCOciHandle::GetStrInt(RWCString& pSql, RWCString& param1, int& param2)
	{
		return(body().GetStrInt(pSql, param1, param2));
	}

	int CCOciHandle::GetStrStr(RWCString& pSql, RWCString& param1, RWCString& param2)
	{
		return(body().GetStrStr(pSql, param1, param2));
	}

	int CCOciHandle::Update(RWCString& pSql)
	{
		return(body().Update(pSql));
	}

	int CCOciHandle::make_docMap(RWCString& pSql, map<int,RWCString>&myRef)
	{
		return(body().make_docMap(pSql, myRef));
	}

}   // end SlapWare namespace

#undef _ThisClass

