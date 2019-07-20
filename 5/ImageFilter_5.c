void MosaicImage(void) {

 int iWidth, iHeight, iMaxValue;
 int * pInputData;
 int * pOutputData;
 int i, j;
 int n;
 int N, M;
 int Value;
 pInputData = ReadPgm( & iWidth, & iHeight, & iMaxValue);
 pOutputData = (int * ) malloc(iWidth * iHeight * sizeof(int));

 printf("nの値を入力してください");
 scanf("%d", & n);

 printf("\n**** Now Mosaicing *****\n");
 printf("\n**** Please Wait *****\n");

 for (i = 0; i < iWidth / n; i++) {
  for (j = 0; j < iHeight / n; j++) {
   Value = 0;
   for (M = 0; M < n; M++) {
    for (N = 0; N < n; N++) {
     Value += pInputData[(j * n + N) * iWidth + i * n + M];
    }
   }
   for (M = 0; M < n; M++) {
    for (N = 0; N < n; N++) {
     pOutputData[(j * n + N) * iWidth + i * n + M] = Value / (n * n);
    }
   }
  }
 }

 WritePgm(pOutputData, iWidth, iHeight, iMaxValue);
 FreePgm(pOutputData);

}


