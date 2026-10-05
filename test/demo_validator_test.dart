import 'package:flutter_test/flutter_test.dart';

import 'package:demo_test/demo_validator.dart';

void main() {
  test('reject passwords less than 8 characters', () {
    expect(isValid('Abc123'), isFalse);
  });

  test('reject passwords without a number', () {
    expect(isValid('Abcdefgh'), isFalse);
  });

  test('reject passwords without an upper case', () {
    expect(isValid('abc12345'), isFalse);
  });

  test('acepta una contraseña válida', () {
    expect(isValid('Abcd1234'), isTrue);
  });
}