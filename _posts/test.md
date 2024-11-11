layout	title	subtitle	cover-img	thumbnail-img	share-img	tags
post
CIRAT10 dataset 사용법
dataset
/assets/img/path.jpg
/assets/img/thumb.png
/assets/img/path.jpg
books
test
'''py import torch from torchvision import transforms, datasets

BATCH_SIZE = 32 train_dataset = datasets.CIFAR10(root="./data/", train=True, download=True, transform=transforms.ToTensor())

test_dataset = datasets.CIFAR10(root="./data/", train=False, download=True, transform=transforms.ToTensor())

train_loader = torch.utils.data.DataLoader(dataset=train_dataset, batch_size=BATCH_SIZE, shuffle=True)

test_loader = torch.utils.data.DataLoader(dataset=test_dataset, batch_size=BATCH_SIZE, shuffle=False) '''
