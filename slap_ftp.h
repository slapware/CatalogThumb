#ifndef __ftp__
#define __ftp__

//#include <winsock2.h>
#pragma warning(push)
#pragma warning(disable : 4996)

#include <io.h>
#include <errno.h>

#include <string>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include "CImageError.h"

#pragma warning(pop)

namespace slapware {    // begin SlapWare namespace

    const int m_buffLen = 1024;
    const int m_loginLen = 32;

    using namespace std;

    class ftp
    {

    public:
        bool IsConnect();
        ftp();
        ~ftp();
        int  DoOpen(string& command);
        void DoList(char *);
        int  DoCD(string& command);
        void DoShellCommand(char *);
        int  DoLogin(string& command);
        void DoClose(void);
        void DoLCD( char *);
        void DoPut( char *);
        int  DoPut( string&, string&);    // SLAP over ride for remote name
        void DoGet( char *);
        void DoLLS(char * );
        void DoBinary();
        void DoRhelp( char *);
        void DoAscii();
        int DoPWD();
        unsigned int get_ftpPort();
        void set_ftpPort(unsigned int new_ftpPort);
        int  CheckFds(char *);

    private:
        char szUser[m_loginLen];        /* stores username */
        char szPass[m_loginLen];        /* stores user password */
        int Connected;                  /* flag for connect status */
        //CImageError* ftpErr;
        std::string m_thr_error;
        int hListenSocket;
        int hControlSocket;
        int hDataSocket;
        typedef boost::shared_ptr<CImageError> CErrorPtr;
        typedef boost::shared_array<char> chrPrt;
        CErrorPtr ftpErr;
        chrPrt szBuffer;

        int bSendPort;
        std::ostringstream strstrm;
        int ReadCommand;
        int bMode;
        unsigned int m_ftpPort;

        int GetReply();
        int GetLine();
        void CleanUp();
        int SendControlMsg(char *, int);
        int SendDataMsg( char *szBuffer, int len);
        int ConnectToServer(const char *name, unsigned int& portnum);
        int GetListenSocket();
        int InitWinsock();
        int AcceptConnection();
        void CloseControlConnection( void );
        void CloseDataConnection( int hDataSocket );
        void CloseListenSocket();
        int ReadDataMsg( char *szBuffer, int len);
        void GetPassword( char *szPass );
        int GetUnixInput(char *command);
        int GetWin32Input( char *command);
        void GetFile( char *fname);
        void PutFile( char *fname);
        int PutFile( string& fname, string& rfile);    // SLAP over-ride
        int ReadControlMsg( char *szBuffer, int len);
        int CheckControlMsg( char *szPtr, int len);
        int CheckInput();

        enum FTPFLAGS
        {
            LS = 0,
            BINARY,
            ASCII,
            PWD,
            CD,
            OPEN,
            CLOSE,
            QUIT,
            LCD,
            LLS,
            LDIR,
            USER,
            SHELL,
            IGNORE_COMMAND,
            GET,
            PUT,
            HELP,
            RHELP,

            FTP_COMPLETE=1, /* these will be used later */
            FTP_CONTINUE,
            FTP_ERROR
        };

    };
}   // end SlapWare namespace

#endif