#include<array>
#include <string>
#include <functional>
#include <iostream>

class PiedraPapelTijera 
{
    const std::array<std::string,3> opciones_ {"piedra", "papel", "tijera"};
    struct Estado {
        const std::array<std::string,4> en_palabras_ {"empate", "perdió", "ganó", "no sabemos"};
        enum TipoEstado {
            empate,
            perdio,
            gano,
            indeterminado
        };
        TipoEstado estado_ {TipoEstado::indeterminado};
        bool esFinal() const { return estado_ != TipoEstado::indeterminado; }
        operator std::string() const {
            return en_palabras_[static_cast<int>(estado_)];
        }
    } estado_;
    int pos_usuario_ {-1};
    int pos_computadora_;
    std::function<void()> siguiente_paso_;

    void obtener_jugada_usuario() {
        std::string valor;
        // ingresar la opción del usuario (piedra, papel o tijera)
        std::cout << "Ingrese piedra, papel o tijera: ";
        std::cin >> valor;
        // validar que sea una opción conocida
        auto const pos { std::find(opciones_.begin(), opciones_.end(), valor)};
        pos_usuario_ = pos == opciones_.end() ? -1 : pos - opciones_.begin();
        if (pos_usuario_ != -1) {
            siguiente_paso_ = [this](){ elegir_jugada_computadora(); };
        }
    }
    void elegir_jugada_computadora() {
        // elegir la opción de la computadora
        std::srand(time(nullptr));
        pos_computadora_ = std::rand() % 3;
        siguiente_paso_ = [this](){ determinar_ganador(); };
    }
    void determinar_ganador() {
        std::cout << opciones_[pos_usuario_] << " vs " << opciones_[pos_computadora_] << ": ";

        const std::string resultados_posibles[] {"Empate", "Pierde", "Gana"};
        auto const indice {(pos_computadora_ - pos_usuario_ + 3) % 3};
        estado_.estado_ = static_cast<Estado::TipoEstado>(indice);
    }

public:
    PiedraPapelTijera() 
    {
        siguiente_paso_ = [this](){ obtener_jugada_usuario(); };
    }
    const Estado &estado() const { return estado_; }
    
    void paso() { siguiente_paso_(); }
};
