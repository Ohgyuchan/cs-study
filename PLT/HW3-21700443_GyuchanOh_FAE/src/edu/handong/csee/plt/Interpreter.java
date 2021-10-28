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
			String n = ((Num)ast).getStrNum();
			System.out.println(new Num(n).getASTCode());
			return new Num(n).getASTCode();
		}
		
		if(ast instanceof Add) {
			Add add = (Add)ast;
			return "" + (Integer.parseInt(interp(add.getLhs(), ds)) + Integer.parseInt(interp(add.getRhs(), ds)));
		}

		if(ast instanceof Sub) {
			Sub sub = (Sub)ast;
			return "" + (Integer.parseInt(interp(sub.getLhs(), ds)) - Integer.parseInt(interp(sub.getRhs(), ds)));
		}
		
		if(ast instanceof Id) {
			Id id = (Id)ast;
			Lookup lookUp = new Lookup();
			System.out.println(lookUp.lookup(id.getStrName(), ds));
			System.exit(0);
		}

		if(ast instanceof Fun) {
			Fun fun = (Fun)ast;
			System.out.println("" + new ClosureV(fun.getParam(), fun.getBody(), ds).getASTCode());
			return "" + new ClosureV(fun.getParam(), fun.getBody(), ds);
		}

		if(ast instanceof App) {
			App app = (App)ast;
			
			ClosureV f_val = new ClosureV(interp(app.getF(), ds), ast, ds);
			NumV a_val = new NumV(interp(app.getA(), ds));

			// return "" + interp(f_val.getBody(), new Asub(f_val.getParam(), a_val, f_val.getDefrdSub()));
		}

		return null;
	}
}
