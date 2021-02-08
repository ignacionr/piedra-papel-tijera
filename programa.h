#include <iostream>

template<typename Juego>
struct Programa {
    int main() {
        Juego juego;
        while (!juego.estado().esFinal()) {
            juego.paso();
        }
        std::cout << static_cast<std::string>(juego.estado()) << std::endl;
        return 0;
    }
};
