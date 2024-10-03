# Parallel Computing

Diego Andrés Alonzo Medinilla 20172


## Al realizar la paralelización, ¿qué está pasando internamente y por qué el resultado no mejora

En primer lugar open mp crea y gestiona muchas tareas y esto se sobrecarga, de manera que a pesar que se creen en diferentes hilos estas se deben de gestionar, distribuirlas entre hilos y sincronizarlas a partir del taskwait. Esto es producto por ser tareas muy pequeñas ya que solo es sumas y demás lo que precisamente introduce una sobrecarga por gestión de hilos.

