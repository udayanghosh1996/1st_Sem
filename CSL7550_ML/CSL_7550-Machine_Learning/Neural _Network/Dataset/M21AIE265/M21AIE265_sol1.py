import numpy as np
import torch
import torchvision
from time import time
from torchvision import datasets, transforms
from torch import nn, optim
import os
from torch.utils.data import DataLoader, dataloader
from torch import nn
from torch.autograd import Variable
import matplotlib.pyplot as plt
import cv2
import torch.nn.functional as func
from sklearn.svm import SVC
from sklearn.decomposition import PCA
device=torch.device('cuda' if torch.cuda.is_available() else 'cpu')
print(device)
transform=transforms.Compose([transforms.ToTensor(),transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])
root_dir=os.path.join(os.getcwd(),'cifar')
train_dataset = datasets.ImageFolder(os.path.join(root_dir,'train'), transform=transform)
test_dataset = datasets.ImageFolder(os.path.join(root_dir,'test'), transform=transform)
train_set, val_set = torch.utils.data.random_split(train_dataset, [25000, 5000])
train_loader = DataLoader(train_set, batch_size=64, shuffle=True)
#train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)
val_loader = DataLoader(val_set, batch_size=64, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=64, shuffle=True)
len(train_dataset)
dataiter = iter(train_loader)
images, labels = dataiter.next()
print(images.shape)
print(labels.shape)
class Cifar_Lin(nn.Module):
    def __init__(self):
        super(Cifar_Lin,self).__init__()
        self.layer1 = nn.Linear(3072,768)
        self.layer2 = nn.Linear(768,192)
        self.Final = nn.Linear(192,6)
        self.relu = nn.ReLU()
    def forward(self, data):
        mtx = torch.flatten(data, start_dim=1)
        mtx = self.layer1(mtx)
        mtx = self.relu(mtx)
        mtx = self.layer2(mtx)
        mtx = self.relu(mtx)
        mtx = self.Final(mtx)
        return mtx
criterion = nn.CrossEntropyLoss()
model = Cifar_Lin().to(device)
optimizer = optim.Adam(model.parameters(), lr=0.00001)
epochs = 30
time0 = time()

for e_no in range(1, epochs+1):
    running_loss = 0
    batch_no = 0
    correct = 0 
    total = 0
    for images, labels in train_loader:
      if torch.cuda.is_available():
          images=Variable(images.cuda())
          labels=Variable(labels.cuda())
      batch_no += 1
      model.train()
      images = images.flatten(start_dim=1)
      optimizer.zero_grad()
      output = model(images)
      _, output_index = output.topk(1)
      if torch.cuda.is_available():
        result = labels.cpu().numpy() == output_index.cpu().numpy().reshape(-1,)
        #print("executing in cuda")
      else:
        result = labels.numpy() == output_index.numpy().reshape(-1,)
      correct += result.sum()
      total += len(labels)
      loss = criterion(output, labels)
      loss.backward()
      optimizer.step()
      running_loss += loss.item()
    else:
      print("Epoch {} - Training Loss: {}".format(e_no, running_loss/len(train_loader)))
      print(f"Training Accuracy: {(correct/total) * 100}")
      print("Training Time in Minute=",(time()-time0)/60)
      model.eval()
      correct = 0
      total = 0
      for val_images, vlabels in test_loader:
        if torch.cuda.is_available():
          val_images = Variable(val_images.cuda())
          vlabels = Variable(vlabels.cuda())
        val_images = val_images.flatten(start_dim=1)
        val_output = model(val_images)
        _, output_idx = val_output.topk(1)
        if torch.cuda.is_available():
          res = vlabels.cpu().numpy() == output_idx.cpu().numpy().reshape(-1,)
        else:
          res = vlabels.numpy() == output_idx.numpy().reshape(-1,)
        correct += res.sum()
        total += len(vlabels)
            
      print(f"Validation Accuracy: {(correct * 100) / total}\n")
