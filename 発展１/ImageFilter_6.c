#define PI 3.1415926
void HoughTransform(void) {

 int iWidth, iHeight, iMaxValue;
 int * piInputData;
 int * piOutputData;
 int * piOutputData2;
 int i, j, x, y;
 int n = 180;
 double T = PI / n;
 double * SIN;
 double * COS;
 double R;
 int Rmax, Rmax2;
 int max = 0;

 printf("\n***** HoughTransform *****\n");

 piInputData = ReadPgm( & iWidth, & iHeight, & iMaxValue);

 Rmax = (int) sqrt(iWidth * iWidth + iHeight * iHeight) + 1;
 Rmax2 = 2 * Rmax;

 piOutputData = (int * ) malloc(n * Rmax2 * sizeof(int));
 piOutputData2 = (int * ) malloc(iWidth * iHeight * sizeof(int));
 SIN = (double * ) malloc(n * sizeof(double));
 COS = (double * ) malloc(n * sizeof(double));

printf("\n***** HoughTransforming Loading *****\n");
 for (i = 0; i < n; i++) {
  SIN[i] = sin(T * i);
  COS[i] = cos(T * i);
 }
 for (i = 0; i < (Rmax2 * n); i++) {
  piOutputData[i] = 0;
 }
 for (i = 0; i < (iWidth * iHeight); i++) {
  piOutputData2[i] = 0;
 }
 for (y = 0; y < iHeight; y++) {
  for (x = 0; x < iWidth; x++) {
   if (piInputData[y * iWidth + x] == 255) {
    for (i = 0; i < n; i++) {
     R = (int)(x * COS[i] + y * SIN[i] + 0.5);
     piOutputData[(int)((R + Rmax) * n + i)]++;
    }
   }
  }
 }
 for (i = 0; i < Rmax2 * n; i++) {
  if (piOutputData[i] > max)
   max = piOutputData[i];
 }
 for (i = 0; i < Rmax2 * n; i++) {
  piOutputData[i] = piOutputData[i] * 255 / max;
 }
printf("\n***** HoughTransform Success *****\n");


printf("\n***** Inverse HoughTransform Loading *****\n");
 for (i = 0; i < n; i++) {
  for (j = 0; j < Rmax2; j++) {
   if (piOutputData[j * n + i] > 50) {
    if (
     piOutputData[j * n + i] >= piOutputData[j * n + i - 1] &&
     piOutputData[j * n + i] >= piOutputData[j * n + i + 1] &&
     piOutputData[j * n + i] >= piOutputData[(j + 1) * n + i] &&
     piOutputData[j * n + i] >= piOutputData[(j + 1) * n + i - 1] &&
     piOutputData[j * n + i] >= piOutputData[(j + 1) * n + i + 1] &&
     piOutputData[j * n + i] >= piOutputData[(j - 1) * n + i] &&
     piOutputData[j * n + i] >= piOutputData[(j - 1) * n + i - 1] &&
     piOutputData[j * n + i] >= piOutputData[(j - 1) * n + i + 1])
      {
      if (i == 0 || i == 180) {
       for (y = 0; y < iHeight; y++) {
        x = (int)(-y * (SIN[i] / COS[i]) + ((j - Rmax) / COS[i]));
        if (x >= 0 && x <= iWidth) {
         piOutputData2[y * iWidth + x] = 255;
        }
       }
      } else {
       for (x = 0; x < iWidth; x++) {
        y = (int)(-(COS[i] / SIN[i]) * x + ((j - Rmax) / SIN[i]));
        if (y >= 0 && y <= iHeight) {
         piOutputData2[y * iWidth + x] = 255;
        }
       }
      }
     }
   }
  }
 }
printf("\n***** Inverse HoughTransform Success *****\n");

 // 入力データを保存しているメモリ領域を解放
 FreePgm(piInputData);
 //PGM 形式のファイルに出力データを出力
 WritePgm(piOutputData, n, Rmax2, iMaxValue);
 WritePgm(piOutputData2, iWidth, iHeight, iMaxValue);
 // 出力データを保存しているメモリ領域を解放
 FreePgm(piOutputData);
 FreePgm(piOutputData2);
}