package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.AST;
import edu.handong.csee.plt.ast.Asub;
import edu.handong.csee.plt.ast.MtSub;

public class Lookup {
    public AST lookup(String name, AST ds) {
		if(ds instanceof MtSub) {
            System.out.println("free identifier");
            System.exit(0);
        }
        
        if(ds instanceof Asub) {
            Asub aSub = (Asub)ds;

            if(aSub.getI() == name) {
                return aSub.getV();
            } else {
                return (lookup(name, aSub.getDefrdSub()));    
            }
        }
        

		return null;
        
	}
}
