from numpy import *
from scipy.optimize import *
# code for penalty function method
# min f(x)=-x1-x2
# s. t. h(x):1-x1^2-x2^2=0
def pen(x):
    # define objective function of unconstrained problem
    # min f(x)+mu h(x)^2
    return -x[0]-x[1]+mu*pow(1-pow(x[0],2)-pow(x[1],2),2)
def jac_pen(x):
    #gradient of above function
    return(array([-1-4*mu*x[0]*(1-pow(x[0],2)-pow(x[1],2)),-1-4*mu*x[1]*(1-pow(x[0],2)-pow(x[1],2))]))
x0,eps,tol,mu,beta,iter1=array([1.0,1.0]),pow(10,-5),1,0.1,10,0 #initialization
while (tol>eps)and(iter1<100):
    res = minimize(pen, x0, method='BFGS',jac=jac_pen,options={'disp': False})# solve unconstrained problem
    x0,h=res.x,1-pow(x0[0],2)-pow(x0[1],2) #updates
    print('h=',h)
    tol,mu,iter1=mu*pow(h,2),mu*beta,iter1+1
    print('tol=',tol)
print('*************************************')
print('optimal solution=',x0)
print('Total no of iteration',iter1)