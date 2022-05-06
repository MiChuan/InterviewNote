class Solution {
public:
    bool isNumeric(string s) {
        //A[.[B]][e|EC]//.B[e|EC]
        //A带符号的整数；B无符号整数，e后面必有一个（有符号）整数，小数点前后必有数字，空格只能出现在字符串首尾；
        int flag=0;//用来标记是否检测到数字
        //空，直接返回
        if(s=="") return false;
        //检测字符串之前是否有空格
        while(s[0]==' ') s=s.substr(1);
        //遇到正负号，向后移 
        if(s[0]=='+'||s[0]=='-') s=s.substr(1);
        //检测小数点前是否有数字，有的话后移，并标记
        while((s[0]>='0') && (s[0]<='9')){
            s=s.substr(1);flag=1; 
        } 
        //如果后面是.,那就向后移，有.就要判断后面有没有数字
        if(s[0]=='.'){
            s=s.substr(1);
            while((s[0]>='0') && (s[0]<='9')){
                s=s.substr(1);flag=1; 
            }
        }
        //判断前半部分有没有数字
        if(flag==0) return false;
        flag=0;
        //接下来判断是有e|E;与上面是串联关系，所以用if不用else
        //如果存在e|E，那就一定要判断，它后面是否跟了数字
        if(s[0]=='e'||s[0]=='E'){
            s=s.substr(1);
            //判断有没有正负号
            if(s[0]=='+'||s[0]=='-') s=s.substr(1);           
            //判断整数
            while((s[0]>='0') && (s[0]<='9')){
                s=s.substr(1);flag=1; 
            }
            //如果有e没有数字，那就出错了
            if(flag==0) return false;     
        }
        //判断空格结尾
        while(s[0]==' ') s=s.substr(1);
        //如果结束了那就是true，如果还有其他字母，那就false
        if(s=="") return true;
        return false;
    }
};