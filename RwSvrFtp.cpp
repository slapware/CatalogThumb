#include "RwSvrFtp.h"

#define _ThisClass		CRwFtp

//using namespace slapware;

namespace slapware 
{    // begin SlapWare namespace
	CRwFtp::CRwFtp(size_t numThreads)
	{
		server_ = RWServerPool::make(numThreads);
		server_.start();
	}

	CRwFtp::CRwFtp(size_t numThreads, size_t numQueue)
	{
		server_ = RWServerPool::make(numThreads, numQueue);
		server_.start();
	}

	CRwFtp::~CRwFtp()
	{
		server_.stop();
		server_.join();
	}

	RWTIOUResult<int> CRwFtp::asyncService(string& input, RWCString& output, int recid)
	{
		RWTRunnableIOUFunction<int> runnable;
		runnable = rwtMakeRunnableIOUFunctionMA3(_ThisClass, *this, int,
			&_ThisClass::PutFile, string&, input, RWCString&, output,
			int, recid);
		server_.enqueue(runnable);
		return( runnable.result() );
	}

	int CRwFtp::PutFile(string& input, RWCString& output, int recid)
	{
		RWFtpAgent agent_(m_host.data(), m_user, m_pswd);

		return 0;
	}
}   // end SlapWare namespace
#undef _ThisClass
