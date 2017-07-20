//-----------------------------------MedLarge--------------------------------------------
			imghandle=-1;

			imghandle = IMG_decompress_bitmap_page((char *)m_realFile.c_str(), 0); //Decompress image page 1
			if (imghandle < 0)
			{
				///////////////////////////////////////////
				// Move up iterator for next map entry.  //
				///////////////////////////////////////////
				itr++;
				continue;
			}

            if (imgGbl.GetImgFormat() == "JPEG") 
            {
                if (m_height > m_width)
                {
                    m_divResult = static_cast<float>(imgGbl.GetMedLargeHeight()) / static_cast<float>(m_height);
                    m_newWidth = static_cast<int>(m_width * m_divResult);
                    r_res = IMG_create_thumbnail(imghandle, m_newWidth, imgGbl.GetMedLargeHeight());
                }
                else
                {
                    m_divResult = static_cast<float>(imgGbl.GetMedLargeWidth()) / static_cast<float>(m_width);
                    m_newHeight = static_cast<int>(m_height * m_divResult);
                    r_res = IMG_create_thumbnail(imghandle, imgGbl.GetMedLargeWidth(), m_newHeight);
                }

                IMGLOW_set_comp_quality(m_quality);   // 100 max
                IMGLOW_set_jpg_interleave(1,1);
                r_res = IMG_cmyk_to_rgb(imghandle);
            }

            if (imgGbl.GetImgFormat() == "GIF") 
            {
                r_res = IMG_resize_bitmap_bicubic(imghandle, imgGbl.GetMedLargeWidth(), imgGbl.GetMedLargeHeight());
            }

            //////////////////////////////////////
            // Write the large image to a file  //
            //////////////////////////////////////
			m_medLargeName = imgGbl.GetMedLargeLocal();
			m_medLargeName += m_isbn13;
			m_medLargeName += ".";
			m_medLargeName += imgGbl.GetImgFormat().c_str();
			if (imghandle >= 0)
			{
			 r_res = IMG_save_bitmap(imghandle, (char *)m_medLargeName.c_str(), m_fmt_JPEG); // 13 = jpeg
				if (r_res < 0)
				{
					wsprintf(buff,"Error Code %d on Save.", r_res);
					string tmp = "Save Error";
					m_thr_error = buff;
					imgErr.Entry(tmp, m_thr_error, m_realFile, m_longName, m_record_id, m_isbn13);

					m_isbn.clear();
                    m_isbn13.clear();
					m_longName.clear();
					m_record_id = 0;
					///////////////////////////////////////////
					// Move up iterator for next map entry.  //
					///////////////////////////////////////////
					itr++;
					IMG_delete_bitmap(imghandle);
					continue;
				}
                else
                {
                    if ( imgGbl.GetUseFTP() )
                    {
                        string m_loc = imgGbl.GetMedLargeFtp();
                        string tmpName = m_isbn13;
                        tmpName += ".";
                        tmpName += imgGbl.GetImgFormat().c_str();
                        /*****************************************************
                        * Do we need to que FTP as FTP down but requested ?  *
                        *****************************************************/
						if(m_queFtp)
						{
							// que FTP
							queFile qf(tmpName, m_loc, m_medLargeName);
							const_cast<queList&>(currentQue).append(qf);
						}
                        else
                        {
                            m_ftpRes = ftpConnection->DoCD(m_loc);
                            if (m_ftpRes >= 300)
                            {
                                strstrm << "FTP Error code : " << m_ftpRes;
                                m_thr_error = strstrm.str();
                                strstrm.str("");
                                imgErr.Entry("FTP CD ERROR", m_thr_error);
                                m_queFtp = true;
                                // que FTP
                                queFile qf(tmpName, m_loc, m_medLargeName);
                                const_cast<queList&>(currentQue).append(qf);
                            }
                            m_ftpRes = ftpConnection->DoPut(m_medLargeName, tmpName );
                            if (m_ftpRes >= 300)
                            {
                                strstrm << "FTP Error code : " << m_ftpRes;
                                m_thr_error = strstrm.str();
                                strstrm.str("");
                                imgErr.Entry("FTP PUT ERROR", m_thr_error);
                                m_queFtp = true;
                                // que FTP
                                queFile qf(tmpName, m_loc, m_medLargeName);
                                const_cast<queList&>(currentQue).append(qf);
                            }
                            m_loc = "..";
                            ftpConnection->DoCD(m_loc);
                        }
                    }
                }
			}
			IMG_delete_bitmap(imghandle);
