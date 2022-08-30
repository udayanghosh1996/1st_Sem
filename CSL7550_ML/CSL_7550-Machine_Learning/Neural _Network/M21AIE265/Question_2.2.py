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
transform=transforms.Compose([transforms.ToTensor()])
path=os.getcwd()
trainset = datasets.MNIST(os.path.join(path,'Train'), download=True, train=True, transform=transform)
valset = datasets.MNIST(os.path.join(path,'Train'), download=True, train=False, transform=transform)
train_loader = torch.utils.data.DataLoader(trainset, batch_size=64, shuffle=True)
val_loader = torch.utils.data.DataLoader(valset, batch_size=64, shuffle=True)
dataiter = iter(train_loader)
images, labels = dataiter.next()
print(images.shape)
print(labels.shape)
class Mnist(nn.Module):
    def __init__(self):
        super(Mnist,self).__init__()
        self.layer1 = nn.Linear(784,392)
        self.layer2 = nn.Linear(392,196)
        self.Final = nn.Linear(196,10)
        self.relu = nn.ReLU()
        self.softmax = nn.Softmax()
    def forward(self, data):
        mtx = torch.flatten(data, start_dim=1)
        mtx = self.layer1(mtx)
        mtx = self.relu(mtx)
        mtx = self.layer2(mtx)
        mtx = self.relu(mtx)
        mtx = self.Final(mtx)
        #mtx = self.softmax(mtx)
        return mtx
criterion = nn.CrossEntropyLoss()
model = Mnist()
optimizer = optim.SGD(model.parameters(), lr=0.0014, momentum=0.9)
epochs = 30
time0 = time()

for e_no in range(1, epochs+1):
    running_loss = 0
    batch_no = 0
    correct = 0 
    total = 0
    for images, labels in train_loader:
        batch_no += 1
        model.train()
        images = images.flatten(start_dim=1)
        optimizer.zero_grad()
        output = model(images)
        _, output_index = output.topk(1)
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
        for val_images, vlabels in val_loader:
            val_images = val_images.flatten(start_dim=1)
            val_output = model(val_images)
            _, output_idx = val_output.topk(1)
            res = vlabels.numpy() == output_idx.numpy().reshape(-1,)
            correct += res.sum()
            total += len(vlabels)
            
        print(f"Validation Accuracy: {(correct * 100) / total}\n")