import pandas as pd
from pandas import DataFrame
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns


# prepare data
test_set = pd.read_csv('raw/TestSet.csv')
test_subset = pd.read_csv('raw/TestSubset.csv')
train_set = pd.read_csv('raw/TrainingSet.csv')
train_subset = pd.read_csv('raw/TrainingSubset.csv')

train = train_set.drop(['EbayID','QuantitySold','SellerName'], axis=1)
train_target = train_set['QuantitySold']
_, n_features = train.shape

df = DataFrame(np.hstack((train,train_target[:, None])), columns=range(n_features) + ["isSold"])
_ = sns.pairplot(df[:50], vars=[2,3,4,10,13], hue="isSold", size=1.5)
plt.figure(figsize=(10,10))

# compute the correlation matrix
corr = df.corr()

# generate a mask for the upper triangle
mask = np.zeros_like(corr,dtype=np.bool)
mask[np.triu_indices_from(mask)] = True

# generate a custom diverging colormap
cmap = sns.diverging_palette(220, 10, as_cmap=True)

sns.heatmap(corr, mask=mask, cmap=cmap, vmax = .3,
                square=True, xticklabels=5, yticklabels=2,
                linewidths=.5, cbar_kws={"shrink":.5})

plt.yticks(rotation=0)

plt.show()
