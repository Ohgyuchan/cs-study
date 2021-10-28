package edu.handong.csee.plt.defrdSub;

import edu.handong.csee.plt.value.Value;

public class Asub extends DefrdSub{
    String i = "";
    Value v = new Value();
    DefrdSub saved = new DefrdSub();

	public Asub(String i, Value v, DefrdSub saved) {
		this.i = i;
        this.v = v;
        this.saved = saved;
	}
	
	public String getStrName() {
		return i;
	}

	public Value getV() {
		return v;
	}
    
	public DefrdSub getDefrdSub() {
		return saved;
	}
	
    public String getASTCode() {
		return "(Asub " + i + " " + v.getASTCode() +  " " + saved.getASTCode() + ")";
	}
}
