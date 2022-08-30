from google.colab import drive
drive.mount('/content/gdrive', force_remount=True)

input_dir = "/content/gdrive/MyDrive/CSL _7550-Machine _Learning/Gurumukhi"
import numpy as np
import os
from sklearn.svm import SVC
import cv2
train_dir = os.path.join(input_dir, "train")
val_dir = os.path.join(input_dir, "val")
def get_dataset(dataset_dir): 
    train_x = [] 
    train_y = []
    directories=os.listdir(dataset_dir)
    for dir in directories:
      for file in os.scandir(os.path.join(dataset_dir,dir)):
        img_path=os.path.join(os.path.join(dataset_dir,dir),file)
        img=cv2.cvtColor(cv2.imread(img_path),cv2.COLOR_BGR2GRAY)
        img=np.array(img)
        train_x.append(img.flatten())
        train_y.append(dir)
    train_x = np.array(train_x)
    train_y = np.array(train_y)
    return train_x, train_y
X_train, y_train = get_dataset(train_dir)
print(X_train.shape)
print(y_train.shape)
X_val, y_val = get_dataset(val_dir)
print(X_val.shape)
print(y_val.shape)
linear_svc = SVC(kernel='linear')
linear_svc.fit(X_train, y_train)
accuracy_linear = linear_svc.score(X_val, y_val)
print("Linear SVM Accuracy: ", accuracy_linear * 100, "%")
poly_svc = SVC(kernel='poly')
poly_svc.fit(X_train, y_train)
accuracy_poly = poly_svc.score(X_val, y_val)
print("Polynomial SVM Accuracy: " , accuracy_poly * 100, "%")
rbf_svc = SVC(kernel='rbf')
rbf_svc.fit(X_train, y_train)
accuracy_rbf = rbf_svc.score(X_val, y_val)
print("RBF SVM Accuracy: " , accuracy_rbf * 100 , "%")