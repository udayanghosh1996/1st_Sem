import numpy as np
import random
import pandas as pd
np.random.seed(42)
a_data=np.random.rand(3)
a_data=a_data/sum(a_data)
A_dataframe=pd.DataFrame([a_data], columns=['a1','a2','a3'])
A_dataframe
np.random.seed(87)
b_data=np.random.rand(2)
b_data=b_data/sum(b_data)
B_dataframe=pd.DataFrame([b_data], columns=['b1','b2'])
B_dataframe
np.random.seed(32)
c_data=np.random.rand(2)
c_data=c_data/sum(c_data)
C_dataframe=pd.DataFrame([c_data], columns=['c1','c2'])
C_dataframe
np.random.seed(142)
m_data=np.random.rand(12,3)
m_data=m_data/m_data.sum(axis=1)[:,None]
indexs=['a1b1c1','a1b1c2','a1b2c1','a1b2c2','a2b1c1','a2b1c2','a2b2c1','a2b2c2','a3b1c1','a3b1c2','a3b2c1','a3b2c2']
M_dataframe=pd.DataFrame(m_data, columns=['m1','m2','m3'], index=indexs)
M_dataframe
np.random.seed(98)
x_data=np.random.rand(3,2)
x_data=x_data/x_data.sum(axis=1)[:,None]
X_dataframe=pd.DataFrame(x_data, columns=['x1','x2'],index=['m1','m2','m3'] )
X_dataframe
np.random.seed(358)
y_data=np.random.rand(3,3)
y_data=y_data/y_data.sum(axis=1)[:,None]
Y_dataframe=pd.DataFrame(y_data, columns=['y1','y2','y3'], index=['m1','m2','m3'])
Y_dataframe
x2_y3=np.array(X_dataframe['x2']*Y_dataframe['y3']).reshape(1,3)
X2_Y3_dataframe=pd.DataFrame(x2_y3,columns=['m1','m2','m3'], index=['x2,y3'])
X2_Y3_dataframe
a1,a2,a3=M_dataframe[0:4],M_dataframe[4:8],M_dataframe[8:12]
a1_x2_y3_data=0
for i in range (0,4):
    a1_x2_y3_data+=a1.iloc[i]*X2_Y3_dataframe*np.array(B_dataframe)[0,int(i/2)]*np.array(C_dataframe)[0,i%2]
a1_x2_y3_data
a2_x2_y3_data=0
for i in range (0,4):
    a2_x2_y3_data+=a2.iloc[i]*X2_Y3_dataframe*np.array(B_dataframe)[0,int(i/2)]*np.array(C_dataframe)[0,i%2]
a2_x2_y3_data
a3_x2_y3_data=0
for i in range (0,4):
    a3_x2_y3_data+=a3.iloc[i]*X2_Y3_dataframe*np.array(B_dataframe)[0,int(i/2)]*np.array(C_dataframe)[0,i%2]
a3_x2_y3_data
print("P(a1|x2,y3)=",np.sum(np.array(a1_x2_y3_data)))
print("P(a2|x2,y3)=",np.sum(np.array(a2_x2_y3_data)))
print("P(a3|x2,y3)=",np.sum(np.array(a3_x2_y3_data)))