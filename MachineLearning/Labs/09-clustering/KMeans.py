import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from copy import deepcopy
from sklearn.decomposition import PCA
from sklearn.preprocessing import MinMaxScaler

EPS = 0.001
INF = 10000000
MAX_ITERATIONS = 100
COLORS = ["r", "g", "b", "c", "m", "y", "k"]

def min_index(k, feature, mean):
    return np.argmin([np.linalg.norm(feature - mean[i]) for i in range(k)])

def k_means(k, data):
    mean = [data[np.random.randint(0, data.shape[0])] for i in range(k)]

    for j in range(MAX_ITERATIONS):
        clasters = [[] for i in range(k)]

        for feature in data:
            clasters[min_index(k, feature, mean)].append(feature)

        prev_mean = deepcopy(mean)
        for i in range(k):
            mean[i] = np.average(clasters[i], axis=0)

        is_final = True
        for i in range(k):
            if np.linalg.norm(mean[i] - prev_mean[i]) > EPS:
                is_final = False

        if is_final:
            break

    return [min_index(k, feature, mean) for feature in data]

data = pd.read_csv('dataset_191_wine.csv')
x = data[data.columns[1:]]
y = data.loc[:, 'class']

x_norm = MinMaxScaler(copy=True).fit_transform(x)
x_pca = PCA(n_components=2).fit_transform(x_norm)

def display_clusters(labels, title):
    unique_labels = np.unique(labels)
    for i in range(len(unique_labels)):
        label = unique_labels[i]
        xs = x_pca[labels == label, 0]
        ys = x_pca[labels == label, 1]
        plt.scatter(xs, ys, color=COLORS[i], alpha=0.5, label=label)
    plt.title(title)
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.legend()
    plt.show()

def display_metric(ys, title):
    xs = [i + 1 for i in range(len(ys))]
    plt.scatter(xs, ys)
    plt.plot(xs, ys)
    plt.title(title)
    plt.xlabel('K')
    plt.ylabel('metric')
    plt.show()

def rand_index(y_real, y_predicted):
    TP, FN, FP, TN = 0, 0, 0, 0
    for i in range(len(y_real)):
        for j in range(len(y_predicted)):
            res1 = y_real[i] == y_real[j]
            res2 = y_predicted[i] == y_predicted[j]
            if res1 and res2:
                TP += 1
            elif res1 and not res2:
                FP += 1
            elif not res1 and res2:
                TN += 1
            elif not res1 and not res2:
                FN += 1

    return (TP + FN) / (TP + TN + FP + FN)

def group_by_clasters(y):
    clasters = [[] for i in range(max(y) + 1)]
    for i in range(len(y)):
        clasters[y[i]].append(i)

    return clasters

def min_separation(x, clusters):
    value = INF
    min_distance = value
    for i in range(len(clusters)):
        for j in range(len(clusters)):
            if i != j:
                for first in clusters[i]:
                    for second in clusters[j]:
                        distance = np.linalg.norm(x[first] - x[second])
                        if distance < min_distance:
                            min_distance = distance

    return min_distance if min_distance != value else 0

def max_diameter(x, clusters):
    max_distance = 0
    for i in range(len(clusters)):
        for first in clusters[i]:
            for second in clusters[i]:
                distance = np.linalg.norm(x[first] - x[second])
                if first != second and distance > max_distance:
                    max_distance = distance

    return max_distance

def dunn_index(x, y):
    clusters = group_by_clasters(y)
    min_sep = min_separation(x, clusters)
    max_diam = max_diameter(x, clusters)

    return min_sep / max_diam if min_sep != 0 else 0

display_clusters(y, 'real labels')

rand_indices = []
dunn_indices = []

for i in range(len(COLORS)):
    y_predicted = k_means(i + 1, x_norm)
    rand_indices.append(rand_index(y, y_predicted))
    dunn_indices.append(dunn_index(x_norm, y_predicted))
    display_clusters(y_predicted, f'K = {i + 1}')

display_metric(rand_indices, 'rand indices')
display_metric(dunn_indices, 'dunn indices')
