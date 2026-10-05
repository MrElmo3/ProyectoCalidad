#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_set>
#include <vector>
#include "validador_seguridad.h"

using ::testing::_;
using ::testing::Return;

// ============================================================================
// 1. DUMMY:
// Objeto de relleno. Solo se pasa para satisfacer la firma de un parámetro
// obligatorio, pero el test nunca espera que se use ni inspecciona su contenido.
// ============================================================================
class DummyAuditor : public IAuditor {
public:
    void registrarEvento(const std::string& /*mensaje*/) override {
        // No hace absolutamente nada.
    }
};

TEST(DoblesPrueba, UsoDeDummy) {
    // Para probar rechazo por formato, necesitamos pasar un auditor no nulo
    DummyAuditor dummy;
    ValidadorSeguridad validador(nullptr, &dummy);

    // Falla por formato (< 8 caracteres), dummy nunca es relevante para la aserción
    EXPECT_FALSE(validador.esValida("Corta1"));
}

// ============================================================================
// 2. STUB:
// Devuelve respuestas fijas y "enlatadas" predefinidas para conducir la prueba.
// No le importa la lógica real, solo responde lo que necesitamos para el test.
// ============================================================================
class StubListaNegraSiempreVulnerada : public IServicioListaNegra {
public:
    bool estaEnListaNegra(const std::string& /*password*/) override {
        return true; // Siempre simula que la clave está filtrada/comprometida
    }
};

TEST(DoblesPrueba, UsoDeStub) {
    StubListaNegraSiempreVulnerada stub;
    ValidadorSeguridad validador(&stub);

    // Cumple formato, pero el Stub asegura que el validador la rechace por lista negra
    EXPECT_FALSE(validador.esValida("PasswordSegura123"));
}

// ============================================================================
// 3. SPY (Espía):
// Registra información sobre cómo fue llamado (número de invocaciones, parámetros)
// para que el test pueda inspeccionar el estado después de la ejecución.
// ============================================================================
class SpyAuditor : public IAuditor {
public:
    int llamadas = 0;
    std::string ultimoMensaje;

    void registrarEvento(const std::string& mensaje) override {
        llamadas++;
        ultimoMensaje = mensaje;
    }
};

TEST(DoblesPrueba, UsoDeSpy) {
    StubListaNegraSiempreVulnerada stub;
    SpyAuditor espia;
    ValidadorSeguridad validador(&stub, &espia);

    validador.esValida("Password123");

    // El Spy permite verificar efectos secundarios
    EXPECT_EQ(espia.llamadas, 1);
    EXPECT_NE(espia.ultimoMensaje.find("Password123"), std::string::npos);
}

// ============================================================================
// 4. MOCK:
// Objeto pre-programado con expectativas estrictas de comportamiento (GTest / GMock).
// Verifica no solo el resultado, sino la interacción exacta (protocolo).
// ============================================================================
class MockServicioListaNegra : public IServicioListaNegra {
public:
    MOCK_METHOD(bool, estaEnListaNegra, (const std::string& password), (override));
};

TEST(DoblesPrueba, UsoDeMockConGoogleMock) {
    MockServicioListaNegra mockServicio;

    // Expectativa: se debe llamar exactamente 1 vez con el argumento "Abcd1234"
    // y debe retornar false (no está en lista negra).
    EXPECT_CALL(mockServicio, estaEnListaNegra("Abcd1234"))
        .Times(1)
        .WillOnce(Return(false));

    ValidadorSeguridad validador(&mockServicio);

    // Verificación
    EXPECT_TRUE(validador.esValida("Abcd1234"));
}

// ============================================================================
// 5. FAKE:
// Implementación simplificada pero completamente funcional en memoria.
// No apta para producción, pero ideal para pruebas complejas sin servidor externo.
// ============================================================================
class FakeServicioListaNegraEnMemoria : public IServicioListaNegra {
private:
    std::unordered_set<std::string> contrasenasComprometidas;

public:
    void agregarContrasenaVulnerada(const std::string& pass) {
        contrasenasComprometidas.insert(pass);
    }

    bool estaEnListaNegra(const std::string& password) override {
        return contrasenasComprometidas.find(password) != contrasenasComprometidas.end();
    }
};

TEST(DoblesPrueba, UsoDeFake) {
    FakeServicioListaNegraEnMemoria fakeDB;
    fakeDB.agregarContrasenaVulnerada("Admin1234");
    fakeDB.agregarContrasenaVulnerada("Password123");

    ValidadorSeguridad validador(&fakeDB);

    // Rechaza las que están registradas en el fake
    EXPECT_FALSE(validador.esValida("Admin1234"));
    EXPECT_FALSE(validador.esValida("Password123"));

    // Acepta una válida que no está en la base de datos en memoria
    EXPECT_TRUE(validador.esValida("ClaveFuerte2026"));
}
