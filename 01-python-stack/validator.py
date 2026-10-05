import re


def es_valida(password: str, servicio_filtradas=None) -> bool:
    if len(password) < 8:
        return False
    if not (re.search(r"\d", password) and re.search(r"[A-Z]", password)):
        return False
    if servicio_filtradas is not None and servicio_filtradas.esta_filtrada(password):
        return False
    return True