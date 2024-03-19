## Postman Sort
<p>Es un algoritmo de ordenamiento de complejidad:  </p>
<ul>
  <li>Complejidad temporal = $$d * (n + k)$$</li>
  <li>Complejidad espacial = $$n + 2^d$$ </li>
</ul>
<p>Donde d es el numero de digitos, n el numero de datos y k el numero de baldes </p>
Este algoritmo es una variante del  <strong>Bucket Sort</strong> que aprovecha la jerarquía estructural
de los elementos, permite agrupar los elementos en subgrupos en este caso con digitos similares y asi reordena los subgrupos
para dar una lista ordenada.

Para ejecutar este programa es necesario entrar a <strong>guaneExa</strong>
```
ssh guaneExa
```
Para compilar el código secuencial se tiene que ejecutar el siguiente comando (Cabe aclararar que se usa OpenMP para medir los tiempos):
```
srun -n 10 -w ExaDELL --pty /bin/bash
gcc -fopenmp postmansort.c -o postmansort
./postmansort
```
Para ejecutar el código paralelizado basta con ejecutar el siguien SBATCH
```
sbatch postmansort.sbatch
```
