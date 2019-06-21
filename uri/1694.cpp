/*
   mathematics | simple combination
   problem: lottery
*/
#include <iostream>
#include <cstring>
using namespace std;

long long int coefBinomial[64][16]; //coefBinomial[i][j] = qte de possibilidades de escolher j elementos de um conjunto de i elementos (ordem não importa e j <= i)
bool ehPrimo[2501];

int qteNaoPrimosLinha[50], qteNaoPrimosColuna[50];

//gera todos coeficientes binomiais
void trianguloPascal(int n) {
   for (int i = 0; i <= n; i++)
      for (int j = 0; j <= min(i, 10); j++) { //pois 1 <= k <= 10
         if (j == 0 || j == i)
            coefBinomial[i][j] = 1;
         else
            coefBinomial[i][j] = coefBinomial[i - 1][j - 1] + coefBinomial[i - 1][j];
      }
}
//gera todos primos
void crivoErastotenes(int lim) {
   memset(ehPrimo, true, sizeof(ehPrimo));
   ehPrimo[0] = ehPrimo[1] = false;

   for (int i = 2; i * i <= lim; i++)
      if (ehPrimo[i])
         for (int j = i * i; j <= lim; j += i)
            ehPrimo[j] = false; //todos j são divisíveis por i, logo já não é primo
}

int main() {
   int qteLin, qteCol, k;
   trianguloPascal(50);
   crivoErastotenes(2500);

   while (true) {
      scanf("%d %d %d", &qteLin, &qteCol, &k);
      if (qteLin == 0 && qteCol == 0 && k == 0)
         break;

      memset(qteNaoPrimosLinha, 0, sizeof(int) * qteLin);
      memset(qteNaoPrimosColuna, 0, sizeof(int) * qteCol);

      for (int i = 0; i < qteLin; i++)
         for (int j = 0; j < qteCol; j++)
            if (!ehPrimo[i * qteCol + j]) {
               qteNaoPrimosLinha[i] += 1;
               qteNaoPrimosColuna[j] += (k != 1) ? 1 : 0; //evita aposta repetida
            }

      long long int qteApostas = 0, qte;
      for (int i = 0; i < qteLin; i++)
         if ((qte = qteNaoPrimosLinha[i]) >= k)
            qteApostas += coefBinomial[qte][k];
      for (int j = 0; j < qteCol; j++)
         if ((qte = qteNaoPrimosColuna[j]) >= k)
            qteApostas += coefBinomial[qte][k];
      printf("%lld\n", qteApostas);
   }
   return 0;
}