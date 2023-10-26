#pragma once

#include <opencv2/core.hpp>
#include <fstream>
#include <map>
#include <set>
#include <unordered_map>
#include "../dnn/version.hpp"

using namespace std;
namespace cv {
    namespace dnn {
        CV__DNN_INLINE_NS_BEGIN

        //namespace dnn_serialization {
            class CV_EXPORTS_W_SIMPLE DnnReader
            {
            public:
                void io(unsigned char *);
                void io(unsigned int *);
                void io(int *);
                void io(float *);
                void io(double *);
                void io(unsigned char *, uint);
                void io(Size *);

                int getPos();
                void gotoPos(uint);

            public:
                //basic_istream<char> *m_pDR_istream;
                istream * m_pDR_istream;
            };

        CV_EXPORTS_W_SIMPLE void io(DnnReader & a1, String & a2);
        CV_EXPORTS_W_SIMPLE void io(DnnReader & a1, Mat & a2);
        CV_EXPORTS_W_SIMPLE void io(DnnReader & a1, MatSize & a2);
            
        CV_EXPORTS_W_SIMPLE void io(DnnReader &a1, vector<Mat> &a2);
        CV_EXPORTS_W_SIMPLE void io_vec_String(DnnReader &a1, vector<String> &a2);

        CV_EXPORTS_W_SIMPLE void io_vec_int(DnnReader &a1, vector<int> &a2);
        CV_EXPORTS_W_SIMPLE void io_vec_uint(DnnReader &a1, vector<uint> &a2);
        CV_EXPORTS_W_SIMPLE void io_vec_vec_uint(DnnReader &a1, vector<vector<uint>> &a2);
        CV_EXPORTS_W_SIMPLE void io(DnnReader &a1, vector<double> &a2);

        CV_EXPORTS_W_SIMPLE void io_set_int(DnnReader &a1, set<int> &a2);
        CV_EXPORTS_W_SIMPLE void io_set_uint(DnnReader &a1, set<uint> &a2);

        CV_EXPORTS_W_SIMPLE void io_map_String_int(DnnReader &a1, map<String, int> &a2);

        CV_EXPORTS_W_SIMPLE void io(DnnReader &a1, unordered_map<uint, uint> & a2);



            //template <class _Tx, class _Ty, class _Tz> void io(_Tx & a1, map<_Ty, _Tz> & a2);
            //template <class _Tx, class _Ty> void io(_Tx & a1, set<_Ty> & a2);
            //template <class _Tx, class _Ty> void io(_Tx & a1, unordered_map<_Ty, _Ty> & a2);
        //}
        CV__DNN_INLINE_NS_END
    }
}
