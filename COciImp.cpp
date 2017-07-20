// SlapWare created 3/23/2009 2:14pm MySql access usage.
#include "COciImp.h"

#define _ThisClass		CCOciImp
namespace slapware 
{    // begin SlapWare namespace
    CCOciImp::CCOciImp(void)
    {
    }

    CCOciImp::~CCOciImp(void)
    {
    }

    CCOciImp::CCOciImp(const RWCString& _server, const RWCString _user, const RWCString _pswd) :
    m_server(_server), m_user(_user), m_pswd(_pswd)
    {
        init();
    }
    ///////////////////////
    //is connection valid//
    ///////////////////////
    bool CCOciImp::check(void)
    {
        if (mySql.isValid())
        {
            return true;
        } else
        {
            return false;
        }
        return false;
    }
    ///////////////////////
    //Make the connection//
    ///////////////////////
    void CCOciImp::init(void)
    {
        try
        {
            mySql = RWDBManager::database("ORACLE_OCI", m_server, m_user, m_pswd, "");
            RWDBStatus status = mySql.status();
        } catch (RWxmsg emsg)
        {
            RWCString why = emsg.why();
        }
        //m_conn = mySql.connection();
    }
    ///////////////////
    // SELECT Section//
    ///////////////////
    bool CCOciImp::DoSelect(const RWCString& _param1, const RWCString& _param2)
    {
        bool isOK = check();
        RWDBTable dbmap = mySql.table("mapback");
        RWDBSelector selector = mySql.selector();
        selector << dbmap["URL"]
        << dbmap["TYPE"];
        selector.where(dbmap["NAME"] == _param1 && dbmap["FORMAT"] == _param2);
        RWDBReader rdr = selector.reader(m_conn);
        while (rdr())
        {
            if (rdr.isValid())
            {
                rdr >> m_param1 >> m_param2;
            }
        }
        return true;
    }

    RWCString CCOciImp::GetURL()
    {
        return m_param1;
    }

    RWCString CCOciImp::GetType()
    {
        return m_param2;
    }

	RWDBStatus CCOciImp::GetStatus()
	{
		RWDBStatus status = mySql.status();
		return status;
	}

	int CCOciImp::GetCount(RWCString& pSql)
	{
		RWDBConnection conn = mySql.connection();
		RWDBOSql myQuery(pSql);
		RWDBTBuffer<unsigned> result(1);
		myQuery.execute(conn);
		int answ = 0;
		if( myQuery.isValid(), RWDBOSql::Query ) 
		{
			myQuery[0] >> result;
			while (myQuery.fetch(), myQuery.rowsFetched() > 0)
			{
				answ = result[0];
			}
		}
		return answ;
	}

	int CCOciImp::GetStrInt(RWCString& pSql, RWCString& param1, int& param2)
	{
		RWDBConnection conn = mySql.connection();
		RWDBOSql myQuery(pSql);
		myQuery.execute(conn);
		if( myQuery.isValid(), myQuery.hasResult() ) 
		{
			RWDBTBuffer<RWCString> szparam(1);
			RWDBTBuffer<unsigned int> result(1);
			unsigned int res = 0;
			myQuery[0] >> szparam >> result;
			while (myQuery.fetch(), myQuery.rowsFetched() > 0)
			{
				param1 = szparam[0];
				res = result[0];
				param2 = res;
			}
		}
		if(myQuery.rowsFetched() == 0)
			return 0;
		else
			return 1;
	}

	int CCOciImp::GetStrStr(RWCString& pSql, RWCString& param1, RWCString& param2)
	{
		RWDBConnection conn = mySql.connection();
		RWDBOSql myQuery(pSql);
		myQuery.execute(conn);
		if( myQuery.isValid(), RWDBOSql::Query ) 
		{
			RWDBTBuffer<RWCString> szparam1(1);
			RWDBTBuffer<RWCString> szparam2(1);
			myQuery[0] >> szparam1 >> szparam2; 
			while (myQuery.fetch(), myQuery.rowsFetched() > 0)
			{
				param1 = szparam1[0];
				param2 = szparam2[0];
			}
		}
		if(myQuery.rowsFetched() == 0)
			return 0;
		else
			return 1;
		return 1;
	}

	int CCOciImp::Update(RWCString& pSql)
	{
		RWDBConnection conn = mySql.connection();
		RWDBOSql myQuery(pSql);
		myQuery.execute(conn);
		//int result;
		//RWDBOSql >> result;
		return 1;
	}

	int CCOciImp::make_docMap(RWCString& pSql, map<int,RWCString>&myRef)
	{
		RWDBConnection conn = mySql.connection();
		RWDBOSql myQuery(pSql);
		myQuery.execute(conn);
		int didFetch = 0;
		if( myQuery.isValid(), myQuery.hasResult() ) 
		{
			RWDBTBuffer<unsigned int> ires(50);
			RWDBTBuffer<RWCString> szparam(50);
			unsigned int res = 0;
			myQuery[0] >> ires >> szparam;
			while (myQuery.fetch(), myQuery.rowsFetched() > 0)
			{
				for(int i = 0; i < myQuery.rowsFetched(); i++ ) 
				{
					myRef.insert(std::pair<int, RWCString>(ires[i], szparam[i]));
					didFetch++;
				}
			}
		}
		return didFetch;
	}
}   // end SlapWare namespace

#undef _ThisClass
