bool isValid(String password) {
  if (password.length < 8) return false;
  final hasDigit = RegExp(r'\d').hasMatch(password);
  final hasUpperCase = RegExp(r'[A-Z]').hasMatch(password);
  return hasDigit && hasUpperCase;
}