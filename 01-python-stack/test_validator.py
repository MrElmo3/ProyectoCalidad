from unittest.mock import Mock

from validator import es_valida


def test_rechaza_menor_a_8_caracteres():
    assert es_valida("Abc123") is False


def test_rechaza_sin_digito():
    assert es_valida("Abcdefgh") is False


def test_rechaza_sin_mayuscula():
    assert es_valida("abc12345") is False


def test_acepta_password_valida():
    assert es_valida("Abcd1234") is True


def test_rechaza_password_filtrada():
    servicio_filtradas = Mock()
    servicio_filtradas.esta_filtrada.return_value = True

    resultado = es_valida("Abcd1234", servicio_filtradas)

    assert resultado is False
    servicio_filtradas.esta_filtrada.assert_called_once_with("Abcd1234")


def test_acepta_password_no_filtrada():
    servicio_filtradas = Mock()
    servicio_filtradas.esta_filtrada.return_value = False

    assert es_valida("Abcd1234", servicio_filtradas) is True