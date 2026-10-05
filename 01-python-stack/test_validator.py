from validator import es_valida

def test_rechaza_menor_a_8_caracteres():
    assert es_valida("Abc123") is False