import random

# importing sklearn libraries
from sklearn import neural_network, linear_model, preprocessing, svm, tree
from sklearn.ensemble import RandomForestRegressor, RandomForestClassifier
from sklearn.model_selection import train_test_split

#Next, we will divide the data into train and test split. The following code will split the dataset into 70% training data and 30% of testing data 
train_x, test_x, train_y, test_y = train_test_split(attribute_list, area_values, test_size=0.3, random_state = 9)
mse_values = []
variance_score = []

#To check predicted values for different test values
def print_values(test, predicted):
    print("The actual output and the predicted output are:")
    
    for value in range(0, len(predicted_y)):
        print('%.4f' % test_y[value], " ", '%.4f' % predicted_y[value])
 
#Random Forest Algorithm
random_forest = RandomForestRegressor() #RandomForestRegressor() function initalization 
random_forest.fit(train_x, train_y) #Model Fitting
predicted_y = random_forest.predict(test_x) #Stroring of predicted values 

print("Mean squared error: ", mean_squared_error(test_y, predicted_y)) #Print Mean squared error
print('Variance score: %.2f' % r2_score(test_y, predicted_y)) #Print Variance score

mse_values.append(mean_squared_error(test_y, predicted_y))
variance_score.append(r2_score(test_y, predicted_y))

#print_values(test_y, predicted_y)
