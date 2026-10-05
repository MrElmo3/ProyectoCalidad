#include "validador_seguridad.h"
#include <regex>

ValidadorSeguridad::ValidadorSeguridad(IServicioListaNegra* servicio, IAuditor* aud)
    : servicioListaNegra(servicio), auditor(aud) {}

bool ValidadorSeguridad::esValida(const std::string& password) {
    // 1. Reglas básicas locales de formato
    if (password.length() < 8) return false;
    if (!std::regex_search(password, std::regex("\\d"))) return false;
    if (!std::regex_search(password, std::regex("[A-Z]"))) return false;

    // 2. Consulta al servicio externo de seguridad (si está presente)
    if (servicioListaNegra != nullptr) {
        if (servicioListaNegra->estaEnListaNegra(password)) {
            if (auditor != nullptr) {
                auditor->registrarEvento("Intento de uso de contrasena vulnerada: " + password);
            }
            return false;
        }
    }

    return true;
}
