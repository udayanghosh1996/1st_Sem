import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA as pc
link="https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data"
dataset=pd.read_csv(link,header=None)
dataset.iloc[:,-1].replace(to_replace=dataset.iloc[:,-1].unique(), 
                             value= list(range(len(dataset.iloc[:,-1].unique()))), inplace=True)
data=dataset.to_numpy()
features=data[:,:4]
label=data[:,4]
class PCA:
    def __init__(self):
        pass
    def fit(self,features):
        cov_matrix=np.cov(features.T)
        eign_val,eign_vec=np.linalg.eig(cov_matrix)
        eign_vec=eign_vec.T
        eign_val=eign_val[np.flip(np.argsort(eign_val))]
        eign_vec=eign_vec[np.flip(np.argsort(eign_val))]
        self.eign_vec_comp=eign_vec[0:2]
    def transform(self,features):
        return np.dot(features,self.eign_vec_comp.T)
pca=PCA()
pca.fit(features)
projected=pca.transform(features)
x=projected[:,0]
y=projected[:,1]
plt.scatter(x,y,c=y, edgecolor="none")