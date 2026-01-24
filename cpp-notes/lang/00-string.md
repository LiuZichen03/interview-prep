what is string?
->char + array

其结构
string s = "HI!"
->H I ! /0 ->三个字符占四位
->strlen(s) -> 判断s[i] != /0;

string word[0] //字符串数组->本质二维数组
word[0] = "HI!";
-> char a = word[0][0]; //a = H

int main(int argc,string argv[])
{
}
->编译时可以输入字符串 其中 argv[0]保存的是文件名     
