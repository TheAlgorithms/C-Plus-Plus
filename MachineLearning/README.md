# MachineLearning C++ Library

A self-contained machine learning toolkit implemented from scratch in C++17 using only STL, Eigen, and optional OpenMP.

## Highlights
- Supervised learning: linear/logistic regression, trees, random forest, SVM, KNN, Naive Bayes, gradient boosting, MLP.
- Unsupervised learning: k-means, DBSCAN, agglomerative clustering, PCA, autoencoder, GMM.
- Reinforcement learning: tabular Q-learning, SARSA, DQN-style approximator, REINFORCE policy gradient.
- Shared utilities for metrics, activations, preprocessing, and CSV loading.

## Build
```bash
cmake -S MachineLearning -B build_ml
cmake --build build_ml -j
```

Each algorithm has a dedicated `demo.cpp` executable.
