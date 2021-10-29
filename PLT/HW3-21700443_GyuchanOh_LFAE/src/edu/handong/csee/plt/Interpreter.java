package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.AST;
import edu.handong.csee.plt.ast.Add;
import edu.handong.csee.plt.ast.App;
import edu.handong.csee.plt.ast.Asub;
import edu.handong.csee.plt.ast.ClosureV;
import edu.handong.csee.plt.ast.ExprV;
import edu.handong.csee.plt.ast.Fun;
import edu.handong.csee.plt.ast.Id;
import edu.handong.csee.plt.ast.MtSub;
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
			
			// Num lhs = (Num)((ExprV)interp(add.getLhs(), ds)).getExpr();
			// AST lds = ((ExprV)interp(add.getLhs(), ds)).getDefrdSub();
			
			// Num rhs = (Num)((ExprV)interp(add.getRhs(), ds)).getExpr();
			// AST rds = ((ExprV)interp(add.getRhs(), ds)).getDefrdSub();
			
			return new NumV(Integer.toString(Integer.parseInt( ((NumV)strict(interp(add.getLhs(), ds))).getStrNumV() ) + Integer.parseInt( ((NumV)strict(interp(add.getRhs(), ds))).getStrNumV() )));
		}

		if(ast instanceof Sub) {
			Sub sub = (Sub)ast;
			
			// Num lhs = (Num)((ExprV)interp(sub.getLhs(), ds)).getExpr();
			// AST lds = ((ExprV)interp(sub.getLhs(), ds)).getDefrdSub();
			
			// Num rhs = (Num)((ExprV)interp(sub.getRhs(), ds)).getExpr();
			// AST rds = ((ExprV)interp(sub.getRhs(), ds)).getDefrdSub();

			return new NumV(Integer.toString(Integer.parseInt( ((NumV)strict(interp(sub.getLhs(), ds))).getStrNumV() ) - Integer.parseInt( ((NumV)strict(interp(sub.getRhs(), ds))).getStrNumV() )));
		}
		
		if(ast instanceof Id) {
			Id id = (Id)ast;
			
			return lookup(id.getStrName(), ds);
		}

		if(ast instanceof Fun) {
			Fun fun = (Fun)ast;

			return new ClosureV(fun.getParam(), fun.getBody(), ds);
		}
		
		if(ast instanceof App) {
			App app = (App)ast;
			
			ClosureV f_val = ((ClosureV) strict(interp(app.getF(), ds)));
			ExprV a_val = new ExprV(app.getA(), ds);
			
			return interp(f_val.getBody(), new Asub(f_val.getParam(), a_val, f_val.getDefrdSub()));
		}

		return null;
	}

	private AST lookup(String name, AST ds) {
		if(ds instanceof MtSub) {
            System.out.println("free identifier");
            System.exit(0);
        }
        
        if(ds instanceof Asub) {
            Asub aSub = (Asub)ds;

            if(aSub.getI().equals(name)) {
                return aSub.getV();
            } else {
                return (lookup(name, aSub.getDefrdSub()));    
            }
        }
		
		return null;
	}
	
	private AST strict(AST v) {
		if(v instanceof ExprV) {
			ExprV expr = (ExprV)v;
			
			return strict(interp(expr.getExpr(), expr.getDefrdSub()));
		
		} else {
			
			return v;
		}
	}
}