# Integrantes:
Sebastian Gian

Santiago González Flores - 2200165

## Binary Search:
Este código implementa dos funciones principales: <strong>bubble_sort</strong> y <strong>binary_search</strong>, que respectivamente ordenan una lista de números y buscan un valor específico en esa lista.

<strong>Bubble_sort:</strong> Esta función ordena una lista de números utilizando el algoritmo de ordenamiento de burbuja. El algoritmo recorre la lista múltiples veces, comparando elementos adyacentes y intercambiándolos si están en el orden incorrecto. Este proceso se repite hasta que no se requieran más intercambios, lo que indica que la lista está ordenada de forma ascendente.

<strong>Binary_search:</strong> Esta función busca un valor específico en una lista ordenada utilizando el algoritmo de búsqueda binaria. Este algoritmo divide repetidamente la lista por la mitad y compara el valor buscado con el elemento en el medio de la lista. Si el valor buscado es igual al elemento medio, se devuelve que se ha encontrado. Si el valor buscado es menor que el elemento medio, la búsqueda se realiza en la mitad inferior de la lista. Si es mayor, la búsqueda se realiza en la mitad superior. Este proceso se repite hasta que se encuentre el valor buscado o hasta que la lista se reduzca a cero, lo que indica que el valor no está presente en la lista.

Para la ejecución de los programa pedimos una reserva interactiva:
```
srun -n 4 --pty /bin/bash
```
### Código MPI:
<img style="height:869px; width:540px"  src="./images/binarySearch_pt1.png"/>
<img style="height:894px; width:527px"  src="./images/binarySearch_pt2.png"/>
<img style="height:894px; width:527px"  src="./images/binarySearch_pt3.png"/>
<img style="height:814px; width:472px"  src="./images/binarySearch_pt4.png"/>
<img style="height:608px; width:445px"  src="./images/binarySearch_pt5.png"/>

<strong>Explicación:</strong>
Se inicializa MPI y se declara variables como el rango (rank), el tamaño (size), la clave a buscar (key), una lista de tamaño fijo (list), y variables para medir el tiempo de ejecución. Luego, se divide la lista en sublistas para que cada proceso MPI pueda ordenar una porción de ella. Utilizando MPI_Scatter, se distribuye la lista entre los procesos. Se inicia el temporizador y se ordena cada sublista utilizando el algoritmo de ordenamiento de burbuja en la función bubble_sort(). Posteriormente, se utiliza MPI_Gather para reunir las sublistas ordenadas en el proceso raíz. Los procesos MPI se sincronizan y se mide y muestra el tiempo tomado para ordenar la lista.

Si el proceso es el raíz, se lee la clave de búsqueda. Utilizando MPI_Bcast, se transmite la clave de búsqueda a todos los procesos. Se inicia el temporizador y cada proceso realiza una búsqueda binaria en su sublista utilizando la función binary_search(). Se sincronizan los procesos MPI y se mide y muestra el tiempo tomado para realizar la búsqueda.

Además, la lista se divide en sublistas iguales para que cada proceso MPI maneje una porción de la lista. La semilla para la generación de números aleatorios se ajusta en función del rango del proceso MPI para garantizar resultados reproducibles y distribución uniforme de números aleatorios. La comunicación MPI se utiliza para distribuir la lista, recolectar sublistas ordenadas y transmitir la clave de búsqueda a todos los procesos.

### Resultados
Para la prueba se usaron n = 100.000, los cuales se seleccionaron de manera aleatoria con la semilla de time y
los resultados con los correspondientes comandos son los siguientes:

#### Binary Search
<img style="height:200px; width:1000px"  src="./images/BinarySearch_C.png"/>

#### Binary Search OpenMp
<img style="height:200px; width:1000px"  src="./images/BinarySearch_OMP.png"/>

#### Binary Search MPI
<img style="height:200px; width:1000px"  src="./images/BinarySearch_MPI.png"/>
