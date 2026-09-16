package main

import (
	"fmt"
	"math"
	"runtime"
	"sync"
)

// 1. POO en Go mediante Interfaces y Estructuras
type FuncionMatematica interface {
	Evaluar(x float64) float64
}

// Estructura que implementa la interfaz
type PolinomioCuadratico struct{}

func (p PolinomioCuadratico) Evaluar(x float64) float64 {
	return 2.0*math.Pow(x, 2) + 3.0*x + 0.5
}

// 2. Estructura de Trabajo para el Worker Pool
type Tarea struct {
	Inicio int
	Fin    int
	A      float64
	H      float64
}

// 3. Worker del Pool: Ejecuta concurrentemente sobre Goroutines
func worker(id int, funcion FuncionMatematica, tareas <-chan Tarea, resultados chan<- float64, wg *sync.WaitGroup) {
	defer wg.Done()
	for tarea := range tareas {
		sumaLocal := 0.0
		for i := tarea.Inicio; i < tarea.Fin; i++ {
			x1 := tarea.A + float64(i)*tarea.H
			x2 := tarea.A + float64(i+1)*tarea.H
			sumaLocal += (funcion.Evaluar(x1) + funcion.Evaluar(x2)) * (tarea.H / 2.0)
		}
		resultados <- sumaLocal
	}
}

// 4. Integrador que administra el Pool de Goroutines
type IntegradorGo struct {
	Funcion    FuncionMatematica
	NumWorkers int
}

func NuevoIntegrador(fn FuncionMatematica) *IntegradorGo {
	return &IntegradorGo{
		Funcion:    fn,
		NumWorkers: runtime.NumCPU(),
	}
}

func (ig *IntegradorGo) Integrar(a, b float64, n int) float64 {
	h := (b - a) / float64(n)
	paso := int(math.Ceil(float64(n) / float64(ig.NumWorkers)))

	tareas := make(chan Tarea, ig.NumWorkers)
	resultados := make(chan float64, ig.NumWorkers)
	var wg sync.WaitGroup

	// Despacho de Workers fijos (Pool)
	for w := 0; w < ig.NumWorkers; w++ {
		wg.Add(1)
		go worker(w, ig.Funcion, tareas, resultados, &wg)
	}

	// Envío de fragmentos de integración a los canales
	for t := 0; t < ig.NumWorkers; t++ {
		inicio := t * paso
		fin := inicio + paso
		if fin > n {
			fin = n
		}
		if inicio < n {
			tareas <- Tarea{Inicio: inicio, Fin: fin, A: a, H: h}
		}
	}
	close(tareas) // Cierra el canal de tareas para que los workers finalicen el bucle

	// Goroutine auxiliar para cerrar el canal de resultados cuando terminen todos los workers
	go func() {
		wg.Wait()
		close(resultados)
	}()

	// Recolección y reducción del área total
	areaTotal := 0.0
	for res := range resultados {
		areaTotal += res
	}

	return areaTotal
}

func main() {
	a := 2.0
	b := 20.0
	tolerancia := 1e-6

	funcion := PolinomioCuadratico{}
	integrador := NuevoIntegrador(funcion)

	fmt.Println(" INTEGRACIÓN POR TRAPECIOS PARALELA (GO) ")
	fmt.Printf("Intervalo: [%.2f, %.2f] | Workers: %d\n", a, b, integrador.NumWorkers)

	areaAnterior := 0.0
	n := 1
	convergencia := false

	for !convergencia {
		areaActual := integrador.Integrar(a, b, n)

		if n > 1 && math.Abs(areaActual-areaAnterior) < tolerancia {
			fmt.Printf("-> Convergencia alcanzada en n = %d trapecios.\n", n)
			fmt.Printf("Área final calculada: %.8f\n", areaActual)
			convergencia = true
		} else {
			if n == 1 || n%1000 == 0 {
				fmt.Printf("Trapecios: %-8d | Área: %.8f\n", n, areaActual)
			}
			areaAnterior = areaActual
			if n < 64 {
				n++
			} else {
				n *= 2
			}
		}
	}
}