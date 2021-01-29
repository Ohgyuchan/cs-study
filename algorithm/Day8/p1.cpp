class Solution {
public:
    string addBinary(string a, string b) {
        /*
        1. reverse given strings
        2. add each index using loop, insert each value to 'result'
        3. reverse result again
        4. return it
        */
        string result ="";
        int carry = 0;
        int i = 0, sum = 0;

        reverse(a.begin(), a.end());  // reverse
        reverse(b.begin(), b.end());  // reverse

        while(i < a.size() || i < b.size()) { // Iterate work it if i is smaller than size of a or b

            sum = carry;

            if(i < a.size()) { sum += a[i]-'0'; } //if 'i' is smaller than size of 'a' sum + a[i]
            if(i < b.size()) { sum += b[i]-'0'; } //if 'i' is smaller than size of 'b' sum + b[i]

            ifsum == 0) { carry = 0; result += '0'; } // if a="0", b="0" sum = 0, carry = 0, result += 0
            else if(sum == 1) { carry = 0; result += '1'; } // if "1" + "0" sum = "0" carry = 0 result += 1
            else if(sum == 2) { carry = 1; result += '0'; } // "1" + "1", sum == "2", carry == 1 result += 0
            else { carry = 1; result += '1'; } // "1" + "1" + "1(carry)" sum > 2, carry == 1 result += 1

            i++;

        }

        if(carry) result += '1'; // if carry has value result += 1
        reverse(result.begin(), result.end()); // reverse result

        return result;
    }
};
