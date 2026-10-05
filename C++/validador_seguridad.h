#pragma once
#include <string>
#include <memory>
#include "servicio_lista_negra.h"

class ValidadorSeguridad {
private:
    IServicioListaNegra* servicioListaNegra;
    IAuditor* auditor;

public:
    // Permite inyección de dependencias (DI)
    ValidadorSeguridad(IServicioListaNegra* servicio, IAuditor* auditor = nullptr);

    bool esValida(const std::string& password);
};
