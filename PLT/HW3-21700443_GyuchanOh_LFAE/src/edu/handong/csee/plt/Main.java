package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.AST;
import edu.handong.csee.plt.ast.MtSub;

public class Main {
	
	static boolean onlyParser = false; // for -p option
	
	public static void main(String[] args) {
		
		String input = "";
		
		if(args[0].compareTo("-p") == 0) {
			input = args[1];
			onlyParser = true;
		} else {
			input = args[0];
		}
		
		// Parser
		Parser parser = new Parser();
		AST ast = parser.parse(input);
		
		if(ast == null) {
			System.out.println("Syntax Error!");
			System.exit(0);
		}
		
		if(onlyParser) {
			System.out.println(ast.getASTCode());
			return;
		}
		
		// interpreter
		Interpreter interpreter = new Interpreter();
		
		
		String result = interpreter.interp(ast, new MtSub()).getASTCode();
		System.out.println(result);
		
	}
}
