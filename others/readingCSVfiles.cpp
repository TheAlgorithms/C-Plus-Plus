// Lectura de un archivo .csv
//
//R.E. Sánchez Yáñez

#include <iostream>
#include <cstdio>

using namespace std;

int main(void)
{
   cout << "Lectura de un archivo .csv con dos datos por renglón." << endl;

   char cad[80];

   // Ahora vamos a leer
   FILE *archivo = fopen("datos.csv", "rt");
   if (archivo == NULL)
   {
      printf("\nNo se pudo abrir el archivo de lectura...");
      return -1;
   }

   // Verificamos cuántos renglones (sin espacios) tenemos
   cout << "\n\nLeyendo archivo.\n";
   int nRenglones = 0;
   while ( fgets(cad,80,archivo) != NULL && cad[0] != '\n')
      nRenglones++;
   cout << "\n\nSe leyeron "<< nRenglones << " renglones.\n";

   // Y regresamos al inicio del archivo
   rewind(archivo);

   // Reservamos memoria para los arreglos
   float *x = new float[nRenglones];
   float *y = new float[nRenglones];

   // Releemos y asignamos los valores
   for (int k=0; k < nRenglones; k++)
   {
      fgets(cad,80,archivo);
      sscanf(cad, "%f%*c%f%\n", &x[k], &y[k]); // ¡¡¡ !!!  El *c es para "descartar un caracter"
   }
   // IMPORTANTE: Cerramos el archivo
   fclose(archivo);

	cout << "\n\nPares ordenados:\n";
   for (int k=0; k < nRenglones; k++)
      printf("(%5.1f, %5.1f)\n",x[k], y[k]);

   // IMPORTANTE: Liberamos la memoria asignada
   delete[] x;
   delete[] y;

   cin.get();
   return 0;
}
