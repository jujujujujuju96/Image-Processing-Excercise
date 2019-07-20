//=====================================================================//
//                                                                     //
//  ファイル名 : ImageFilter.c                                         //
//  内      容 : PPM(Portable PixMap) または PGM(Portable GrayMap)形式 //
//               のデータを画像処理する関数の定義                      //
//  更  新  日 : 2004. 2. 14 木村 彰徳 (Computer Graphics Lab.)        //
//               2003. 3. 21 駒井 教平 (Computer Vision & Games Lab.)  //
//                                                                     //
//=====================================================================//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "ImageFilter.h"

#include "ImageFileIO.h"
#include "ImageTools.h"

//---------------------------------------------------------------------//
// 例１）                                                              //
// void  NegativeImage(void)                                           //
//  内      容 : PPM形式の入力データをネガ画像に変換                   //
//  更  新  日 : 2004. 2. 11 木村 彰徳 (Computer Graphics Lab.)        //
//---------------------------------------------------------------------//
void NegativeImage(void) {

    int iWidth, iHeight, iMaxValue;   // 画像の幅，高さ，解像度
    struct RGB * pRGBInputData;       // 入力データを格納
    struct RGB * pRGBOutputData;      // 画像処理したデータを格納
    int i;                            // ループカウンタ

    // ネガ画像
    printf("\n**** Negative Image *****\n");

    // PPM形式の入力データの読み込み
    pRGBInputData = ReadPpm(&iWidth, &iHeight, &iMaxValue);
    
    // 出力データ（１次元）のメモリ領域の確保
    // pRGBOutputData[iWidth*iHeight]
    pRGBOutputData = (struct RGB *)malloc(iWidth*iHeight*sizeof(struct RGB));

    // 入力データ(pRGBInputmData)のRGBの値を反転して，
    // 出力データ(pRGBOutputData)に保存
    for(i = 0; i < iWidth*iHeight; i++){
	pRGBOutputData[i].iRed   = iMaxValue - pRGBInputData[i].iRed;
	pRGBOutputData[i].iGreen = iMaxValue - pRGBInputData[i].iGreen;
	pRGBOutputData[i].iBlue  = iMaxValue - pRGBInputData[i].iBlue;
    }

    // 入力データを保存しているメモリ領域を解放
    FreePpm(pRGBInputData);

    // PPM形式のファイルに出力データを出力
    WritePpm(pRGBOutputData, iWidth, iHeight, iMaxValue);

    // 出力データを保存しているメモリ領域を解放
    FreePpm(pRGBOutputData);
}


//---------------------------------------------------------------------//
// 例2）                                                              //
// void DrawLines(void)                                                //
//  内      容 : PGM形式のデータに線を描く　　                         //
//  更  新  日 : 2004. 2. 12 木村 彰徳 (Computer Graphics Lab.)        //
//---------------------------------------------------------------------//
void DrawLines(void) {
    
    
    int iWidth, iHeight, iMaxValue;     // 画像の幅，高さ，解像度
    int * piOutputData;                 // 画像処理したデータを格納
    int iIndex;                         // インデックス
  //  int w, h, x, y;                   // 座標ループカウンタ
    int iStartX, iStartY, iEndX, iEndY; // 直線の始点と終点座標　
    int iWHITE;                         // 白の値


    // 線を描く
    printf("\n**** Draw Lines *****\n");

    // 画像の幅，高さ，解像度の指定と白の設定
    iWidth  = 400;
    iHeight = 400;
    iMaxValue = 255;
    iWHITE = iMaxValue;

    // 出力データ（１次元）のメモリ領域の確保
    // piOutputData[iWidth*iHeight]
    piOutputData = (int *)malloc(iWidth*iHeight*sizeof(int));

    // 画素を白で初期化
    for(iIndex = 0; iIndex < iWidth*iHeight; iIndex++)
	piOutputData[iIndex] = iWHITE;


    // 出力データ(piOutputData)に線を描く
    iStartX = 0; iStartY = 0;
    iEndY = iHeight;
    for(iEndX = iWidth - 1; iEndX >= 0; iEndX-=5) {
	DrawStraightLine(piOutputData, iWidth, iHeight, iMaxValue,
			 iStartX, iStartY, iEndX, iEndY, SOLID, BLACKLINE);
    }
    iEndX = iWidth;
    for(iEndY = iHeight - 1; iEndY >= 0; iEndY-=5) {
	DrawStraightLine(piOutputData, iWidth, iHeight, iMaxValue,
			 iStartX, iStartY, iEndX, iEndY, SOLID, BLACKLINE);
    }

    // PGM形式のファイルに出力データを出力
    WritePgm(piOutputData, iWidth, iHeight, iMaxValue);

    // 出力データを保存しているメモリ領域を解放
    FreePgm(piOutputData);
}
//---------------------------------------------------------------------//
// 1）                                                               //
// void GrayscaleImage(void)                                　//
//  内      容 : 濃淡画像の生成                         　　　　　　　 　//
//---------------------------------------------------------------------//
void GrayscaleImage(void) {

    int iWidth, iHeight, iMaxValue;   // 画像の幅，高さ，解像度
    struct RGB * pRGBInputData;       // 入力データを格納
    int * pYOutputData;      // YIQを定義
    int i;                            // ループカウンタ
    int a,b,c;

    // ネガ画像
    printf("\n**** Grayscale Image *****\n");

    // PPM形式の入力データの読み込み
    pRGBInputData = ReadPpm(&iWidth, &iHeight, &iMaxValue);
    
    // 出力データ（１次元）のメモリ領域の確保
   // pRGBOutputData[iWidth*iHeight]
    pYOutputData = (int *)malloc(iWidth*iHeight*sizeof(int));


    // 出力データ(pRGBOutputData)に保存
    a = 0.3 * 1024;
    b = 0.6 * 1024;
    c = 0.1 * 1024;

    for(i = 0; i < iWidth*iHeight; i++){
	pYOutputData[i] = (a*pRGBInputData[i].iRed +
                            b*pRGBInputData[i].iGreen +
	                     c*pRGBInputData[i].iBlue) / 1024;
    }
    // 入力データを保存しているメモリ領域を解放
    FreePpm(pRGBInputData);

    // PPM形式のファイルに出力データを出力
    WritePgm(pYOutputData, iWidth, iHeight, iMaxValue);

    // 出力データを保存しているメモリ領域を解放
    FreePgm(pYOutputData);
}


