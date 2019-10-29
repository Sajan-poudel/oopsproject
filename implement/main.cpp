#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
using namespace std;
class constraints;
class stack
{
    char c;
    int n;
    int x;

public:
    int top1;
    int top2;
    stack()
    {
        top1 = 0;
        top2 = 0;
    }
    virtual void push(int) = 0;
    virtual void push(char) = 0;
    void impl(string str)
    {
        // cout<<str.length()<<endl;
        n = 1;
        for (int i = 0; i < str.length(); i++)
        {
            c = str[i];
            if (isalnum(c))
            {
                if (isdigit(c))
                {
                    x = (c - '0');
                    while (isdigit(str[++i]))
                    {
                        x = x * 10 + (int)(str[i] - '0');
                    }
                    // val[top1++] = x * n;
                    push(x * n);
                    i--;
                }
                else
                {
                    // var[top2++] = c;
                    push(c);
                }
            }

            else if (c == '-')
            {
                n = -1;
            }
            else
            {
                n = 1;
            }
        }
    }
};

class Objfunc : public stack
{
public:
    int val[10];
    char var[10];
    void push(int x)
    {
        val[top1++] = x;
    }
    void push(char c)
    {
        var[top2++] = c;
    }
    void resize(int x)
    {
        for (int i = 0; i < x; i++)
        {
            val[top1++] = 0;
        }
    }

    friend int arraydec(int *, int *, Objfunc, constraints);
};

class constraints : public stack
{
    int row;

public:
    constraints()
    {
        top1 = 1;
    }
    int **val;
    ~constraints()
    {
        free(val);
    }
    void setsize(int a, int b)
    {
        string exp1;
        val = new int *[a];
        for (int i = 0; i < a; i++)
        {
            val[i] = new int[b];
        }
        for (int i = 0; i < a; i++)
        {
            top1 = 1;
            row = i;
            cout << "Enter the  " << i + 1 << "  expression" << endl;
            cin >> exp1;
            impl(exp1);
        }
    }
    void resize(int a, int b)
    {
        int j;
        for (int i = 0, temp; i < a; i++)
        {
            val[i][0] = 0;
            temp = val[i][top1 - 1];
            for (j = b + 1; j < b + 1 + a; j++)
            {
                if (i == j - (b + 1))
                    val[i][j] = 1;
                else
                {
                    val[i][j] = 0;
                }
            }
            val[i][j] = temp;
        }
        top1 = j + 1;
    }
    void push(int x)
    {
        val[row][top1++] = x;
    }
    void push(char c)
    {
    }

    void computeRatio(int *x, int ind, int size){
        // cout<<top1<<endl;
        // cout<<ind<<endl;
        for(int i = 0; i<size; i++){
            val[i][top1] = val[i][top1-1] / val[i][ind];
            // cout<<val[i][top1];
        }
        // cout<<endl;
    }

    friend int arraydec(int *, int *, Objfunc, constraints);
};

int arraydec(int *x, int *y, Objfunc p, constraints q)
{
    int ind = 0;
    for (int a = 0, temp = 0; a < p.top1 + 1; a++)
    {
        for (int j = 0; j < p.top1 - p.top2; j++)
        {
            temp += q.val[j][0] * q.val[j][a + 1];
        }
        x[a] = temp;
        if (a < p.top1)
        {
            y[a] = p.val[a] - temp;
            temp = 0;
            ind = y[a] > y[ind] ? a : ind;
        }
    }
    return ind;
}

int main()
{
    Objfunc st;
    constraints co;
    string exp;
    int cons, *zj, *cj_zj, gre; //value -> no. of constraints
    cout << "enter the expression: ";
    cin >> exp;
    st.impl(exp);
    cout << exp << endl;
    // for (int i = 0; i < st.top2; i++)
    //     cout << st.var[i] << "\t";
    // cout << endl;
    // cout << st.var << endl;
    // cout << st.top2 << endl;

    cout << "Enter the number of constraints expression: ";
    cin >> cons;
    st.resize(cons);
    // string exp1[cons];
    co.setsize(cons, st.top2 + cons + 3);
    co.resize(cons, st.top2);
    zj = new int[st.top1 + 1];
    cj_zj = new int[st.top1];
    gre = arraydec(zj, cj_zj, st, co);
    co.computeRatio(cj_zj, gre+1, cons);
    for (int i = 0; i < st.top1; i++)
        cout << st.val[i] << "\t";
    cout << endl;
    for (int i = 0; i < cons; i++)
    {
        for (int j = 0; j < co.top1 + 1; j++)
        {
            cout << co.val[i][j] << "\t";
        }
        cout << endl;
    }

    cout << endl;
    for (int i = 0; i < st.top1 + 1; i++)
        cout << zj[i] << "\t";
    cout << endl;
    for (int i = 0; i < st.top1; i++)
        cout << cj_zj[i] << "\t";
    cout << endl;
    cout<<co.top1<<endl;
    return 0;
}