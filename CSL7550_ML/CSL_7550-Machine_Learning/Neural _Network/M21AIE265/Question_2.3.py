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
transform=transforms.Compose([transforms.Grayscale(),
                             transforms.ToTensor()])
path=os.getcwd()
train_dataset = datasets.ImageFolder(os.path.join(path,'train'), transform=transform)
test_dataset = datasets.ImageFolder(os.path.join(path,'val'), transform=transform)
train_set, val_set = torch.utils.data.random_split(train_dataset, [895, 100])
#train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)
train_loader = DataLoader(train_set, batch_size=64, shuffle=True)
val_loader = DataLoader(val_set, batch_size=64, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=64, shuffle=True)
dataiter = iter(train_loader)
images, labels = dataiter.next()
print(images.shape)
print(labels.shape)
class Gurumukhi(nn.Module):
    def __init__(self):
        super(Gurumukhi,self).__init__()
        self.layer1 = nn.Linear(1024,512)
        self.layer2 = nn.Linear(512,256)
        self.Final = nn.Linear(256,10)
        self.relu = nn.ReLU()
        self.logsoftmax = nn.LogSoftmax()
    def forward(self, data):
        mtx = torch.flatten(data, start_dim=1)
        mtx = self.layer1(mtx)
        mtx = self.relu(mtx)
        mtx = self.layer2(mtx)
        mtx = self.relu(mtx)
        mtx = self.Final(mtx)
        mtx = self.logsoftmax(mtx)
        return mtx
criterion = nn.NLLLoss()
model = Gurumukhi()
optimizer = optim.SGD(model.parameters(), lr=0.012, momentum=0.9)
epochs = 25
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