package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.AST;
import edu.handong.csee.plt.ast.Add;
import edu.handong.csee.plt.ast.App;
import edu.handong.csee.plt.ast.Asub;
import edu.handong.csee.plt.ast.ClosureV;
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
			return new NumV(Integer.toString(Integer.parseInt( ((NumV)interp(add.getLhs(), ds)).getStrNumV() ) + Integer.parseInt( ((NumV)interp(add.getRhs(), ds)).getStrNumV() )));
		}

		if(ast instanceof Sub) {
			Sub sub = (Sub)ast;
			return new NumV(Integer.toString(Integer.parseInt( ((NumV)interp(sub.getLhs(), ds)).getStrNumV() ) - Integer.parseInt( ((NumV)interp(sub.getRhs(), ds)).getStrNumV() )));
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
			
			ClosureV f_val = (ClosureV) interp(app.getF(), ds);
			AST a_val = interp(app.getA(), ds);
			
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
}