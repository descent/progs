import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import SGDRegressor
import random
from sklearn.preprocessing import MinMaxScaler

# prepare data
test_subset = pd.read_csv('raw/TestSubset.csv')
train_subset = pd.read_csv('raw/TrainingSubset.csv')

train = train_subset.drop(['EbayID','Price','SellerName'],axis=1)
train_target = train_subset['Price']

scaler = MinMaxScaler()
train = scaler.fit_transform(train)
n_trainSamples, n_features = train.shape

# ploting example from scikit-learn
def plot_learning(clf,title):

    plt.figure()
    validationScore = []
    trainScore = []
    mini_batch = 500
    # define the shuffle index
    ind = list(range(n_trainSamples))
    random.shuffle(ind)

    for idx in range(int(np.ceil(n_trainSamples / mini_batch))):
        x_batch = train[ind[idx * mini_batch: min((idx + 1) * mini_batch, n_trainSamples)]]
        y_batch = train_target[ind[idx * mini_batch: min((idx + 1) * mini_batch, n_trainSamples)]]

        if idx > 0:
            validationScore.append(clf.score(x_batch, y_batch))
        clf.partial_fit(x_batch, y_batch)
        if idx > 0:
            trainScore.append(clf.score(x_batch, y_batch))

    plt.plot(trainScore, label="train score")
    plt.plot(validationScore, label="validation socre")
    plt.xlabel("Mini_batch")
    plt.ylabel("Score")
    plt.legend(loc='best')
    plt.title(title)

sgd_regresor = SGDRegressor(penalty='l2',alpha=0.001)
plot_learning(sgd_regresor,"SGDRegressor")

test = test_subset.drop(['EbayID','Price','SellerName'], axis=1)
test = scaler.fit_transform(test)
test_target = test_subset['Price']

print("SGD regressor prediction result on testing data: %f" % sgd_regresor.score(test,test_target))

plt.show()


