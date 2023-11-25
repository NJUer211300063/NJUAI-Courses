import random
import csv
import numpy as np
import math
from sklearn.preprocessing import normalize
from sklearn.metrics import roc_curve, auc, accuracy_score
import matplotlib.pyplot as plt
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline


def set_seed(seed):
    random.seed(seed)
    np.random.seed(seed)


def GenerateData(data_path):
    with open(data_path, "r", encoding="utf-8") as f:
        data = np.array(list(csv.reader(f))[1:])
    N = data.shape[0]
    X = data[:, :-1].astype(np.float64)
    X = normalize(X, axis=0, norm="max")  # avoid overflow problem

    y = data[:, -1].astype(np.int32).reshape(N, 1)
    test_id = np.random.choice(N, int(0.3 * N), replace=False)
    X_train = np.delete(X, test_id, axis=0)
    y_train = np.delete(y, test_id, axis=0)
    X_test = X[test_id]
    y_test = y[test_id]
    print("Dimension of the feature data in training set:", X_train.shape)
    print("Dimension of the feature data in testing set:", X_test.shape)
    return X_train, y_train, X_test, y_test


model_name = ["Logistic Regression", "Decision Tree", "SVM"]
colors = ['red',
          'green',
          'blue',
          ]


def PlotROCs(y_prob_lr, y_prob_tree, y_prob_svm, y_test):
    # %%
    # TODO: Plot the ROCs in one graph
    auc_arr = []
    plt.figure()
    for y_prod, name, color in zip((y_prob_lr, y_prob_tree, y_prob_svm), model_name, colors):
        fpr, tpr, _ = roc_curve(y_test, y_prod)
        roc_auc = auc(fpr, tpr)
        auc_arr.append(roc_auc)
        plt.plot(fpr, tpr, color=color, label="%s (AUC = %0.4f)" % (name, roc_auc))

    plt.plot([0, 1], [0, 1], color="navy", lw=2, linestyle="--")
    plt.xlim([0.0, 1.0])
    plt.ylim([0.0, 1.05])
    plt.xlabel("FPR")
    plt.ylabel("TPR")
    plt.title("ROC Curve")
    plt.legend()
    plt.show()
    return auc_arr
    # %%


def main(data_path):
    (X_train, y_train, X_test, y_test,) = GenerateData(data_path)
    # %%
    # TODO: Plot the ROCs in one graph

    lr_model = LogisticRegression()
    lr_model.fit(X_train, y_train.ravel())

    tree_model = DecisionTreeClassifier(criterion="gini", max_depth=6, random_state=100)
    tree_model.fit(X_train, y_train.ravel())

    svm_model = SVC(gamma="scale", kernel="rbf", probability=True)
    svm_model.fit(X_train, y_train.ravel())

    # predicted probability on test set using logistic regression model

    y_prob_lr = lr_model.predict_proba(X_test)[:, 1]
    print("Logistic Regression: Accuracy in test set: %.4f" % lr_model.score(X_test, y_test))
    print("Logistic Regression: Accuracy in train set: %.4f" % lr_model.score(X_train, y_train))

    # predicted probability on test set using tree model
    y_prob_tree = tree_model.predict_proba(X_test)[:, 1]
    print("Decision Tree: Accuracy in test set: %.4f" % tree_model.score(X_test, y_test))
    print("Decision Tree: Accuracy in train set: %.4f" % tree_model.score(X_train, y_train))

    # predicted probability on test set using svm model
    y_prob_svm = svm_model.predict_proba(X_test)[:, 1]
    print("SVM: Accuracy in test set: %.4f" % svm_model.score(X_test, y_test))
    print("SVM: Accuracy in train set: %.4f" % svm_model.score(X_train, y_train))
    # %%

    aucs = PlotROCs(y_prob_lr, y_prob_tree, y_prob_svm, y_test)

    for auc, name in zip(aucs, model_name):
        print("%s: AUC in test set: %.4f" % (name, auc))


if __name__ == "__main__":
    set_seed(6)
    data_path = "data.csv"
    main(data_path)
