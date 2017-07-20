// TnChecker.cpp : Defines the entry point for the console application.
//
#ifdef _DEBUG
#define _RWCONFIG 15s
#else
#define _RWCONFIG 12s
#endif

#include "stdafx.h"
#include <sstream>
#include "CImageGlobals.h"
#include "CImageError.h"

#include "RwFtp.h"
#include <rw/pointer/RWTOnlyPointer.h>
#include "COciHandle.h"
#include <rw/tools/regex.h> // Get access regular expressions

/////////////////////////
// Snowbound Includes  //
/////////////////////////
#ifdef WIN32
	#include "NT_GLUE.h"
#endif
#include "IMGLIB.h"
#include "IMG_ERR.h"
/////////////////////////////////////////
// MilliSeconds to sleep between runs  //
/////////////////////////////////////////
const unsigned int m_sleep_time = 30000;
///////////////////////////////////////
// Static values for SnowBound use.  //
///////////////////////////////////////
const int m_cnvClr = 256;
const int m_fmt_JPEG = 13;
const int m_fmt_TIFF = 9;	// LZW-TIFF
const int m_quality = 75;	// IMGLOW_set_comp_quality value
/////////////////////////////////////////////
// Map Snowbound Format Integer to a Name  //
/////////////////////////////////////////////
char* mapFormatIntegerToName(int format)
{
if (format == TIFF_UNCOMPRESSED)
	return ("TIF"); //"0
else if (format == BMP_UNCOMPRESSED)
	return ("BMP"); //"1
else if (format == PCX)
	return ("PCX"); //"2
else if (format == TARGA)
	return ("TARGA"); //"3
else if (format == GIF)
	return ("GIF"); //"4
else if (format == WPG)
	return ("WPG"); //"5
else if (format == WMF)
	return ("WMF"); //"6
else if (format == TIFF_HUFFMAN)
	return ("TIFF_HUFFMAN"); //"7
else if (format == TIFF_G3_FAX)
	return ("TIFF_G3_FAX"); //"8
else if (format == TIFF_LZW)
	return ("TIFF_LZW"); //"9
else if (format == TIFF_G4_FAX)
	return ("TIFF_G4_FAX"); //"10
else if (format == DCX)
	return ("DCX"); //"11
else if (format == BMP_COMPRESSED)
	return ("BMP_COMPRESSED"); //"12
else if (format == JPEG)
	return ("JPG"); //"13
else if (format == EPS)
	return ("EPS"); //"14
else if (format == PICT)
	return ("PICT"); //"15
else if (format == TIFF_PACK)
	return ("TIFF_PACK"); //"16
else if (format == TIFF_2D)
	return ("TIFF_2D"); //"17
else if (format == CALS)
	return ("CALS"); //"18
else if (format == LASER_DATA)
	return ("LASER_DATA"); //"19
else if (format == XBM)
	return ("XBM"); //"20
else if (format == MACPAINT)
	return ("MACPAINT"); //"21
else if (format == GX2)
	return ("GX2"); //"22
else if (format == KOFAX)
	return ("KOFAX"); //"23
else if (format == IOCA)
	return ("IOCA"); //"24
else if (format == ICONTYPE)
	return ("ICONTYPE"); //"25
else if (format == IFF_ILBM)
	return ("IFF_ILBM"); //"26
else if (format == CLIP)
	return ("CLIP"); //"27
else if (format == IMG)
	return ("IMG"); //"28
else if (format == BROOK_TROUT)
	return ("BROOK_TROUT"); //"29
else if (format == MSP)
	return ("MSP"); //"30
else if (format == CUT)
	return ("CUT"); //"31
else if (format == TARGA16)
	return ("TARGA16"); //"32
else if (format == CCITT_G3)
	return ("CCITT_G3"); //"33
else if (format == CCITT_G4)
	return ("CCITT_G4"); //"34
else if (format == XPM)
	return ("XPM"); //"35
else if (format == XWD)
	return ("XWD"); //"36
else if (format == RAST)
	return ("RAST"); //"37
else if (format == ASCII)
	return ("ASCII"); //"38
else if (format == PHOTOCD)
	return ("PHOTOCD"); //"39
else if (format == TIFF_JPEG)
	return ("TIFF_JPEG"); //"40
else if (format == PHOTOSHOP)
	return ("PHOTOSHOP"); //"41
else if (format == IMNET)
	return ("IMNET"); //"42
else if (format == PNG)
	return ("PNG"); //"43
else if (format == GIF_INTERLACED)
	return ("GIF"); //"44
else if (format == XEROX_EPS)
	return ("XEROX_EPS"); //"45
else if (format == TIFF_ABIC)
	return ("TIFF_ABIC"); //"46
else if (format == TIFF_ABIC_BW)
	return ("TIFF_ABIC_BW"); //"47
else if (format == DIB)
	return ("DIB"); //"48
else if (format == MODCA_IOCA)
	return ("MODCA_IOCA"); //"49
else if (format == TIFF_G4_FAX_FO)
	return ("TIFF_G4_FAX_FO"); //"51
else if (format == CCITT_G4_FO)
	return ("CCITT_G4_FO"); //"52
else if (format == CCITT_G3_FO)
	return ("CCITT_G3_FO"); //"53
else if (format == FLASH_PIX)
	return ("FLASH_PIX"); //"54
else if (format == DICOM)
	return ("DICOM"); //"55
else if (format == JEDMICS)
	return ("JEDMICS"); //"56
else if (format == PCL_1)
	return ("PCL_1"); //"57
else if (format == WINFAX)
	return ("WINFAX"); //"58
else if (format == PDF)
	return ("PDF"); //"59
else if (format == SCITEX)
	return ("SCITEX"); //"60
else if (format == MAG)
	return ("MAG"); //"61
else if (format == DCS)
	return ("DCS"); //"62
else if (format == EPS_BITMAP)
	return ("EPS_BITMAP"); //"63
else if (format == EPS_BITMAP_G4)
	return ("EPS_BITMAP_G4"); //"64
else if (format == NCR)
	return ("NCR"); //"65
else if (format == TIFF_JBIG)
	return ("TIFF_JBIG"); //"66
else if (format == TIFF_G4_FAX_STRIP)
	return ("TIFF_G4_FAX_STRIP"); //"67
else if (format == WBMP)
	return ("WBMP"); //"68
else if (format == EPS_BITMAP_LZW)
	return ("EPS_BITMAP_LZW"); //"69
else if (format == JPEG2000)
	return ("JPEG2000"); //"70
else if (format == JBIG)
	return ("JBIG"); //"71
else if (format == COD)
	return ("COD"); //"72
else
	return (NULL);
}
////////////////////////////
//Test local or production//
////////////////////////////
//#define _SLAP_DBG_LOCAL_ 1;
#define _USE_OCTREE 1;

typedef map<int, RWCString, less<int> > docMap;


