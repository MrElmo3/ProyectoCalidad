#pragma once
#include <string>

// Interfaz para desacoplar el servicio externo (ej. API REST / Base de Datos)
class IServicioListaNegra {
public:
    virtual ~IServicioListaNegra() = default;
    virtual bool estaEnListaNegra(const std::string& password) = 0;
};

// Interfaz secundaria para auditoria/logs (util para demostrar Dummy)
class IAuditor {
public:
    virtual ~IAuditor() = default;
    virtual void registrarEvento(const std::string& mensaje) = 0;
};
