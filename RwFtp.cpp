#include "RwFtp.h"

#define _ThisClass		CRwFtp

const size_t networkMaxWait = 40000;

namespace slapware 
{    // begin SlapWare namespace
	// The constructor initializes the pool so that it creates
	// 0 threads by default, will expand out to a maximum of 5 
	// threads, and will reduce the number of threads if any 
	// are idle for more than 500 milliseconds.
	CRwFtp::CRwFtp(size_t minThreads, size_t maxThreads)
		: pool_(RWThreadPool::make(minThreads, maxThreads, 500))
	{
		RWWinSockInfo winsock;
	}

	CRwFtp::~CRwFtp()
	{
		pool_.stop();
		if (m_verbose)
		{
			cout << "pool_.stop(): " << endl;
		}
	}

	void CRwFtp::handleRequest(string input, RWCString output, bool verbose)
	{
		m_verbose = verbose;
		RWFunctor0 functor;
		functor = rwtMakeFunctor0MA3(_ThisClass,
			*this,
			void,
			&_ThisClass::PutFile,
			string,
			input,
			RWCString,
			output,
			bool,
			verbose);

		pool_.enqueue(functor);
	}

	void CRwFtp::PutFile(string input, RWCString output, bool verbose)
	{
		try
		{
			RWFtpAgent agent_(m_host.data(), m_user, m_pswd);
			agent_.setTimeout(networkMaxWait);
			RWSocketPortal portal = agent_.put(output, RWFtpAgent::cmode_passive, RWFtpAgent::tmode_binary);
			RWStreamCoupler couple(RWStreamCoupler::mode_binary);
			RWTimedPortal tportal(portal, networkMaxWait);
			RWPortalOStream ostrm(tportal);
	
			ifstream infile(input.c_str(), ios::in | ios::binary);
			couple(infile, ostrm);
	
			RWBoolean b = agent_.dataClose();
		}
		catch (const RWxmsg& msg)
		{
			if (verbose)
			{
				cout << "Error in Thread: " << msg.why() << endl;
			}
			return;
		}
		catch (...)
		{
			if (verbose)
			{
				cout << "Error: Unexpected exception in Thread." << endl;
			}
			return;
		}
		return;
	}
}   // end SlapWare namespace
#undef _ThisClass
