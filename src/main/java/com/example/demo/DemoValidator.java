package com.example.demo;

import java.util.regex.Pattern;

public class DemoValidator {
	public static boolean IsValid(String psw) {

		if(psw.length() < 8) return false;
		return 
			Pattern.compile("\\d").matcher(psw).find() &&
			Pattern.compile("[A-Z]").matcher(psw).find();
	}
}
