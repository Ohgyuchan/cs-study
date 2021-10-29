package edu.handong.csee.plt.ast;

import edu.handong.csee.plt.value.ClosureV;
import edu.handong.csee.plt.value.NumV;

public class AST {
	
	public String getASTCode() {
		String astCode="";
		if(this instanceof Add)
			astCode = ((Add)this).getASTCode();

		if(this instanceof Sub)
			astCode = ((Sub)this).getASTCode();
		
		if(this instanceof Num)
			astCode = ((Num)this).getASTCode();
		
		if(this instanceof NumV)
			astCode = ((NumV)this).getASTCode();
		
		if(this instanceof ClosureV)
			astCode = ((ClosureV)this).getASTCode();

		return astCode;
	}
}

