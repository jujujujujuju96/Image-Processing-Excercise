void Templatematching(void) {
 int iWidth, iHeight, iMaxValue;
 int * pInputData;
 int * pOutputData;
 int * pattenData;
 int i, j;
 int x, y;
 int M, N;
 int X=0, Y=0;
 double Ta, Tb;
 double WT, Wa, Wb;
 double * R;
 double Buff = -1;
 FILE * file_x;
 FILE * file_y;
 file_x = fopen("file_x.data", "w+");
 file_y = fopen("file_y.data", "w+");

 pInputData = ReadPgm( & iWidth, & iHeight, & iMaxValue);
 pattenData = ReadPgm( & M, & N, & iMaxValue);
 pOutputData = (int * ) malloc(M * N * sizeof(int));
 R = (double * ) malloc((iWidth - M + 1) * (iHeight - N + 1) * sizeof(double));

 printf("\n**** Now Templatematching *****\n");
 printf("\n**** Please Wait *****\n");

 //テンプレート画像の輝度値の合計を求める
 Ta = 0;
 Tb = 0;
 for (i = 0; i < M - 1; i++) {
  for (j = 0; j < N - 1; j++) {
   Ta += pattenData[j * M + i];
   Tb += pattenData[j * M + i] * pattenData[j * M + i];
  }
 }

 //探索画像の点(K-M+1)*(L-N+1)について注目する
 for (x = 0; x < iWidth - M; x++) {
  for (y = 0; y < iHeight - N; y++) {
   WT = 0;
   Wa = 0;
   Wb = 0;
   //テンプレート画像との正規化相関を求める
   for (i = 0; i < M - 1; i++) {
    for (j = 0; j < N - 1; j++) {
     WT += pInputData[x + i + iWidth * (y + j)] * pattenData[i + j * M];
     Wa += pInputData[x + i + iWidth * (y + j)];
     Wb += pInputData[x + i + iWidth * (y + j)] * pInputData[x + i + iWidth * (y + j)];
    }
   }
   R[x + y * (iWidth - M + 1)] = (double)((WT - Wa * Ta / (double)(M * N)) / sqrt((Wb - Wa * Wa / (double)(M * N)) * (Tb - Ta * Ta / (double)(M * N))));
   //探索した点の中で一番相関が強い場所を記憶する
   if (Buff < R[x + y * (iWidth - M + 1)]) {
    X = x;
    Y = y;
    Buff = R[x + y * (iWidth - M + 1)];
   }
  }
 }

 //出力の部分
 for (i = 0; i < M - 1; i++) {
  for (j = 0; j < N - 1; j++) {
   pOutputData[i + j * M] = pInputData[X + i + (Y + j) * iWidth];
  }
 }
 WritePgm(pOutputData, M, N, iMaxValue);
 for (i = 0; i < iWidth - M; i++) {
  fprintf(file_x, "%d\t", i);
  fprintf(file_x, "%f\n", R[i + Y * (iWidth - M + 1)]);
 }
 for (i = 0; i < iHeight - N; i++) {
  fprintf(file_y, "%d\t", i);
  fprintf(file_y, "%f\n", R[X + i * (iWidth - M + 1)]);
 }
 FreePgm(pInputData);
 FreePgm(pattenData);
 FreePgm(pOutputData);
}









