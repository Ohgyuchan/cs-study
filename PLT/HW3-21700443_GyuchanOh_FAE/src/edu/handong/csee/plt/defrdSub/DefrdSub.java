package edu.handong.csee.plt.defrdSub;

public class DefrdSub {
	
	public String getASTCode() {
		String astCode="";
		if(this instanceof MtSub)
			astCode = ((MtSub)this).getASTCode();
		
		if(this instanceof Asub)
			astCode = ((Asub)this).getASTCode();
		
		return astCode;
	}
}
