#pragma once

#ifdef WIN32
#pragma warning( disable : 4267 )  // Disable warning messages
#endif

#ifdef _DEBUG
#define _RWCONFIG 15s
#else
#define _RWCONFIG 12s
#endif

#include <rw/thread/RWServerPool.h>
#include <rw/itc/RWTIOUResult.h>
#include <rw/thread/rwtMakeRunnableIOUFunction.h>
#include <rw/network/RWSocketPortal.h>
#include <rw/cstring.h>
#include <rw/bstream.h>
#include <rw/rstream.h>

//#include <rw/network/RWPortalOStream.h>
#include <rw/network/RWWinSockInfo.h>

#include <rw/ftp/RWFtpAgent.h>

#define _ThisClass		CRwFtp

using namespace std;

namespace slapware 
{    // begin SlapWare namespace
	class CRwFtp
	{
	public:
		CRwFtp(size_t numThreads);
		CRwFtp(size_t numThreads, size_t numQueue);
		virtual ~CRwFtp(void);
		RWTIOUResult<int> asyncService(string& input, RWCString& output, int recid);
		int PutFile(string& input, RWCString& output, int recid);
		RWCString User() const { return m_user; }
		void User(RWCString& val) { m_user = val; }
		RWCString Pswd() const { return m_pswd; }
		void Pswd(RWCString& val) { m_pswd = val; }
		RWCString Host() const { return m_host; }
		void Host(RWCString& val) { m_host = val; }

	private:
		RWServerPool server_;
		//RWFtpAgent agent_;
		RWCString m_user;
		RWCString m_pswd;
		RWCString m_host;
	};
}   // end SlapWare namespace
#undef _ThisClass
