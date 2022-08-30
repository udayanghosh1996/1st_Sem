from scipy.optimize import minimize
import random
r=65
def constrain(x):
   return pow(pow(x[0],2)+x[1],2) 
def penalty(x):
    z=pow(pow(x[0],2)-r,2) + pow(pow(x[0],2)-2*x[1],2) + mu*constrain(x)
    return z
def differ(x):
    a0=4*x[0]*(pow(x[0],2)-r) + 4*x[0]*(pow(x[0],2)-2*x[1]) + 4*mu*x[0]*(pow(x[0],2)+x[1])
    a1=-4*(pow(x[0],2)-2*x[1]) +2*mu*(pow(x[0],2)+x[1])
    return [a0,a1]
x0=[random.random(),random.random()]
b=10
mu=0.1
maxiter=200
stop_criter=pow(10,-5)
tol=1
for i in range (1,maxiter):
    if tol<stop_criter:
        break
    sol=minimize(penalty,x0,method='BFGS', jac=differ)
    x0=sol.x
    h=constrain(x0)
    tol=mu*pow(h,2)
    mu*=b
    i+=1
print("points for minimized values: ",x0)
print('minimized value =',penalty(x0))