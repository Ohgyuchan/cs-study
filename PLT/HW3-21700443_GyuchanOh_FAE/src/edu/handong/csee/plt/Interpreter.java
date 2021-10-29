package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.AST;
import edu.handong.csee.plt.ast.Add;
import edu.handong.csee.plt.ast.App;
import edu.handong.csee.plt.ast.Asub;
import edu.handong.csee.plt.ast.ClosureV;
import edu.handong.csee.plt.ast.Fun;
import edu.handong.csee.plt.ast.Id;
import edu.handong.csee.plt.ast.Sub;
import edu.handong.csee.plt.ast.Num;
import edu.handong.csee.plt.ast.NumV;

public class Interpreter {

	public AST interp(AST ast, AST ds) {
		
		if(ast instanceof Num) {
			Num n = (Num)ast;
			
			return new NumV(n.getStrNum());
		}
		
		if(ast instanceof Add) {
			Add add = (Add)ast;
			return new NumV(Integer.toString(Integer.parseInt(interp(add.getLhs(), ds).getASTCode()) + Integer.parseInt(interp(add.getRhs(), ds).getASTCode())));
		}

		if(ast instanceof Sub) {
			Sub sub = (Sub)ast;
			return new NumV(Integer.toString(Integer.parseInt(interp(sub.getLhs(), ds).getASTCode()) - Integer.parseInt(interp(sub.getRhs(), ds).getASTCode())));
		}
		
		if(ast instanceof Id) {
			Id id = (Id)ast;
			
			return new Lookup().lookup(id.getStrName(), ds);
		}

		if(ast instanceof Fun) {
			Fun fun = (Fun)ast;

			return new ClosureV(fun.getParam(), fun.getBody(), ds);
		}
		
		if(ast instanceof App) {
			App app = (App)ast;

			AST f_ast = interp(app.getF(), ds);
			AST a_ast = interp(app.getA(), ds);

			System.out.println(ast.getASTCode());
			System.out.println(f_ast.getASTCode());
			System.out.println(a_ast.getASTCode());
			
			Fun f_fun = (Fun)f_ast;
			Fun a_fun = (Fun)a_ast;
			
			ClosureV f_val = new ClosureV(f_fun.getParam(), f_fun.getBody(), ds);
			ClosureV a_val = new ClosureV(a_fun.getParam(), a_fun.getBody(), ds);
			
			return interp(f_val.getBody(), new Asub(f_val.getParam(), a_val, f_val.getDefrdSub()));
		}

		return null;
	}
}