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
    virtual void push(double) = 0;
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
                    push((double)x * n);
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
    double val[10];
    char var[10];
    int op;
    void push(double x)
    {
        val[top1++] = x * op;
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

    friend int arraydec(double *, double *, Objfunc, constraints);
    friend void print(Objfunc, constraints, int, int, double *, double *);
};

class constraints : public stack
{
    int row;

public:
    constraints()
    {
        top1 = 1;
    }
    double **val;
    ~constraints()
    {
        // free(val);
    }
    void setsize(int a, int b)
    {
        string exp1;
        val = new double *[a];
        for (int i = 0; i < a; i++)
        {
            val[i] = new double[b];
        }
        for (int i = 0; i < a; i++)
        {
            top1 = 1;
            row = i;
            cout << "Enter the  " << i + 1 << "  expression: " << endl;
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

    void compute(int ind, int min, int row)
    {
        double div;
        // cout << top1 << endl;
        div = val[min][ind];
        for (int j = 1; j < top1; j++)
        {
            val[min][j] = val[min][j] / div;
            // cout << val[min][j] << "\t";
        }
        // cout << endl;
        for (int i = 0; i < row; i++)
        {
            div = val[i][ind];
            for (int j = 1; j < top1; j++)
            {
                if (i == min)
                {
                    break;
                }
                val[i][j] = val[i][j] - val[min][j] * div;
                // cout << val[i][j] << "\t";
            }
            // cout << endl;
        }
    }
    void push(double x)
    {
        val[row][top1++] = x;
    }
    void push(char c)
    {
    }

    int computeRatio(int ind, int size)
    {
        // cout<<top1<<endl;
        // cout<<ind<<endl;
        int min = 0;
        // cout<<top1<<"\t"<<ind<<"\t"<<size<<endl;
        for (int i = 0; i < size; i++)
        {
            // cout << "hey i am here\n";
            // cout << val[i][top1 - 1] << "\t" << val[i][ind] << endl;
            if (val[i][ind] == 0)
            {
                val[i][top1] = -1;
            }
            else
            {
                val[i][top1] = val[i][top1 - 1] / val[i][ind];
            }
            // cout << "this is done\n";
            min = ((val[i][top1] < val[min][top1]) && (val[i][top1] > 0)) ? i : min;
            min = (val[min][top1] < 0) ? i : min;
            // cout<<val[i][top1];
        }
        // cout << min << endl;
        // cout << "compute done\n";
        return min;
    }

    friend int arraydec(double *, double *, Objfunc, constraints);
    friend void print(Objfunc, constraints, int, int, double *, double *);
};

int arraydec(double *x, double *y, Objfunc p, constraints q)
{
    int ind = 0;
    double temp = 0;
    for (int a = 0; a < p.top1 + 1; a++)
    {
        for (int j = 0; j < p.top1 - p.top2; j++)
        {
            temp += q.val[j][a + 1] * q.val[j][0];
        }
        x[a] = temp;
        if (a < p.top1)
        {
            y[a] = p.val[a] - temp;
            temp = 0;
            ind = y[a] > y[ind] ? a : ind;
        }
    }
    // cout << "arraay dec done\n";
    return ind;
}

void print(Objfunc st, constraints co, int gre, int min, int cons, double *zj, double *cj_zj)
{
    for (int i = 0; i < 15; i++)
    {
        cout << " ";
    }
    cout << "\tCJ\t";
    for (int i = 0; i < st.top1; i++)
        cout << st.val[i] << "\t";
    cout << endl;
    cout << "Basic variables\t"
         << "CB\t";
    int incre = 1;
    for (int i = 0; i < st.top1; i++)
    {
        if (i < st.top2)
        {
            cout << st.var[i] << "\t";
        }
        else
        {
            cout << "S" << incre << "\t";
            incre++;
        }
    }
    cout << "XB\tRatio\n";
    for (int i = 0; i < cons; i++)
    {
        cout << "             S" << (i + 1) << "\t";
        for (int j = 0; j < co.top1 + 1; j++)
        {
            cout << co.val[i][j] << "\t";
        }
        cout << endl;
    }

    cout << endl;
    for (int i = 0; i < 13; i++)
        cout << " ";
    cout << "\tZj\t";
    for (int i = 0; i < st.top1 + 1; i++)
        cout << zj[i] << "\t";
    cout << endl;
    // for(int i=0; i<5; i++)
    cout << " Cj-Zj ";
    for (int i = 0; i < 5; i++)
        cout << " ";
    cout << "\t\t";
    for (int i = 0; i < st.top1; i++)
        cout << cj_zj[i] << "\t";
    cout << endl;
    if (cj_zj[gre] > 0)
    {
        cout << co.val[min][gre + 1] << " is the pivot element so making pivot element as 1 and rest of the element in pivot column as 0\n";
    }
    cout << endl;
}

int main()
{
    // char *c = "basic variable";
    Objfunc st;
    constraints co;
    string exp;
    int cons, gre, min, ch = 0; //value -> no. of constraints
    double *zj, *cj_zj;
    cout << "\nenter the following operation to be done: \n";
    cout << "1. To maximize\n";
    cout << "2. To minimize\n";
    cout << "3. exit\n>>>>>>>";
    cin >> ch;
    while (ch != 3)
    {
        if (ch == 1)
        {
            st.op = 1;
        }
        else
        {
            st.op = -1;
        }
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
        zj = new double[st.top1 + 1];
        cj_zj = new double[st.top1];
        do
        {
            gre = arraydec(zj, cj_zj, st, co);
            min = co.computeRatio(gre + 1, cons);
            print(st, co, gre, min, cons, zj, cj_zj);
            // cout << co.top1 << endl;
            co.val[min][0] = st.val[gre];
            co.compute(gre + 1, min, cons);
        } while (cj_zj[gre] > 0);
        cout << "Since there is no positive value in Cj-Zj we conclude that ";
        ch==1?cout<<"Zmax": cout<<"Zmin ";
        cout<<" is: " << zj[st.top1] * st.op << endl;

        cout << "\nenter the following operation to be done: \n";
        cout << "1. To maximize\n";
        cout << "2. To minimize\n";
        cout << "3. exit\n>>>>>>>";
        cin >> ch;
    }
    return 0;
}