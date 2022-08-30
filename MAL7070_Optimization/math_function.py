from cmath import atan
import math
def f_x(x):
    z=(1.5*x/pow(1+pow(x,2),2))-(0.65*math.atan(1/x))+(0.65*x/(1+pow(x,2)))
    return z
def f__x(x):
    z=(2.8-3.2*pow(x,2))/pow(1+pow(x,2),3)
    return z
def lamb(l,f1,f2):
    return (l-(f1/f2))
if __name__=="__main__":
    e=float(input("enter value of epsilon\n"))
    l=float(input("enter value of lambda\n"))
    i=1
    while(math.fabs(f_x(l))>e):
        print("iteration:  ",i,'\n')
        i+=1
        f1=f_x(l)
        f2=f__x(l)
        l=lamb(l,f1,f2)
        print("f_x=",f1,'\n')
        print("f__x=",f2,'\n')
        print("lambda=",l,'\n')
        print(f_x(l))
        print("|f'(x)|=",math.fabs(f_x(l)),'\n')
        print("----------------------\n")