#include <opencv2/dnn/dnn_serialization.h>
namespace cv {
    namespace dnn{
        CV__DNN_INLINE_NS_BEGIN
            //namespace dnn_serialization {

            void DnnReader::io(unsigned char * a1)
            {
                m_pDR_istream->read(reinterpret_cast<char *>(a1), sizeof(unsigned char));
            }

            void DnnReader::io(unsigned int * a1)
            {
                m_pDR_istream->read(reinterpret_cast<char *>(a1), sizeof(unsigned int));
            }

            void DnnReader::io(int * a1)
            {
                m_pDR_istream->read(reinterpret_cast<char *>(a1), sizeof(int));
            }

            void DnnReader::io(float * a1)
            {
                m_pDR_istream->read(reinterpret_cast<char *>(a1), sizeof(float));
            }

            void DnnReader::io(double * a1)
            {
                m_pDR_istream->read(reinterpret_cast<char *>(a1), sizeof(double));
            }

            void DnnReader::io(unsigned char * pbData, uint nSize)
            {
                if (nSize)
                    m_pDR_istream->read(reinterpret_cast<char *>(pbData), nSize);
            }

            void DnnReader::io(Size * a1)
            {
                m_pDR_istream->read(reinterpret_cast<char *>(a1), sizeof(Size));
            }

            int DnnReader::getPos()
            {
                streamoff pos = m_pDR_istream->tellg();
                return pos;
            }

            void DnnReader::gotoPos(uint a1)
            {
                m_pDR_istream->seekg(a1);
            }

            //////////////////////////
            void io(DnnReader & a1, String & a2)
            {
                basic_string<char> bs10;
                int n4 = bs10.length();
                a1.io(&n4);
                uchar* p6 = new uchar[n4];
                a1.io(p6, n4);
                bs10.insert(bs10.begin(), p6, p6 + n4);
                delete p6;
                a2 = bs10;
            }

            void io(DnnReader & a1, Mat & a2)
            {
                int n13 = a2.dims;
                a1.io(&n13);
                cv::MatSize ms12 = a2.size;
                io(a1, ms12);
                int n11 = a2.flags & 0xFFF;
                a1.io(&n11);
                int n10 = a2.elemSize1();  //(0x48442211 >> ((4 * a2.flags) & 0x1C)) & 0xF
                a1.io(&n10);
                //Mat v15(n13, ms12.p, n11);
                //a2 = v15;

                a2 = cv::Mat(n13, ms12.p, n11);


                if (n11 == 5)
                {
                    float r8, r9;
                    cv::Mat m1a = a2.reshape(1, ms12.p[0]);
                    a1.io(&r9);
                    a1.io(&r8);
                    cv::Mat m14;
                    io(a1, m14);
                    m14.convertTo(m1a, 5, (r8 - r9) / 255.0f, r9);
                }
                else
                {
                    int n5 = a2.total();
                    a1.io(a2.data, n10 * n5);
                }
                delete[](ms12.p - 1);
            }

            void io(DnnReader & a1, MatSize & a2)
            {
                int n10 = *(a2.p - 1);
                a1.io(&n10);
                int * p7 = new int[n10 + 1];
                *p7 = n10;
                a2.p = p7 + 1;
                vector<int> v1;
                io_vec_int(a1, v1);
                memcpy(a2.p, v1.data(), 4 * n10);
            }

            void io_vec_int(DnnReader & a1, vector<int> & a2)
            {
                int n8 = a2.size();
                a1.io(&n8);
                if (n8 != a2.size())
                {
                    a2.resize(n8);
                }

                for (size_t i = 0; i < n8; i++)
                {
                    a1.io(&a2[i]);
                }
            }

			void io_vec_uint(DnnReader & a1, vector<uint>& a2)
			{
                int n8 = a2.size();
                a1.io(&n8);
                if (n8 != a2.size())
                {
                    a2.resize(n8);
                }

                for (size_t i = 0; i < n8; i++)
                {
                    a1.io(&a2[i]);
                }
			}

			CV_EXPORTS_W_SIMPLE void io_vec_vec_uint(DnnReader & a1, vector<vector<uint>>& a2)
			{
                uint nSize = a2.size();
                a1.io(&nSize);
                if (nSize != a2.size())
                    a2.resize(nSize);
                for (int i = 0; i < nSize; i++)
                {
                    io_vec_uint(a1, a2[i]);
                }
			}

            void io(DnnReader & a1, vector<Mat> & a2)
            {
                int n8 = a2.size();
                a1.io(&n8);
                if (n8 != a2.size())
                {
                    a2.resize(n8);
                }

                for (size_t i = 0; i < n8; i++)
                {
                    io(a1, a2[i]);
                }
            }

            void io_vec_String(DnnReader & a1, vector<String> & a2)
            {
                int n8 = a2.size();
                a1.io(&n8);
                if (n8 != a2.size())
                {
                    a2.resize(n8);
                }

                for (size_t i = 0; i < n8; i++)
                {
                    io(a1, a2[i]);
                }
            }

            void io(DnnReader & a1, vector<double> & a2)
            {
                int n8 = a2.size();
                a1.io(&n8);
                if (n8 != a2.size())
                {
                    a2.resize(n8);
                }

                for (size_t i = 0; i < n8; i++)
                {
                    a1.io(&a2[i]);
                }
            }

            void io_map_String_int(DnnReader & a1, map<String, int> & a2)
            {
                int n2a = a2.size();
                a1.io(&n2a);

                for (size_t i = 0; i < n2a; i++)
                {
                    int v7;
                    String v8;
                    io(a1, v8);
                    a1.io(&v7);
                    a2[v8] = v7;
                }
            }

            void io_set_int(DnnReader & a1, set<int> & a2)
            {
                int n7 = a2.size();
                a1.io(&n7);

                for (size_t i = 0; i < n7; i++)
                {
                    int v6;
                    a1.io(&v6);
                    a2.insert(v6);
                }
            }

            void io_set_uint(DnnReader & a1, set<uint> & a2)
            {
                int n7 = a2.size();
                a1.io(&n7);

                for (size_t i = 0; i < n7; i++)
                {
                    uint v6;
                    a1.io(&v6);
                    a2.insert(v6);
                }
            }

            void io(DnnReader &a1, unordered_map<uint, uint> & a2)
            {
                int nSize;
                nSize = a2.size();

                a1.io(&nSize);
                for (int i = 0; i < nSize; ++i)
                {
                    uint v1, v2;
                    a1.io(&v1);
                    a1.io(&v2);
                    a2[v1] = v2;                    
                }
            }

        //}
        CV__DNN_INLINE_NS_END
    }
}