class Cifer_CNN(nn.Module):
    def __init__(self):
        super(Cifer_CNN,self).__init__()
        layer1=nn.Conv2d(in_channels=3, out_channels=12, kernel_size=3, padding=1, stride=1)
        layer2=nn.Conv2d(in_channels=12, out_channels=32, kernel_size=3, padding=1, stride=1)
        layer3=nn.Conv2d(in_channels=32, out_channels=64, kernel_size=3, padding=1, stride=1)
        layer4=nn.Conv2d(in_channels=64, out_channels=128, kernel_size=3, padding=1, stride=1)
        layer5=nn.Conv2d(in_channels=128, out_channels=256, kernel_size=3, padding=1, stride=1)
        layer6=nn.Conv2d(in_channels=256, out_channels=512, kernel_size=3, padding=1, stride=1)
        linear=nn.Linear(131072,1024)
        final=nn.Linear(1024,6)
        maxpool=nn.MaxPool2d(kernel_size=2)
        relu=nn.ReLU()
        batch_norm1=nn.BatchNorm2d(12)
        batch_norm2=nn.BatchNorm2d(32)
        batch_norm3=nn.BatchNorm2d(64)
        batch_norm4=nn.BatchNorm2d(128)
        batch_norm5=nn.BatchNorm2d(256)
        batch_norm6=nn.BatchNorm2d(512)
    def forward(self, data):
        mtx1 = self.relu(func.batchnorm1(self.layer1(data)))
        mtx1 = maxpool(mtx1)
        mtx1 = self.relu(func.batchnorm2(self.layer2(mtx1)))
        mtx1 = self.relu(func.batchnorm3(self.layer3(mtx1)))
        mtx1 = self.relu(func.batchnorm4(self.layer4(mtx1)))
        mtx1 = self.relu(func.batchnorm5(self.layer5(mtx1)))
        mtx1 = self.relu(func.batchnorm6(self.layer6(mtx1)))
        mtx1 = torch.flatten(mtx1, start_dim=1)
        mtx1 = func.relu(self.linear(mtx1))
        mtx1 = self.Final(mtx1)
        return mtx1
criterion1 = nn.CrossEntropyLoss()
model1 = Cifer_CNN().to(device)
optimizer1 = optim.Adam(model.parameters(), lr=0.001,weight_decay=0.0001)
epochs = 15
time0 = time()

for e_no in range(1, epochs+1):
    running_loss = 0
    batch_no = 0
    correct = 0 
    total = 0
    for images, labels in train_loader:
      if torch.cuda.is_available():
        images=Variable(images.cuda())
        labels=Variable(labels.cuda())
      batch_no += 1
      model1.train()
      #images = images.flatten(start_dim=1)
      optimizer1.zero_grad()
      output = model(images)
      _, output_index = output.topk(1)
      if torch.cuda.is_available():
        result = labels.cpu().numpy() == output_index.cpu().numpy().reshape(-1,)
      else:
        result = labels.numpy() == output_index.numpy().reshape(-1,)
      correct += result.sum()
      total += len(labels)
      loss = criterion1(output, labels)
      loss.backward()
      optimizer1.step()
      running_loss += loss.item()
    else:
        print("Epoch {} - Training Loss: {}".format(e_no, running_loss/len(train_loader)))
        print(f"Training Accuracy: {(correct/total) * 100}")
        print("Training Time in Minute=",(time()-time0)/60)
        model1.eval()
        correct = 0
        total = 0
        for val_images, vlabels in test_loader:
          if torch.cuda.is_available():
            val_images = Variable(val_images.cuda())
            vlabels = Variable(vlabels.cuda())
          val_images = val_images.flatten(start_dim=1)
          val_output = model(val_images)
          _, output_idx = val_output.topk(1)
          res = vlabels.cpu().numpy() == output_idx.cpu().numpy().reshape(-1,)
          correct += res.sum()
          total += len(vlabels)
            
        print(f"Validation Accuracy: {(correct * 100) / total}\n")
def get_dataset(dataset_dir): 
    train_x = [] 
    train_y = []
    directories=os.listdir(dataset_dir)
    for dir in directories:
      for file in os.scandir(os.path.join(dataset_dir,dir)):
        img_path=os.path.join(os.path.join(dataset_dir,dir),file)
        img=cv2.imread(img_path)
        img=np.array(img)
        train_x.append(img.flatten())
        train_y.append(dir)
    train_x = np.array(train_x)
    train_y = np.array(train_y)
    return train_x, train_y
X_train, y_train = get_dataset(os.path.join(root_dir,'train'))
print(X_train.shape)
print(y_train.shape)
X_val, y_val = get_dataset(os.path.join(root_dir,'test'))
print(X_val.shape)
print(y_val.shape)
pca = PCA(n_components = 100)
pca_train=pca.fit_transform(X_train)
x_train=pca_train
pca_val=pca.fit_transform(X_val)
x_val=pca_val
x_train.shape
poly_svc = SVC(kernel='poly')
poly_svc.fit(x_train, y_train)
accuracy_poly = poly_svc.score(x_val, y_val)
print("Polynomial SVM Accuracy: ", accuracy_poly * 100, "%")


