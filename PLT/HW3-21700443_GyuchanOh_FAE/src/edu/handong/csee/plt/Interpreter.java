package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.AST;
import edu.handong.csee.plt.ast.Add;
import edu.handong.csee.plt.ast.Id;
import edu.handong.csee.plt.ast.Sub;
import edu.handong.csee.plt.ast.Num;

public class Interpreter {

	public String interp(AST ast) {
		
		if(ast instanceof Num) {
			return ((Num)ast).getStrNum();
		}
		
		if(ast instanceof Add) {
			Add add = (Add)ast;
			return "" + (Integer.parseInt(interp(add.getLhs())) + Integer.parseInt(interp(add.getRhs())));
		}

		if(ast instanceof Sub) {
			Sub sub = (Sub)ast;
			return "" + (Integer.parseInt(interp(sub.getLhs())) - Integer.parseInt(interp(sub.getRhs())));
		}
		
		if(ast instanceof Id) {
			System.out.println("Free identifier");
			System.exit(0);
		}

		return null;
	}
}
