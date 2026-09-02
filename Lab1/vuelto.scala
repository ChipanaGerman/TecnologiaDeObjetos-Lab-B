import scala.io.StdIn // Importamos la herramienta para leer del teclado

object Laboratorio01 {
  def main(args: Array[String]): Unit = {
    println("--- CALCULADORA DE VUELTO ---")

    // 1. Pedir la cantidad de dinero
    print("Ingresa la cantidad total (money): ")
    val money = StdIn.readInt()

    // 2. Pedir las denominaciones de monedas
    // El usuario debe ingresarlas separadas por espacios, ej: 1 2 5 10 20
    print("Ingresa las monedas disponibles separadas por espacio: ")
    val inputMonedas = StdIn.readLine()
    
    // Convertimos el texto ingresado en una Lista de Enteros
    val coins = inputMonedas.split(" ").map(_.toInt).toList

    // 3. Llamar a la función y mostrar resultado
    val soluciones = countChange(money, coins)
    
    println(s"\nPara un total de $money con monedas [${coins.mkString(", ")}]:")
    println(s"Hay $soluciones maneras diferentes de dar el vuelto.")
  }

  // LA FUNCIÓN RECURSIVA (El corazón del lab)
  def countChange(money: Int, coins: List[Int]): Int = {
    if (money == 0) {
      1 // ¡Éxito! Encontramos una combinación exacta
    } 
    else if (money < 0 || coins.isEmpty) {
      0 // No sirve: o nos pasamos o nos quedamos sin monedas
    } 
    else {
      // AQUÍ ESTÁ EL TRUCO:
      // Sumamos dos caminos:
      // 1. Usar la moneda actual (head): restamos su valor al dinero
      // 2. Ignorar la moneda actual y probar con el resto (tail)
      countChange(money - coins.head, coins) + countChange(money, coins.tail)
    }
  }
}