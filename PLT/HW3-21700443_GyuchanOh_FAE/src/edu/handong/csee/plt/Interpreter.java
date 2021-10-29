package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.AST;
import edu.handong.csee.plt.ast.Add;
import edu.handong.csee.plt.ast.App;
import edu.handong.csee.plt.ast.Fun;
import edu.handong.csee.plt.ast.Id;
import edu.handong.csee.plt.ast.Sub;
import edu.handong.csee.plt.defrdSub.Asub;
import edu.handong.csee.plt.defrdSub.DefrdSub;
import edu.handong.csee.plt.value.ClosureV;
import edu.handong.csee.plt.value.NumV;
import edu.handong.csee.plt.ast.Num;

public class Interpreter {

	public String interp(AST ast, DefrdSub ds) {
		
		if(ast instanceof Num) {
			Num n = (Num)ast;
			return n.getStrNum();
			// return new NumV(n.getStrNum()).getASTCode();
		}
		
		if(ast instanceof Add) {
			Add add = (Add)ast;
			return "" + (Integer.toString(Integer.parseInt(interp(add.getLhs(), ds)) + Integer.parseInt(interp(add.getRhs(), ds))));
		}

		if(ast instanceof Sub) {
			Sub sub = (Sub)ast;
			return "" + (Integer.toString(Integer.parseInt(interp(sub.getLhs(), ds)) - Integer.parseInt(interp(sub.getRhs(), ds))));
		}
		
		if(ast instanceof Id) {
			Id id = (Id)ast;
			
			return "" + new Lookup().lookup(id.getStrName(), ds);
		}

		// if(ast instanceof ClosureV) {
		// 	ClosureV cv = (ClosureV)ast;

		// 	return "" + interp(cv.getBody(), ds);
		// }
		
		if(ast instanceof Fun) {
			Fun fun = (Fun)ast;

			return "" + new ClosureV(fun.getParam(), fun.getBody(), ds).getASTCode();
		}
		
		if(ast instanceof App) {
			App app = (App)ast;

			ClosureV f_val = new ClosureV(interp(app.getF(), ds), app.getF(), ds);
			ClosureV a_val = new ClosureV(interp(app.getA(), ds), app.getF(), ds);

			return "" + interp(f_val.getBody(), new Asub(f_val.getParam(), a_val, f_val.getDefrdSub()));
		}

		return null;
	}
}