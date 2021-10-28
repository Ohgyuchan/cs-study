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
			return ((Num)ast).getStrNum();
		}
		
		if(ast instanceof Add) {
			Add add = (Add)ast;
			return "" + new NumV(Integer.toString(Integer.parseInt(interp(add.getLhs(), ds)) + Integer.parseInt(interp(add.getRhs(), ds)))).getASTCode();
		}

		if(ast instanceof Sub) {
			Sub sub = (Sub)ast;
			return "" + new NumV(Integer.toString(Integer.parseInt(interp(sub.getLhs(), ds)) - Integer.parseInt(interp(sub.getRhs(), ds)))).getASTCode();
		}
		
		if(ast instanceof Id) {
			Id id = (Id)ast;
			Lookup lookUp = new Lookup();
			return lookUp.lookup(id.getStrName(), ds);
		}

		if(ast instanceof Fun) {
			Fun fun = (Fun)ast;

			return "" + new ClosureV(fun.getParam(), fun.getBody(), ds).getASTCode();
		}

		if(ast instanceof App) {
			App app = (App)ast;
			
			String f_val = interp(app.getF(), ds);
			ClosureV a_val = new ClosureV(interp(app.getF(), ds), app.getA(), ds);

			return "" + interp(ast, new Asub(f_val, a_val, ds));
		}

		return null;
	}
}
