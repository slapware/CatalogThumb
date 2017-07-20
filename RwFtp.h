#pragma once

#ifdef WIN32
#pragma warning( disable : 4267 )  // Disable warning messages
#endif

#ifdef _DEBUG
#define _RWCONFIG 15s
#else
#define _RWCONFIG 12s
#endif

#include <rw/thread/RWThreadPool.h>
#include <rw/functor/RWFunctor0.h>
#include <rw/functor/RWTFunctor0MA3Imp.h>
#include <rw/network/RWSocketPortal.h>
#include <rw/network/RWTimedPortal.h>
#include <rw/cstring.h>
#include <rw/bstream.h>
#include <rw/rstream.h>

#include <rw/network/RWPortalOStream.h>
#include <rw/network/RWWinSockInfo.h>
#include <rw/internet/RWStreamCoupler.h>

#include <rw/ftp/RWFtpAgent.h>
#include <fstream>

#define _ThisClass		CRwFtp

using namespace std;

namespace slapware 
{    // begin SlapWare namespace
	class CRwFtp
	{
	public:
		CRwFtp(size_t minThreads, size_t maxThreads);
		virtual ~CRwFtp(void);
		void handleRequest(string input, RWCString output, bool verbose);
		void PutFile(string input, RWCString output, bool verbose);
		RWCString User() const { return m_user; }
		void User(RWCString& val) { m_user = val; }
		RWCString Pswd() const { return m_pswd; }
		void Pswd(RWCString& val) { m_pswd = val; }
		RWCString Host() const { return m_host; }
		void Host(RWCString& val) { m_host = val; }

	private:
		RWThreadPool pool_;
		RWCString m_user;
		RWCString m_pswd;
		RWCString m_host;
		bool m_verbose;
	};
}   // end SlapWare namespace
#undef _ThisClass
