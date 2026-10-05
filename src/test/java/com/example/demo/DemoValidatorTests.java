package com.example.demo;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

public class DemoValidatorTests {

	@Test
	void RejectMinor8CharLenght() {
		assertFalse(DemoValidator.IsValid("Abc123"));
	}
	
	@Test
	void RejectNoDigit() {
		assertFalse(DemoValidator.IsValid("Abcdefgh"));
	}

	@Test 
	void RejectNoUpperCase() {
		assertFalse(DemoValidator.IsValid("abcdef1234"));
	}

	@Test 
	void AcceptValidPsw() {
		assertTrue(DemoValidator.IsValid("Abcdef12345"));
	}
}