void GoWait()
{
	for(int wtime = 0;wtime <= 4; wtime++)
	{
		Sleep(m_sleep_time);
		Sleep(m_sleep_time);
		Sleep(m_sleep_time);
		Sleep(m_sleep_time);
	}
}
using namespace slapware;
////////////////////////////////
// Main program entry point.  //
////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	bool m_verboseLog;
	CImageGlobals m_imgGbl;
	bool isOK = m_imgGbl.Init();
	CImageError m_imgErr(m_imgGbl.GetLog());
	if(!isOK)
	{
		cout << "FATAL : Setting's couldn't not be initialized." << endl;
		return 69;
	}

    if ( argc >= 2 )
    {
        m_verboseLog = true;
		cout << "Verbose mode on...." << endl;
    }
    else
    {
        m_verboseLog = false;
    }

	RWCString m_smallName;
	RWCString m_largeName;
    RWCString m_medLargeName;
	RWCString m_medName;
	RWCString m_fileSave;
	RWCString m_workDir;
	RWCString m_srvok;
	RWCString m_szerror;
	RWCString m_longName;
	RWCString m_realFile;
	RWCString m_fileName;
    string m_thr_error;
	string m_ouser = "prodtele";
	string m_opass = "prodtele";
	RWCString m_isbn;
    RWCString m_assetType;
	long m_record_id;
    int m_reissue;  // reissue number for sale restricted check
	int m_imghandle;
	int m_type;
	int m_res;
	int m_two8;
	bool m_canRun;
    float m_divResult;
    int m_width, m_height, m_bpp;
    int m_newWidth;
	int m_newHeight;
	int	smajor;
	int	sminor;
	char szPath[MAX_PATH];

	RWCString m_upSql, m_sqlData;
	std::ostringstream m_strstrm;
	int m_rec_found;

	smajor = 0;
	sminor = 0;
	::GetCurrentDirectory (sizeof (szPath), szPath);

	RWCString m_user, m_pswd, m_host;
	m_user = m_imgGbl.GetFtpUser().data();
	m_pswd = m_imgGbl.GetFtpPass().data();
	m_host = m_imgGbl.GetFtpHost().data();
	RWTOnlyPointer<CRwFtp> ftp(new CRwFtp(1, 3));
	ftp->Host(m_host);
	ftp->User(m_user);

	ftp->Pswd(m_pswd);
	for (;;)
	{		// LOOP ******************************
#ifdef _DEBUG		
        Sleep(5);
#else
        Sleep(m_sleep_time);
		Sleep(m_sleep_time);
		Sleep(m_sleep_time);
		Sleep(m_sleep_time);
#endif        
        m_canRun = m_imgErr.IsValidTime();	// Check time of day
		if(!m_canRun)
		{
			GoWait();
            continue;
        }
		////////////////////////////////////////////////
		// Smart pointer heap protection local scope  //
		////////////////////////////////////////////////
		RWTOnlyPointer<CCOciHandle> pdb(new CCOciHandle(m_imgGbl.GetTNS().data(), m_ouser.data(), m_opass.data()));
		if(!pdb->GetStatus().isValid() ) // != RWDBStatus::ok)
		{
			m_thr_error = pdb->GetStatus().message();
            if( (m_thr_error.find ( "-01033", 0 ) != string::npos) || (m_thr_error.find ( "-01034", 0 ) != string::npos)
                 || (m_thr_error.find ( "-01089", 0 ) != string::npos) || (m_thr_error.find ( "-03114", 0 ) != string::npos))
			{
                GoWait();	// Long wait as backup running
			}
            else
            {
				m_thr_error = pdb->GetStatus().message();
				m_imgErr.Entry(m_thr_error);
                GoWait();	// or database is otherwise down.
            }
            continue;
		}
#ifndef _SLAP_DBG_LOCAL_		
		///////////////////////////////////////////////
		// Check if any data is present to process.  //
		///////////////////////////////////////////////
		m_strstrm << "select count(*) from " << m_imgGbl.GetDbTable() << " pt, DOC_RENDITIONS dr ";
		m_strstrm << "WHERE pt.RECORD_ID = dr.RECORD_ID AND ";
		m_strstrm << "pt.PUSHED = 'N' AND dr.FILE_LOCATION like ('" << m_imgGbl.GetFileStore() << "%')";
		m_sqlData = m_strstrm.str();
		m_strstrm.str("");
		///////////////////////////////////////
		// Get to work on records available  //
		///////////////////////////////////////
		m_strstrm << "select pt.RECORD_ID, RTRIM(pt.TR005_ISBNEXTENDED) ";
		m_strstrm << "FROM " << m_imgGbl.GetDbTable() << " pt, DOC_RENDITIONS dr ";
		m_strstrm << "WHERE pt.RECORD_ID = dr.RECORD_ID AND ";
		m_strstrm << "pt.PUSHED = 'N' AND ";
		m_strstrm << "dr.FILE_LOCATION like ('" << m_imgGbl.GetFileStore() << "%')";
		//m_strstrm << "dr.FILE_LOCATION like ('" << m_imgGbl.GetFileStore() << "%') AND ";
		//m_strstrm << "rownum < 2";
		m_upSql = m_strstrm.str();
		m_strstrm.str("");
		///////////////////////////////////////////////
		// Check if any data is present to process.  //
		///////////////////////////////////////////////
		int m_records;
		m_records = pdb->GetCount(m_sqlData);
		if(!pdb->GetStatus().isValid())
		{
			m_thr_error = "<Exception type=\"OCI GET COUNT\">";
			m_thr_error += pdb->GetStatus().message();
			m_thr_error += "</Exception>";
			m_imgErr.Entry(m_thr_error);
			if( m_verboseLog )
			{
				cout << "OCI GET COUNT : " << m_szerror << endl;
			}
			continue;
		}
		/////////////////////////////////////////////////////////
		// If data present, make RECORD_ID, ISBN map of data.  //
		/////////////////////////////////////////////////////////
		if( m_records == 0 )
		{
			m_thr_error = "No entries to process.";
			if( m_verboseLog )
			{
				cout << m_thr_error << endl;
			}
			continue;
		}

		if (m_verboseLog)
		{
			cout << "Create the stl map." << endl;
		}
		docMap getMap;
		getMap.clear();
		int tDo = pdb->make_docMap(m_upSql, getMap);
		if( !pdb->GetStatus().isValid() )
		{
			m_thr_error = "<Exception type=\"OCI MAKE MAP\">";
			m_thr_error += pdb->GetStatus().message();
			m_thr_error += "</Exception>";
			m_imgErr.Entry(m_thr_error);
			if( m_verboseLog )
			{
				cout << "OCI MAKE MAP : " << m_szerror << endl;
			}
			continue;
		}
#endif		

	enum m_authMode { None, AUTH, IMPLICIT};

	////////////////////////////////////////////////////////
	//File rename method is decided here from xml setting.//
	////////////////////////////////////////////////////////
	enum m_renameMode { HCSTD, ISBN, ISBNID, ISBNTYPE, ISBNFILE };
	m_renameMode thisRename;
	if (m_imgGbl.GetRename() != 0)
	{
		thisRename = static_cast<m_renameMode>(m_imgGbl.GetRenameMode());
	}
	else
		thisRename = HCSTD;
    ////////////////////////////////////////////////////////////////
    // Build and process the map to convert and send images here. //
    ////////////////////////////////////////////////////////////////
#ifndef _SLAP_DBG_LOCAL_
	if (m_verboseLog)
	{
		cout << "create and use the docMap::iterator" << endl;
	}
		docMap::iterator itr = getMap.begin();
		while( itr != getMap.end() )
		{
			m_record_id = (*itr).first;			  // Get record_id to process
			m_isbn = (*itr).second;				  // Get ISBN to process
			if( (m_record_id == 0) || (m_isbn.length() < 12) )
			{
				itr++;
				continue;
			}

        try {
				m_strstrm << "select rtrim(FILE_LOCATION), rtrim(FILE_NAME) from DOC_RENDITIONS ";
				m_strstrm << "WHERE RECORD_ID = " << m_record_id;
				m_upSql = m_strstrm.str();
				m_strstrm.str("");
				m_rec_found = pdb->GetStrStr(m_upSql, m_longName, m_fileName);
				if( !pdb->GetStatus().isValid() )
				{
					m_thr_error = pdb->GetStatus().message();
					if( (m_thr_error.find ( "-01033", 0 ) != string::npos) || (m_thr_error.find ( "-01034", 0 ) != string::npos)
						|| (m_thr_error.find ( "-01089", 0 ) != string::npos) || (m_thr_error.find ( "-03114", 0 ) != string::npos) )
					{
						GoWait();  // Long wait as backup running
					}
					else
					{
						m_thr_error = "<Exception type=\"DB Unavailable\">";
						m_thr_error += pdb->GetStatus().message();
						m_thr_error += "</Exception>";
						m_imgErr.Entry(m_thr_error);
						GoWait();  // or database is otherwise down.
					}
					getMap.clear();
					itr++;
					continue;
				}	// if (!m_szerror.empty())
				/////////////////////////////////////////////
				// Test for correct file store available.  //
				/////////////////////////////////////////////
				int compret = m_imgGbl.GetFileStore().compare(m_longName.std().substr ( 0 , m_imgGbl.GetFileStore().length() ) );
				if( compret == 0 )	  // is it the correct image server ?
				{
					m_realFile = m_imgGbl.LocateFile(m_longName.std());
					if( m_realFile.isNull() )
					{
						string tmp = "Locate File";
						m_thr_error = "FILENAME-Mapping";
						m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
						// Mark as error in DB
						m_strstrm << "UPDATE " << m_imgGbl.GetDbTable() << " SET PUSHED = 'M' ";
						m_strstrm << "WHERE RECORD_ID = " << m_record_id;
						m_upSql = m_strstrm.str();
						m_strstrm.str("");
						m_rec_found = pdb->Update(m_upSql);
						if( !pdb->GetStatus().isValid() )
						{
							m_thr_error = pdb->GetStatus().message();
							if (m_verboseLog)
							{
								cout << m_thr_error << endl;
							}
							string tmp = "OCI Update DB Error";
							m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
						}	// if (!m_szerror.empty()) 
						m_isbn.remove(0);
						m_longName.remove(0);
						m_record_id = 0;
						itr++;
						continue;
					}
				}
				else
				{
					//////////////////////////////////////
					// Reset vars for validation test.  //
					//////////////////////////////////////
					m_isbn.remove(0);
					m_longName.remove(0);
					m_record_id = 0;
					///////////////////////////////////////////
					// Move up iterator for next map entry.  //
					///////////////////////////////////////////
					itr++;
					continue;
				}
				#else
				m_record_id = 1600832;
				m_isbn = "9780061547843";
				m_realFile = "C:\\KingoftheClub pb c.eps";
	#endif	
			///////////////////////////////////////////////////////////
			// ASSET_TYPE & REISSUE_NUMBER INFORMATION obtained here //
			///////////////////////////////////////////////////////////
			m_strstrm << "select RTRIM(ASSET_TYPE), REISSUE_NUMBER from EDITORIAL ";
			m_strstrm << "WHERE RECORD_ID = " << m_record_id;
			m_upSql = m_strstrm.str();
			m_strstrm.str("");
			/////////////////////////////////////////////////
			// Check if any error occurred in the process. //
			/////////////////////////////////////////////////
			m_assetType.remove(0);
			m_rec_found = pdb->GetStrInt(m_upSql, m_assetType, m_reissue );
			if (!pdb->GetStatus().isValid())
			{
				m_thr_error = "<Exception type=\"GET ASSET_TYPE\">";
				m_thr_error += pdb->GetStatus().message();
				m_thr_error += "</Exception>";
				m_imgErr.Entry(m_thr_error);
				if (m_verboseLog)
				{
					cout << m_thr_error << " Line = " << __LINE__  << endl;
				}
	#ifndef _SLAP_DBG_LOCAL_
				itr++;
	#endif // _SLAP_DBG_LOCAL_
				continue;
			}
//			RWTRegex<char> re("\\| |/|-");
//			RWTRegex<char> asst("Jacket_Cover_Snapshot|Display");
//			re.replace(m_assetType, "_", 0);
			if(m_assetType.contains ( "Cover Snapshot", RWCString::ignoreCase ) )
			{
				m_assetType = "Cover";
				//asst.replace(m_assetType, "Cover", 0);
				//size_t spAt = m_assetType.first(" ");
				//if (spAt != RW_NPOS)
				//{
				//	m_assetType.replace(spAt, 1, "_");
				//}
			}
			if(m_assetType.contains ( "Display", RWCString::ignoreCase ) ) // 01/22/2009 SLAP
			{
				m_assetType = "Cover";
				//asst.replace(m_assetType, "_Cover", 0);
			}
			//////////////////////////////
			// Obtain Input Image Info  //
			//////////////////////////////
			m_type = 0;
			m_type = IMGLOW_get_filetype( (char *)m_realFile.data() );

			if (m_type < 0)
			{
				string tmp = "Get FileType Failed";

				switch(m_type)
				{
				case -1:
					m_strstrm << "OUT OF MEMORY = " << m_type;
					m_thr_error = m_strstrm.str();
					m_strstrm.str("");
					break;
				case -2:
					m_strstrm << "FILE NOT FOUND = " << m_type;
					m_thr_error = m_strstrm.str();
					m_strstrm.str("");
					break;
				case -3:
					m_strstrm << "CORRUPT FILE = " << m_type;
					m_thr_error = m_strstrm.str();
					m_strstrm.str("");
					break;
				default:
					m_strstrm << "IMGLOW_get_filetype = " << m_type;
					m_thr_error = m_strstrm.str();
					m_strstrm.str("");
					break;
				}

				m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
				m_strstrm << "UPDATE " << m_imgGbl.GetDbTable() << " SET PUSHED = 'T' ";
				m_strstrm << "WHERE RECORD_ID = " << m_record_id;
				m_upSql = m_strstrm.str();
				m_strstrm.str("");
				m_rec_found = pdb->Update(m_upSql);
				if (!pdb->GetStatus().isValid())
				{
					m_thr_error = pdb->GetStatus().message();
					string tmp = "UPDATE DB Entry";
					m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
					if (m_verboseLog)
					{
						cout << m_thr_error << " Line = " << __LINE__ << endl;
					}
				}   // if (!m_szerror.empty()) 

				m_isbn.remove(0);
				m_longName.remove(0);
				m_record_id = 0;
				///////////////////////////////////////////
				// Move up iterator for next map entry.  //
				///////////////////////////////////////////
	#ifndef _SLAP_DBG_LOCAL_
				itr++;
	#endif // _SLAP_DBG_LOCAL_
				continue;
			}
			//////////////////////////////////////////////////////////////
			// IF file is not an EPS, perform a DIRECT send with rename.//
			//////////////////////////////////////////////////////////////
	//		if ( (m_type == 4) || (m_type == 13) || (m_type == 43) || (m_type == 59) ) 13 == jpg
			if ( (m_type == 4) || (m_type == 43) || (m_type == 59) )
			{
				std::string m_directName;
				RWCString m_serverPath;

				RWTRegex<char> re("\\| |/|-");
				RWTRegex<char> asst("_Jacket_Cover Snapshot");
				m_strstrm << m_isbn << "_" << m_reissue << "_" << m_assetType << "." << mapFormatIntegerToName(m_type);
				m_directName = m_strstrm.str();
				m_strstrm.str("");
				re.replace(m_directName, "_", 0);
				if(m_directName.find ( "_Jacket_Cover Snapshot", 0 ) != string::npos)
				{
					asst.replace(m_directName, "Cover", 0);
					//boost::replace_all(m_directName, "_Jacket_Cover_Snapshot", "_Cover");
				}

				if (m_imgGbl.GetStepIn())
				{
					m_serverPath = m_imgGbl.GetUserDir().data();
				}

				if (m_imgGbl.GetUseDir())
				{
					m_strstrm << m_isbn << "_" << m_reissue << "/";
					m_workDir = m_strstrm.str();
					m_strstrm.str("");
					m_serverPath += m_workDir.data();
				}

				m_serverPath += m_imgGbl.GetDirectFtp().data();
				m_serverPath += "/";
				m_serverPath += m_directName.data();

				ftp->handleRequest( m_fileSave.std(), m_serverPath, m_verboseLog);

				if(m_imgGbl.GetDeleteRec() != 0)
				{
					m_strstrm << "DELETE from " << m_imgGbl.GetDbTable();
					m_strstrm << " WHERE RECORD_ID = " << m_record_id;
					m_upSql = m_strstrm.str();
					m_strstrm.str("");
					m_rec_found = pdb->Update(m_upSql);
					if (!pdb->GetStatus().isValid())
					{
						m_thr_error = pdb->GetStatus().message();
						string tmp = "OCI DELETE DB Entry";
						m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
						if (m_verboseLog)
						{
							cout << m_thr_error << " Line = " << __LINE__ << endl;
						}
					}   // if (!m_szerror.empty()) 
				}
				//////////////////////////////////////
				// Reset vars for validation test.  //
				//////////////////////////////////////
				m_isbn.remove(0);
				m_longName.remove(0);
				m_record_id = 0;
				///////////////////////////////////////////
				// Move up iterator for next map entry.  //
				///////////////////////////////////////////
	#ifndef _SLAP_DBG_LOCAL_
				itr++;
	#endif // _SLAP_DBG_LOCAL_
				continue;
			}	// *** DIRECT SEND completed ***
			try 
			{ 
				m_imghandle = -1;
				char buff[75];
				/////////////////////////////////////////////////////
				// Read the Cover/Snapshot file into image object  //
				/////////////////////////////////////////////////////
				if(m_realFile.length() < 8)
				{
					string tmp = "FileName Length Check";
					m_thr_error = "FILENAME-invalid";
					m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
					// Mark as error of Length in DB
					m_strstrm << "UPDATE " << m_imgGbl.GetDbTable() << " SET PUSHED = 'L' ";
					m_strstrm << "WHERE RECORD_ID = " << m_record_id;
					m_upSql = m_strstrm.str();
					m_strstrm.str("");
					m_rec_found = pdb->Update(m_upSql);
					if (!pdb->GetStatus().isValid())
					{
					m_thr_error = pdb->GetStatus().message();
					string tmp = "OCI DELETE DB Entry";
					m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
					}   // if (!m_szerror.empty()) 
					m_isbn.remove(0);
					m_longName.remove(0);
					m_record_id = 0;
					///////////////////////////////////////////
					// Move up iterator for next map entry.  //
					///////////////////////////////////////////
	#ifndef _SLAP_DBG_LOCAL_
					itr++;
	#endif // _SLAP_DBG_LOCAL_
					IMG_delete_bitmap(m_imghandle);
					continue;
				}
	///////////////////////////////////////////////////////
	// This is used to observe behavior in production.  //
	///////////////////////////////////////////////////////
				if (m_imghandle >= 0)
				{
					IMG_delete_bitmap(m_imghandle);
					m_imghandle=-1;
				}
				m_imghandle = IMG_decompress_bitmap((char *)m_realFile.data()); //Decompress image page 1
				if (m_imghandle < 0)
				{
					string tmp = "Read Image Failed";
					m_strstrm << "IMG_decompress = " << m_imghandle;
					m_thr_error = m_strstrm.str();
					m_strstrm.str("");
					m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
					// Mark as error Read
					m_strstrm << "UPDATE " << m_imgGbl.GetDbTable() << " SET PUSHED = 'R' ";
					m_strstrm << "WHERE RECORD_ID = " << m_record_id;
					m_upSql = m_strstrm.str();
					m_strstrm.str("");
					m_rec_found = pdb->Update(m_upSql);
					if (!pdb->GetStatus().isValid())
					{
						m_thr_error = pdb->GetStatus().message();
						string tmp = "OCI DELETE DB Entry";
						m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
					}   // if (!m_szerror.empty()) 
					///////////////////////////////////////////
					// Move up iterator for next map entry.  //
					///////////////////////////////////////////
	#ifndef _SLAP_DBG_LOCAL_
					itr++;
	#endif // _SLAP_DBG_LOCAL_
					continue;
				}
			/////////////////////////////////////
			// Get the file information here.  //
			/////////////////////////////////////
			m_height = 0;

			LPBITMAPINFOHEADER inheader = IMG_bitmap_info(m_imghandle, &m_width, &m_height, &m_bpp);

			/////////////////////////////////////////////////////////////////
			// Avoid divide by zero with adding an exception stack frame.  //
			/////////////////////////////////////////////////////////////////
			if ((m_height == 0) || (m_width == 0))
			{
				string tmp = "LPBITMAPINFOHEADER Invalid";
				m_strstrm << "m_height = " << m_height;
				m_strstrm << " m_width = " << m_width;
				m_thr_error = m_strstrm.str();
				m_strstrm.str("");
	
				m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
				// Mark as Height error
				m_strstrm << "UPDATE " << m_imgGbl.GetDbTable() << " SET PUSHED = 'H' ";
				m_strstrm << "WHERE RECORD_ID = " << m_record_id;
				m_upSql = m_strstrm.str();
				m_strstrm.str("");
				m_rec_found = pdb->Update(m_upSql);
				if (!pdb->GetStatus().isValid())
				{
					m_thr_error = pdb->GetStatus().message();
					string tmp = "OCI DELETE DB Entry";
					m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
				}   // if (!m_szerror.empty()) 
				///////////////////////////////////////////
				// Move up iterator for next map entry.  //
				///////////////////////////////////////////
	#ifndef _SLAP_DBG_LOCAL_
					itr++;
	#endif // _SLAP_DBG_LOCAL_
					continue;
				} // if (m_height == 0)

				try
				{
					if (m_height >= m_width)
					{
						m_divResult = static_cast<float>(m_imgGbl.GetLargeHeight()) / static_cast<float>(m_height);
						m_newWidth = static_cast<int>(m_width * m_divResult);
						// Logic to ensure max width ok or adjust to resolve
						if (m_newWidth > static_cast<int>(m_imgGbl.GetLargeWidth()))
						{
							float m_diff = m_imgGbl.GetLargeWidth() / static_cast<float>(m_newWidth);
							m_newWidth = static_cast<int>(m_newWidth * m_diff);
							int fixedHeight = static_cast<int>(m_imgGbl.GetLargeHeight() * m_diff);
							m_res = IMG_create_thumbnail(m_imghandle, m_newWidth, fixedHeight);
						}
						else
							m_res = IMG_create_thumbnail(m_imghandle, m_newWidth, m_imgGbl.GetLargeHeight());
					}
					else
					{
						m_divResult = static_cast<float>(m_imgGbl.GetLargeWidth()) / static_cast<float>(m_width);
						m_newHeight = static_cast<int>(m_height * m_divResult);
						m_res = IMG_create_thumbnail(m_imghandle, m_imgGbl.GetLargeWidth(), m_newHeight);
					}
				}
				catch(...)
				{
					m_thr_error = "Divide by zero";
					string tmp = "Resize Thumbnail";
					m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
	#ifndef _SLAP_DBG_LOCAL_
					itr++;
	#endif // _SLAP_DBG_LOCAL_
					continue;
				}
				//m_res = IMG_create_thumbnail(m_imghandle, m_newWidth, m_imgGbl.GetLargeHeight());
				///////////////////////////////////////////////////////
				// Added test to avoid blank image creation 3_28_05  //
				///////////////////////////////////////////////////////
				if(m_res < 0)
				{
					string tmp = "Resize_thumbnail Failed";
					m_strstrm << "IMG_create_thumbnail = " << m_res;
					m_thr_error = m_strstrm.str();
					m_strstrm.str("");
					m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
					m_strstrm << "UPDATE " << m_imgGbl.GetDbTable() << " SET PUSHED = 'Z' ";
					m_strstrm << "WHERE RECORD_ID = " << m_record_id;
					m_upSql = m_strstrm.str();
					m_strstrm.str("");
					m_rec_found = pdb->Update(m_upSql);
					if (!pdb->GetStatus().isValid())
					{
						m_thr_error = pdb->GetStatus().message();
						string tmp = "OCI DELETE DB Entry";
						m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
					}   // if (!m_szerror.empty()) 
					m_isbn.remove(0);
					m_longName.remove(0);
					m_record_id = 0;
					///////////////////////////////////////////
					// Move up iterator for next map entry.  //
					///////////////////////////////////////////
	#ifndef _SLAP_DBG_LOCAL_
					itr++;
	#endif // _SLAP_DBG_LOCAL_
					continue;
				}   // if(r_res < 0)

	#ifdef _USE_OCTREE
					m_two8 = IMG_octree_color(m_imghandle, 8, NULL, m_cnvClr);
	#else
					IMGLOW_set_comp_quality(m_quality);
					IMGLOW_set_jpg_interleave(1,1);
					m_res = IMG_cmyk_to_rgb(m_imghandle);
					m_two8 = 16;
	#endif
				///////////////////////////////////////////////////////
				// Added test to avoid blank image creation 7_02_08  //
				///////////////////////////////////////////////////////
				if (m_two8 < 8)
				{
					///////////////////////////////////////////////////////////////////////
					//Insert into CMS_PUSH14 to allow SB version 14 to handle this image.//
					///////////////////////////////////////////////////////////////////////
					if( m_imgGbl.GetDbTable().find("14") == string::npos)
					{
						m_strstrm << "INSERT INTO " << m_imgGbl.GetDbTable() << "14 VALUES (" << m_record_id;
						m_strstrm << ", '" << m_assetType << "', '" << m_isbn << "', ";
						m_strstrm << m_reissue << ", 'N')";
						m_upSql = m_strstrm.str();
						m_strstrm.str("");
						m_rec_found = pdb->Update(m_upSql);
						// Disable trigger
						m_strstrm << "alter trigger PRODTELE." << m_imgGbl.GetDbTable() << "_FLAG_DELETE_TRIG disable";
						m_upSql = m_strstrm.str();
						m_strstrm.str("");
						m_rec_found = pdb->Update(m_upSql);
						// Delete record
						m_strstrm << "DELETE from " << m_imgGbl.GetDbTable() << " WHERE RECORD_ID = " << m_record_id;
						m_upSql = m_strstrm.str();
						m_strstrm.str("");
						m_rec_found = pdb->Update(m_upSql);
						//Enable trigger
						m_strstrm << "alter trigger PRODTELE." << m_imgGbl.GetDbTable() << "_FLAG_DELETE_TRIG ENABLE";
						m_upSql = m_strstrm.str();
						m_strstrm.str("");
						m_rec_found = pdb->Update(m_upSql);
						if (!pdb->GetStatus().isValid())
						{
							m_thr_error = pdb->GetStatus().message();
							string tmp = "OCI Update DB Entry";
							m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
						}   // if (!m_szerror.empty()) 
						// Reset vars
						m_isbn.remove(0);
						m_longName.remove(0);
						m_record_id = 0;
	#ifndef _SLAP_DBG_LOCAL_
						itr++;
	#endif // _SLAP_DBG_LOCAL_
						continue;
					}
					else
					{
						m_strstrm << "UPDATE " << m_imgGbl.GetDbTable() << " SET PUSHED = 'E' ";
						m_strstrm << "WHERE RECORD_ID = " << m_record_id;
						m_upSql = m_strstrm.str();
						m_strstrm.str("");
						m_rec_found = pdb->Update(m_upSql);
						if (!pdb->GetStatus().isValid())
						{
							m_thr_error = pdb->GetStatus().message();
							string tmp = "OCI Update DB Entry";
							m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
						}   // if (!m_szerror.empty()) 
						m_isbn.remove(0);
						m_longName.remove(0);
						m_record_id = 0;
	#ifndef _SLAP_DBG_LOCAL_
						itr++;
	#endif // _SLAP_DBG_LOCAL_
						continue;
					}
				} // if (m_two8 < 0)
				//////////////////////////////////////
				// Write the large image to a file  //
				//////////////////////////////////////
				switch( thisRename )
				{
				case HCSTD: // 0
					m_largeName = m_fileName;
					m_strstrm.str("");
					break;

				case ISBN: // 1
					m_strstrm << m_isbn << ".jpg";
					m_largeName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNID: // 2
					m_strstrm << m_isbn << "_" << m_record_id << ".jpg";
					m_largeName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNTYPE: // 3
					m_strstrm << m_isbn << "_" << m_reissue << "_" << m_assetType << ".jpg";
					m_largeName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNFILE: // 4
					m_strstrm << m_isbn << "_" << m_fileName;
					m_largeName = m_strstrm.str();
					m_strstrm.str("");
					break;

				default:	// all other
					m_largeName = m_fileName;
					m_strstrm.str("");
					break;
				}

				m_fileSave = m_imgGbl.GetLocalLarge() + m_largeName;

				if (m_imghandle >= 0)
				{
					int result;
					try
					{
						result = IMG_save_bitmap(m_imghandle, (char *)m_fileSave.data(), m_fmt_JPEG); // 13 = jpeg
					}
					catch (...)
					{
						result = -666;
					}
					if (result < 0)
					{
						wsprintf(buff,"Error Code %d on File Save.", result);
						string tmp = "Save Error";
						m_thr_error = buff;
						m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
						// Mark Save error
						m_strstrm << "UPDATE " << m_imgGbl.GetDbTable() << " SET PUSHED = 'S' ";
						m_strstrm << "WHERE RECORD_ID = " << m_record_id;
						m_upSql = m_strstrm.str();
						m_strstrm.str("");
						m_rec_found = pdb->Update(m_upSql);
						if (!pdb->GetStatus().isValid())
						{
							m_thr_error = pdb->GetStatus().message();
							string tmp = "OCI DELETE DB Entry";
							m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
						}   // if (!m_szerror.empty()) 
						m_isbn.remove(0);
						m_longName.remove(0);
						m_record_id = 0;
						///////////////////////////////////////////
						// Move up iterator for next map entry.  //
						///////////////////////////////////////////
	#ifndef _SLAP_DBG_LOCAL_
						itr++;
	#endif // _SLAP_DBG_LOCAL_
						IMG_delete_bitmap(m_imghandle);
						continue;
					}
					else
					{
						RWCString m_serverPath;
						if (m_imgGbl.GetStepIn())
						{
							m_serverPath = m_imgGbl.GetUserDir().data();
							m_serverPath += "/";
						}

						if (m_imgGbl.GetUseDir())
						{
							m_strstrm << m_isbn << "_" << m_reissue << "/";
							m_workDir += m_strstrm.str();
							m_strstrm.str("");
							m_serverPath += m_workDir.data();
						}

						if (m_imgGbl.GetSizeSort())
						{
							m_serverPath += m_imgGbl.GetLargeFtp().data();
							m_serverPath += "/";
							m_serverPath += m_largeName.data();
						}
						ftp->handleRequest( m_fileSave.std(), m_serverPath, m_verboseLog);
					}
				}
				IMG_delete_bitmap(m_imghandle);
	//-----------------------------------VeryLarge--------------------------------------------
				m_imghandle=-1;

				m_imghandle = IMG_decompress_bitmap((char *)m_realFile.data()); //Decompress image page 1
				if (m_imghandle < 0)
				{
					///////////////////////////////////////////
					// Move up iterator for next map entry.  //
					///////////////////////////////////////////
#ifndef _SLAP_DBG_LOCAL_
					itr++;
#endif // _SLAP_DBG_LOCAL_
					continue;
				}

				//////////////////////////////////////
				// Changed to calc size 07/10/2008  //
				//////////////////////////////////////
				if (m_height >= m_width)
				{
					m_divResult = static_cast<float>(m_imgGbl.GetvLargeHeight()) / static_cast<float>(m_height);
					m_newWidth = static_cast<int>(m_width * m_divResult);
					if (m_newWidth > static_cast<int>(m_imgGbl.GetvLargeWidth()))
					{
						float m_diff = m_imgGbl.GetvLargeWidth() / static_cast<float>(m_newWidth);
						m_newWidth = static_cast<int>(m_newWidth * m_diff);
						int fixedHeight = static_cast<int>(m_imgGbl.GetvLargeHeight() * m_diff);
						m_res = IMG_create_thumbnail(m_imghandle, m_newWidth, fixedHeight);
					}
					else
						m_res = IMG_create_thumbnail(m_imghandle, m_newWidth, m_imgGbl.GetvLargeHeight());
				}
				else
				{
					m_divResult = static_cast<float>(m_imgGbl.GetvLargeWidth()) / static_cast<float>(m_width);
					m_newHeight = static_cast<int>(m_height * m_divResult);
					m_res = IMG_create_thumbnail(m_imghandle, m_imgGbl.GetvLargeWidth(), m_newHeight);
				}
				///////////////////////////
				// Create the Thumbnail  //
				///////////////////////////
				if (m_res < 0)
				{
					string tmp = "IMG_create_thumbnail Failed";
					m_strstrm << "Result = " << m_res;
					m_thr_error = m_strstrm.str();
					m_strstrm.str("");
					m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
				}

				m_two8 = IMG_octree_color(m_imghandle, 8, NULL, m_cnvClr);
				if (m_two8 < 0)
				{
					string tmp = "IMG_octree_color Failed";
					m_strstrm << "Palette Adjust 256 = " << m_two8;
					m_thr_error = m_strstrm.str();
					m_strstrm.str("");
					m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
				}

				IMGLOW_set_comp_quality(m_quality);   // 100 max
				IMGLOW_set_jpg_interleave(1,1);
				m_res = IMG_cmyk_to_rgb(m_imghandle);
				/////////////////////////////////////////
				// Write the medLarge image to a file  //
				/////////////////////////////////////////
				RWCString m_vLargeName;
				switch( thisRename )
				{
				case HCSTD: // 0
					m_vLargeName = m_fileName;
					m_strstrm.str("");
					break;

				case ISBN: // 1
					m_strstrm << m_isbn << ".jpg";
					m_vLargeName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNID: // 2
					m_strstrm << m_isbn << "_" << m_reissue << ".jpg";
					m_vLargeName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNTYPE: // 3
					m_strstrm << m_isbn << "_" << m_reissue << "_" << m_assetType << ".jpg";
					m_vLargeName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNFILE: // 4
					m_strstrm << m_isbn << "_" << m_fileName;
					m_vLargeName = m_strstrm.str();
					m_strstrm.str("");
					break;

				default:	// all other
					m_vLargeName = m_fileName;
					m_strstrm.str("");
					break;
				}

				m_fileSave = m_imgGbl.GetvLocalLarge() + m_vLargeName;
				if (m_verboseLog)
				{
					cout << "Very Large local save to " << m_fileSave << endl;
				}

				if (m_imghandle >= 0)
				{
					m_res = IMG_save_bitmap(m_imghandle, (char *)m_fileSave.data(), m_fmt_JPEG); // 13 = jpeg
					if (m_res < 0)
					{
						if (m_verboseLog)
						{
							cout <<"vLarge save error." << endl;
						}
						wsprintf(buff,"Error Code %d on Save.", m_res);
						string tmp = "Save Error";
						m_thr_error = buff;
						m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());

						m_isbn.remove(0);
						m_longName.remove(0);
						m_record_id = 0;
						///////////////////////////////////////////
						// Move up iterator for next map entry.  //
						///////////////////////////////////////////
#ifndef _SLAP_DBG_LOCAL_
						itr++;
#endif // _SLAP_DBG_LOCAL_
						IMG_delete_bitmap(m_imghandle);
						continue;
					}
					else
					{
						RWCString m_serverPath;
						if (m_imgGbl.GetStepIn())
						{
							m_serverPath = m_imgGbl.GetUserDir().c_str();
							m_serverPath += "/";
						}

						if (m_imgGbl.GetUseDir())
						{
							m_strstrm << m_isbn << "_" << m_reissue << "/";
							m_workDir = m_strstrm.str();
							m_strstrm.str("");
							m_serverPath += m_workDir.data();
						}

						if (m_imgGbl.GetSizeSort())
						{
							m_serverPath += m_imgGbl.GetvLargeFtp().c_str();
							m_serverPath += "/";
							m_serverPath += m_vLargeName.data();
						}
						if (m_verboseLog)
						{
							cout << "Sending " << m_fileSave << " To " << m_serverPath << endl;
						}

						ftp->handleRequest( m_fileSave.std(), m_serverPath, m_verboseLog);
					}
				}
				IMG_delete_bitmap(m_imghandle);
	//-----------------------------------MedLarge--------------------------------------------
				m_imghandle=-1;

				m_imghandle = IMG_decompress_bitmap((char *)m_realFile.data()); //Decompress image page 1
				if (m_imghandle < 0)
				{
					///////////////////////////////////////////
					// Move up iterator for next map entry.  //
					///////////////////////////////////////////
	#ifndef _SLAP_DBG_LOCAL_
					itr++;
	#endif // _SLAP_DBG_LOCAL_
					continue;
				}

				//////////////////////////////////////
				// Changed to calc size 07/10/2008  //
				//////////////////////////////////////
				if (m_height >= m_width)
				{
					m_divResult = static_cast<float>(m_imgGbl.GetMedLargeHeight()) / static_cast<float>(m_height);
					m_newWidth = static_cast<int>(m_width * m_divResult);
					if (m_newWidth > static_cast<int>(m_imgGbl.GetMedLargeWidth()))
					{
						float m_diff = m_imgGbl.GetMedLargeWidth() / static_cast<float>(m_newWidth);
						m_newWidth = static_cast<int>(m_newWidth * m_diff);
						int fixedHeight = static_cast<int>(m_imgGbl.GetMedLargeHeight() * m_diff);
						m_res = IMG_create_thumbnail(m_imghandle, m_newWidth, fixedHeight);
					}
					else
						m_res = IMG_create_thumbnail(m_imghandle, m_newWidth, m_imgGbl.GetMedLargeHeight());
				}
				else
				{
					m_divResult = static_cast<float>(m_imgGbl.GetMedLargeWidth()) / static_cast<float>(m_width);
					m_newHeight = static_cast<int>(m_height * m_divResult);
					m_res = IMG_create_thumbnail(m_imghandle, m_imgGbl.GetMedLargeWidth(), m_newHeight);
				}
				///////////////////////////
				// Create the Thumbnail  //
				///////////////////////////
				if (m_res < 0)
				{
					string tmp = "IMG_create_thumbnail Failed";
					m_strstrm << "Result = " << m_res;
					m_thr_error = m_strstrm.str();
					m_strstrm.str("");
					m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
				}

				m_two8 = IMG_octree_color(m_imghandle, 8, NULL, m_cnvClr);
				if (m_two8 < 0)
				{
					string tmp = "IMG_octree_color Failed";
					m_strstrm << "Palette Adjust 256 = " << m_two8;
					m_thr_error = m_strstrm.str();
					m_strstrm.str("");
					m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
				}

				IMGLOW_set_comp_quality(m_quality);   // 100 max
				IMGLOW_set_jpg_interleave(1,1);
				m_res = IMG_cmyk_to_rgb(m_imghandle);
				/////////////////////////////////////////
				// Write the medLarge image to a file  //
				/////////////////////////////////////////
				switch( thisRename )
				{
				case HCSTD: // 0
					m_medLargeName = m_fileName;
					m_strstrm.str("");
					break;

				case ISBN: // 1
					m_strstrm << m_isbn << ".jpg";
					m_medLargeName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNID: // 2
					m_strstrm << m_isbn << "_" << m_reissue << ".jpg";
					m_medLargeName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNTYPE: // 3
					m_strstrm << m_isbn << "_" << m_reissue << "_" << m_assetType << ".jpg";
					m_medLargeName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNFILE: // 4
					m_strstrm << m_isbn << "_" << m_fileName;
					m_medLargeName = m_strstrm.str();
					m_strstrm.str("");
					break;

				default:	// all other
					m_medLargeName = m_fileName;
					m_strstrm.str("");
					break;
				}

				m_fileSave = m_imgGbl.GetMedLargeLocal() + m_medLargeName;

				if (m_imghandle >= 0)
				{
				m_res = IMG_save_bitmap(m_imghandle, (char *)m_fileSave.data(), m_fmt_JPEG); // 13 = jpeg
					if (m_res < 0)
					{
						wsprintf(buff,"Error Code %d on Save.", m_res);
						string tmp = "Save Error";
						m_thr_error = buff;
						m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());

						m_isbn.remove(0);
						m_longName.remove(0);
						m_record_id = 0;
						///////////////////////////////////////////
						// Move up iterator for next map entry.  //
						///////////////////////////////////////////
	#ifndef _SLAP_DBG_LOCAL_
						itr++;
	#endif // _SLAP_DBG_LOCAL_
						IMG_delete_bitmap(m_imghandle);
						continue;
					}
					else
					{
						RWCString m_serverPath;
						if (m_imgGbl.GetStepIn())
						{
							m_serverPath = m_imgGbl.GetUserDir().data();
							m_serverPath += "/";
						}

						if (m_imgGbl.GetUseDir())
						{
							m_strstrm << m_isbn << "_" << m_reissue << "/";
							m_workDir = m_strstrm.str();
							m_strstrm.str("");
							m_serverPath += m_workDir.data();
						}

						if (m_imgGbl.GetSizeSort())
						{
							m_serverPath += m_imgGbl.GetMedLargeFtp().data();
							m_serverPath += "/";
							m_serverPath += m_medLargeName.data();
						}

						ftp->handleRequest( m_fileSave.std(), m_serverPath, m_verboseLog);
					}
				}
				IMG_delete_bitmap(m_imghandle);
	//-----------------------------------Med--------------------------------------------
				m_imghandle=-1;

				if (m_imghandle >= 0)
				{
					IMG_delete_bitmap(m_imghandle);
					m_imghandle=-1;
				}

				m_imghandle = IMG_decompress_bitmap((char *)m_realFile.data()); //Decompress image page 1
				if (m_imghandle < 0)
				{
					///////////////////////////////////////////
					// Move up iterator for next map entry.  //
					///////////////////////////////////////////
	#ifndef _SLAP_DBG_LOCAL_
					itr++;
	#endif // _SLAP_DBG_LOCAL_
					continue;
				}

				if (m_height >= m_width)
				{
					m_divResult = static_cast<float>(m_imgGbl.GetMedHeight()) / static_cast<float>(m_height);
					m_newWidth = static_cast<int>(m_width * m_divResult);
					if (m_newWidth > static_cast<int>(m_imgGbl.GetMedWidth()))
					{
						float m_diff = m_imgGbl.GetMedWidth() / static_cast<float>(m_newWidth);
						m_newWidth = static_cast<int>(m_newWidth * m_diff);
						int fixedHeight = static_cast<int>(m_imgGbl.GetMedHeight() * m_diff);
						m_res = IMG_create_thumbnail(m_imghandle, m_newWidth, fixedHeight);
					}
					else
						m_res = IMG_create_thumbnail(m_imghandle, m_newWidth, m_imgGbl.GetMedHeight());
				}
				else
				{
					m_divResult = static_cast<float>(m_imgGbl.GetMedWidth()) / static_cast<float>(m_width);
					m_newHeight = static_cast<int>(m_height * m_divResult);
					m_res = IMG_create_thumbnail(m_imghandle, m_imgGbl.GetMedWidth(), m_newHeight);
				}

				m_two8 = IMG_octree_color(m_imghandle, 8, NULL, m_cnvClr);
				IMGLOW_set_comp_quality(m_quality);   // 100 max
				IMGLOW_set_jpg_interleave(1,1);
				m_res = IMG_cmyk_to_rgb(m_imghandle);
				//////////////////////////////////////
				// Write the medium image to a file //
				//////////////////////////////////////
				switch( thisRename )
				{
				case HCSTD: // 0
					m_medName = m_fileName;
					m_strstrm.str("");
					break;

				case ISBN: // 1
					m_strstrm << m_isbn << ".jpg";
					m_medName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNID: // 2
					m_strstrm << m_isbn << "_" << m_record_id << ".jpg";
					m_medName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNTYPE: // 3
					m_strstrm << m_isbn << "_" << m_reissue << "_" << m_assetType << ".jpg";
					m_medName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNFILE: // 4
					m_strstrm << m_isbn << "_" << m_fileName;
					m_medName = m_strstrm.str();
					m_strstrm.str("");
					break;

				default:	// all other
					m_medName = m_fileName;
					m_strstrm.str("");
					break;
				}

				m_fileSave = m_imgGbl.GetMedLocal() + m_medName;

				if (m_imghandle >= 0)
				{
				m_res = IMG_save_bitmap(m_imghandle, (char *)m_fileSave.data(), m_fmt_JPEG); // 13 = jpeg
					if (m_res < 0)
					{
						wsprintf(buff,"Error Code %d on Save.", m_res);
						string tmp = "Save Error";
						m_thr_error = buff;
						m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());

						m_isbn.remove(0);
						m_longName.remove(0);
						m_record_id = 0;
						///////////////////////////////////////////
						// Move up iterator for next map entry.  //
						///////////////////////////////////////////
	#ifndef _SLAP_DBG_LOCAL_
						itr++;
	#endif // _SLAP_DBG_LOCAL_
						IMG_delete_bitmap(m_imghandle);
						continue;
					}
					else
					{
						RWCString m_serverPath;
						if (m_imgGbl.GetStepIn())
						{
							m_serverPath = m_imgGbl.GetUserDir().data();
							m_serverPath += "/";
						}

						if (m_imgGbl.GetUseDir())
						{
							m_strstrm << m_isbn << "_" << m_reissue << "/";
							m_workDir = m_strstrm.str();
							m_strstrm.str("");
							m_serverPath += m_workDir.data();
						}

						if (m_imgGbl.GetSizeSort())
						{
							m_serverPath += m_imgGbl.GetMedFtp().data();
							m_serverPath += "/";
							m_serverPath += m_medName.data();
						}

						ftp->handleRequest( m_fileSave.std(), m_serverPath, m_verboseLog);
					}
				}
				IMG_delete_bitmap(m_imghandle);
	//-----------------------------------Small---------------------------------------------
				m_imghandle=-1;

				m_imghandle = IMG_decompress_bitmap((char *)m_realFile.data()); //Decompress image page 1
				if (m_imghandle < 0)
				{
					///////////////////////////////////////////
					// Move up iterator for next map entry.  //
					///////////////////////////////////////////
					IMG_delete_bitmap(m_imghandle);
					m_imghandle=-1;
	#ifndef _SLAP_DBG_LOCAL_
					itr++;
	#endif // _SLAP_DBG_LOCAL_
					continue;
				}

				if (m_height >= m_width)
				{
					m_divResult = static_cast<float>(m_imgGbl.GetSmallHeight()) / static_cast<float>(m_height);
					m_newWidth = static_cast<int>(m_width * m_divResult);
					if (m_newWidth > static_cast<int>(m_imgGbl.GetSmallWidth()))
					{
						float m_diff = m_imgGbl.GetSmallWidth() / static_cast<float>(m_newWidth);
						m_newWidth = static_cast<int>(m_newWidth * m_diff);
						int fixedHeight = static_cast<int>(m_imgGbl.GetSmallHeight() * m_diff);
						m_res = IMG_create_thumbnail(m_imghandle, m_newWidth, fixedHeight);
					}
					else
						m_res = IMG_create_thumbnail(m_imghandle, m_newWidth, m_imgGbl.GetSmallHeight());
				}
				else
				{
					m_divResult = static_cast<float>(m_imgGbl.GetSmallWidth()) / static_cast<float>(m_width);
					m_newHeight = static_cast<int>(m_height * m_divResult);
					m_res = IMG_create_thumbnail(m_imghandle, m_imgGbl.GetSmallWidth(), m_newHeight);
				}

				IMGLOW_set_comp_quality(m_quality);
				IMGLOW_set_jpg_interleave(1,1);
				m_res = IMG_cmyk_to_rgb(m_imghandle);
				//////////////////////////////////////
				// Write the large image to a file  //
				//////////////////////////////////////
				switch( thisRename )
				{
				case HCSTD: // 0
					m_smallName = m_fileName;
					m_strstrm.str("");
					break;

				case ISBN: // 1
					m_strstrm << m_isbn << ".jpg";
					m_smallName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNID: // 2
					m_strstrm << m_isbn << "_" << m_record_id << ".jpg";
					m_smallName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNTYPE: // 3
					m_strstrm << m_isbn << "_" << m_reissue << "_" << m_assetType << ".jpg";
					m_smallName = m_strstrm.str();
					m_strstrm.str("");
					break;

				case ISBNFILE: // 4
					m_strstrm << m_isbn << "_" << m_fileName;
					m_smallName = m_strstrm.str();
					m_strstrm.str("");
					break;

				default:	// all other
					m_smallName = m_fileName;
					m_strstrm.str("");
					break;
				}

				m_fileSave = m_imgGbl.GetLocalSmall() + m_smallName;

				if (m_imghandle >= 0)
				{
				m_res = IMG_save_bitmap(m_imghandle, (char *)m_fileSave.data(), m_fmt_JPEG); // 13 = jpeg
					if (m_res < 0)
					{
						wsprintf(buff,"Error Code %d on Save.",m_res);
						string tmp = "Save Error";
						m_thr_error = buff;
						m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());

						m_isbn.remove(0);
						m_longName.remove(0);
						m_record_id = 0;
						///////////////////////////////////////////
						// Move up iterator for next map entry.  //
						///////////////////////////////////////////
	#ifndef _SLAP_DBG_LOCAL_
						itr++;
	#endif // _SLAP_DBG_LOCAL_
						IMG_delete_bitmap(m_imghandle);
						continue;
					}
					else
					{
						RWCString m_serverPath;
						if (m_imgGbl.GetStepIn())
						{
							m_serverPath = m_imgGbl.GetUserDir().data();
							m_serverPath += "/";
						}

						if (m_imgGbl.GetUseDir())
						{
							m_strstrm << m_isbn << "_" << m_reissue << "/";
							m_workDir = m_strstrm.str();
							m_strstrm.str("");
							m_serverPath += m_workDir.data();
						}

						if (m_imgGbl.GetSizeSort())
						{
							m_serverPath += m_imgGbl.GetSmallFtp().data();
							m_serverPath += "/";
							m_serverPath += m_smallName.data();
						}

						ftp->handleRequest( m_fileSave.std(), m_serverPath, m_verboseLog);
					}
				}
				IMG_delete_bitmap(m_imghandle);
			} // main generation try
			catch( ... ) 
			{ 
				IMG_delete_bitmap(m_imghandle);
				string tmp = "Image Conversion";
				m_thr_error = "CAUGHT UNKNOWN ERROR";
				m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
			} 
	/////////////////////////////////////////////////////////////
	// Here is the ideal place to do any required logging and  //
	// delete the database record to prevent re-processing.    //
	/////////////////////////////////////////////////////////////
			if(m_imgGbl.GetDeleteRec() != 0)
			{
				m_strstrm << "DELETE from " << m_imgGbl.GetDbTable();
				m_strstrm << " WHERE RECORD_ID = " << m_record_id;
				m_upSql = m_strstrm.str();
				m_strstrm.str("");
				m_rec_found = pdb->Update(m_upSql);
				if (!pdb->GetStatus().isValid())
				{
				 m_thr_error = pdb->GetStatus().message();
				 string tmp = "OCI DELETE DB Entry";
				 m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
				}   // if (!m_szerror.empty()) 
			}
        } 
        catch (const RWxmsg& msg)
        {
            m_thr_error = msg.why();
            string tmp = "RW catch";
            m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
            if (m_verboseLog)
            {
                cout << "Error : " << msg.why() << endl;
            }
            itr++;
            continue;
        }
        catch (...)
        {
            m_thr_error = "Unexpected Exception ...";
            string tmp = "RW catch";
            m_imgErr.Entry(tmp, m_thr_error, m_realFile.std(), m_longName.std(), m_record_id, m_isbn.std());
            if (m_verboseLog)
            {
                cout << "Error: Unexpected exception." << endl;
            }
            itr++;
            continue;
        }
        //////////////////////////////////////
        // Reset vars for validation test.  //
        //////////////////////////////////////
        m_isbn.remove(0);
		m_assetType.remove(0);
        m_longName.remove(0);
        m_record_id = 0;
        ///////////////////////////////////////////
        // Move up iterator for next map entry.  //
        ///////////////////////////////////////////
#ifndef _SLAP_DBG_LOCAL_		
		itr++;
	}	// while (itr != pdb->docMap.end() )
#endif		
    /////////////////////////////////////////////////////////////
    // End the process of map to convert and send images here. //
    /////////////////////////////////////////////////////////////
		if( m_verboseLog )
		{
			cout << "About to delete pdb ****** ->" << endl;
		}
		delete pdb;	// created on heap before thumbnail loop
		if( m_verboseLog )
		{
			cout << "Bottom LOOP ****** ->" << endl;
		}
    }		// LOOP ******************************
	return 0; // Never reached.
}

