#include <gtest/gtest.h>
#include "validador.h"

TEST(ValidadorPassword, RechazaMenorA8Caracteres) {
    EXPECT_FALSE(es_valida("Abc123"));
}

TEST(ValidadorPassword, RechazaSinDigito) {
    EXPECT_FALSE(es_valida("Abcdefgh"));
}

TEST(ValidadorPassword, RechazaSinMayuscula) {
    EXPECT_FALSE(es_valida("abc12345"));
}

TEST(ValidadorPassword, AceptaPasswordValida) {
    EXPECT_TRUE(es_valida("Abcd1234"));
}
