#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <memory>

// 1. POO: Clase base abstracta para la función
class FuncionBase {
public:
    virtual ~FuncionBase() = default;
    virtual double evaluar(double x) const = 0;
};

// Implementación de f(x) = 2x^2 + 3x + 0.5
class PolinomioCuadratico : public FuncionBase {
public:
    double evaluar(double x) const override {
        return 2.0 * x * x + 3.0 * x + 0.5;
    }
};

// 2. Estructura asignada dinámicamente para los rangos de cálculo
struct RangoCalculo {
    int inicio;
    int fin;
    double h;
    double a;

    RangoCalculo(int i, int f, double delta, double limiteInf)
        : inicio(i), fin(f), h(delta), a(limiteInf) {}
};

// 3. Implementación de un Thread Pool orientado a objetos con C++ moderno
class ThreadPool {
private:
    std::vector<std::thread> trabajadores;
    std::queue<std::function<void()>> tareas;
    std::mutex colaMutex;
    std::condition_variable condicion;
    bool detener;

public:
    ThreadPool(size_t numHilos) : detener(false) {
        for (size_t i = 0; i < numHilos; ++i) {
            trabajadores.emplace_back([this]() {
                while (true) {
                    std::function<void()> tarea;
                    {
                        std::unique_lock<std::mutex> lock(this->colaMutex);
                        this->condicion.wait(lock, [this]() {
                            return this->detener || !this->tareas.empty();
                        });
                        if (this->detener && this->tareas.empty()) {
                            return;
                        }
                        tarea = std::move(this->tareas.front());
                        this->tareas.pop();
                    }
                    tarea();
                }
            });
        }
    }

    template<class F>
    auto encolar(F&& f) -> std::future<typename std::result_of<F()>::type> {
        using tipoRetorno = typename std::result_of<F()>::type;
        auto tarea = std::make_shared<std::packaged_task<tipoRetorno()>>(std::forward<F>(f));
        std::future<tipoRetorno> res = tarea->get_future();
        {
            std::unique_lock<std::mutex> lock(colaMutex);
            if (detener) {
                throw std::runtime_error("No se pueden encolar tareas en un ThreadPool detenido");
            }
            tareas.emplace([tarea]() { (*tarea)(); });
        }
        condicion.notify_one();
        return res;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(colaMutex);
            detener = true;
        }
        condicion.notify_all();
        for (std::thread &trabajador : trabajadores) {
            if (trabajador.joinable()) {
                trabajador.join();
            }
        }
    }
};

// 4. Clase Integrador Numérico con Gestión Dinámica de Memoria
class IntegradorTrapecio {
private:
    const FuncionBase* funcion; // Referencia a objeto en Heap
    ThreadPool pool;
    size_t nucleos;

public:
    IntegradorTrapecio(const FuncionBase* fn)
        : funcion(fn),
          nucleos(std::thread::hardware_concurrency()),
          pool(nucleos > 0 ? nucleos : 4) {}

    double integrar(double a, double b, int n) {
        double h = (b - a) / n;
        int paso = std::ceil((double)n / nucleos);
        std::vector<std::future<double>> futuros;

        // Gestión de memoria dinámica manual en heap para los descriptores de tarea
        std::vector<RangoCalculo*> buffersRangos;

        for (size_t t = 0; t < nucleos; ++t) {
            int inicio = t * paso;
            int fin = std::min(inicio + paso, n);

            if (inicio < n) {
                // Asignación dinámica explícita (Heap)
                RangoCalculo* rango = new RangoCalculo(inicio, fin, h, a);
                buffersRangos.push_back(rango);

                futuros.push_back(pool.encolar([this, rango]() -> double {
                    double sumaLocal = 0.0;
                    for (int i = rango->inicio; i < rango->fin; ++i) {
                        double x1 = rango->a + i * rango->h;
                        double x2 = rango->a + (i + 1) * rango->h;
                        sumaLocal += (this->funcion->evaluar(x1) + this->funcion->evaluar(x2)) * (rango->h / 2.0);
                    }
                    return sumaLocal;
                }));
            }
        }

        double areaTotal = 0.0;
        for (auto &fut : futuros) {
            areaTotal += fut.get();
        }

        // Liberación explícita de memoria dinámica para evitar fugas (Memory Leaks)
        for (RangoCalculo* ptr : buffersRangos) {
            delete ptr;
        }

        return areaTotal;
    }
};

int main() {
    double a = 2.0;
    double b = 20.0;
    double tolerancia = 1e-6;

    // Instanciación dinámica del objeto Polinomio en el Heap (Memoria dinámica)
    FuncionBase* polinomio = new PolinomioCuadratico();
    IntegradorTrapecio* integrador = new IntegradorTrapecio(polinomio);

    std::cout << " INTEGRACIÓN POR TRAPECIOS PARALELA (C++) " << std::endl;
    std::cout << "Intervalo: [" << a << ", " << b << "]" << std::endl;

    double areaAnterior = 0.0;
    int n = 1;
    bool convergencia = false;

    while (!convergencia) {
        double areaActual = integrador->integrar(a, b, n);

        if (n > 1 && std::abs(areaActual - areaAnterior) < tolerancia) {
            std::cout << "-> Convergencia alcanzada en n = " << n << " trapecios." << std::endl;
            std::cout.precision(10);
            std::cout << "Área final calculada: " << std::fixed << areaActual << std::endl;
            convergencia = true;
        } else {
            if (n == 1 || n % 1000 == 0) {
                std::cout << "Trapecios: " << n << " | Área: " << areaActual << std::endl;
            }
            areaAnterior = areaActual;
            n = (n < 64) ? n + 1 : n * 2;
        }
    }

    // Limpieza de memoria dinámica
    delete integrador;
    delete polinomio;

    return 0;
}