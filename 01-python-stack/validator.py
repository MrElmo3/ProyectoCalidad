import re


def es_valida(password: str) -> bool:
    if len(password) < 8:
        return False
    return bool(re.search(r"\d", password)) and bool(re.search(r"[A-Z]", password))