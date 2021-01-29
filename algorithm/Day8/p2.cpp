class Solution {
public:
    int romanToInt(string s) {
        int res = 0;
        map<char,int> map;
        map.insert('I',1);
        map.insert('V',5);
        map.insert('X',10);
        map.insert('L',50);
        map.insert('C',100);
        map.insert('D',500);
        map.insert('M',1000);
        res += map.get(s.charAt(0));
        for(int i=1;i<s.length();i++){
            int cur = map.get(s.charAt(i));
            int pre = map.get(s.charAt(i-1));
            if (pre<cur) res -= pre*2;
            res += cur;
        }
        return res;
    }
};
