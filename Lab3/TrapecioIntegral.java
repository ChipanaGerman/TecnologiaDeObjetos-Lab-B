import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

// 1. Abstracción de la Función Matemática (POO)
interface FuncionMatematica {
    double evaluar(double x);
}

// 2. Implementación concreta de f(x) = 2x^2 + 3x + 0.5
class PolinomioCuadratico implements FuncionMatematica {
    @Override
    public double evaluar(double x) {
        return 2.0 * Math.pow(x, 2) + 3.0 * x + 0.5;
    }
}

// 3. Tarea concurrente para calcular un sub-rango de trapecios
class TareaTrapecio implements Callable<Double> {
    private final FuncionMatematica funcion;
    private final double a;
    private final double h;
    private final int inicio;
    private final int fin;

    public TareaTrapecio(FuncionMatematica funcion, double a, double h, int inicio, int fin) {
        this.funcion = funcion;
        this.a = a;
        this.h = h;
        this.inicio = inicio;
        this.fin = fin;
    }

    @Override
    public Double call() {
        double sumaParcial = 0.0;
        for (int i = inicio; i < fin; i++) {
            double x1 = a + i * h;
            double x2 = a + (i + 1) * h;
            sumaParcial += (funcion.evaluar(x1) + funcion.evaluar(x2)) * (h / 2.0);
        }
        return sumaParcial;
    }
}

// 4. Clase orquestadora con Pool de Threads
class IntegradorParalelo {
    private final FuncionMatematica funcion;
    private final int numeroHilos;
    private final ExecutorService threadPool;

    public IntegradorParalelo(FuncionMatematica funcion) {
        this.funcion = funcion;
        this.numeroHilos = Runtime.getRuntime().availableProcessors();
        this.threadPool = Executors.newFixedThreadPool(this.numeroHilos);
    }

    public double calcularArea(double a, double b, int n) throws InterruptedException, ExecutionException {
        double h = (b - a) / n;
        int cantidadPorHilo = (int) Math.ceil((double) n / numeroHilos);

        List<Future<Double>> resultadosFuturos = new ArrayList<>();

        for (int t = 0; t < numeroHilos; t++) {
            int inicio = t * cantidadPorHilo;
            int fin = Math.min(inicio + cantidadPorHilo, n);

            if (inicio < n) {
                Callable<Double> tarea = new TareaTrapecio(funcion, a, h, inicio, fin);
                resultadosFuturos.add(threadPool.submit(tarea));
            }
        }

        double areaTotal = 0.0;
        for (Future<Double> resultado : resultadosFuturos) {
            areaTotal += resultado.get();
        }
        return areaTotal;
    }

    public void cerrar() {
        this.threadPool.shutdown();
    }
}

// 5. Clase Principal
public class TrapecioIntegral {
    public static void main(String[] args) {
        double a = 2.0;
        double b = 20.0;
        double tolerancia = 1e-6; // Criterio de parada: cuando el valor se estabiliza

        FuncionMatematica funcion = new PolinomioCuadratico();
        IntegradorParalelo integrador = new IntegradorParalelo(funcion);

        System.out.println(" INTEGRACIÓN POR TRAPECIOS PARALELA (JAVA) ");
        System.out.printf("Intervalo: [%.2f, %.2f]%n", a, b);

        double areaAnterior = 0.0;
        int n = 1;
        boolean convergencia = false;

        try {
            while (!convergencia) {
                double areaActual = integrador.calcularArea(a, b, n);

                if (n > 1 && Math.abs(areaActual - areaAnterior) < tolerancia) {
                    System.out.printf("-> Convergencia alcanzada en n = %d trapecios.%n", n);
                    System.out.printf("Área final calculada: %.8f%n", areaActual);
                    convergencia = true;
                } else {
                    if (n == 1 || n % 1000 == 0) {
                        System.out.printf("Trapecios: %-8d | Área: %.8f%n", n, areaActual);
                    }
                    areaAnterior = areaActual;
                    n = (n < 64) ? n + 1 : n * 2; // Crecimiento progresivo para converger eficientemente
                }
            }
        } catch (InterruptedException | ExecutionException e) {
            System.err.println("Error en ejecución concurrente: " + e.getMessage());
        } finally {
            integrador.cerrar();
        }
    }
}