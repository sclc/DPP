//==========================================================================
// 時間計測用クラス
//
// (c)Copyright Spacesoft corp., 2015 All rights reserved.
//                                    Kitayama, Hiroyuki
//
//==========================================================================
#ifndef spCpfmh
#define spCpfmh

#include <windows.h>

//--------------------------------------------------------------------------
// クラス
class Cpfm
{

private:
    // ----- private member -------------------------------------------------
    int         counter;
    const static int   maxCounter=10;
    LARGE_INTEGER   *liTime;


public:
    Cpfm(void)                                  // コンストラクタ
    {
        liTime=new LARGE_INTEGER[maxCounter];
        counter=0;
    }

    virtual ~Cpfm(void)                         // デストラクタ
    {
        if(counter!=0)
            delete[] liTime;
    }


    // ----- public method --------------------------------------------------

    //------------------------------------------------------
    // get crrrent counter
    void
    Cpfm::getTime(void)
    {
        if(counter>=maxCounter)
            return;                             // overflow

        QueryPerformanceCounter( &(liTime[counter++]));
    }


    //------------------------------------------------------
    // print time
    void
    Cpfm::printTime(void)
    {
        LARGE_INTEGER   liFreq;
        QueryPerformanceFrequency(&liFreq);

        if(counter>2)
        {
            for(int i=1;i<counter;i++)
            {
                printf( "%d: time = %16.9lf[ms]\n", i,
                    1000.0*(double)(liTime[i].QuadPart-liTime[i-1].QuadPart)
                                                            /liFreq.QuadPart );
            }
        }
        fprintf(stderr, "total   = %16.9lf[ms]\n",
                    1000.0*(double)(liTime[counter-1].QuadPart
                                        - liTime[0].QuadPart)/liFreq.QuadPart );
    }
};
//---------------------------------------------------------------------------
#endif
