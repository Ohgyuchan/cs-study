package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.AST;
import edu.handong.csee.plt.ast.Add;
import edu.handong.csee.plt.ast.Id;
import edu.handong.csee.plt.ast.Sub;
import edu.handong.csee.plt.ast.Num;

public class Substitution {

	public AST subst(AST ast, AST idtf, String val) {
		
		if(ast instanceof Num) {
			return ast;
		}
		
		if(ast instanceof Add) {
			Add add = (Add)ast;
			return new Add(subst(add.getLhs(), idtf, val), subst(add.getRhs(), idtf, val));
		}

		if(ast instanceof Sub) {
			Sub sub = (Sub)ast;
			return new Sub(subst(sub.getLhs(), idtf, val), subst(sub.getRhs(),idtf,val));
		}

		
		
		
		if(ast instanceof Id) {
			if(ast instanceof Id && idtf instanceof Id) {
				return new Num(val);
			} else {
				return ast;
			}
		}

		return null;
	}
}
