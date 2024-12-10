#___________ Классификация IRIS набора данных________________________________________________________________

# 1. Загрузка и вызов необходимых пакетов 

library(caret)
library(tidyr)

# 2.Загрузка набора данных

data(iris)
iris.dataset <-iris
View(iris.dataset)

# 3. разбиене данных в training set and testing set

# Разбиение данных на 80% training и 20% testing
index <- createDataPartition(iris.dataset$Species, p=0.80, list=FALSE)
testset <- iris.dataset[-index,]
trainset <- iris.dataset[index,]

# 4. Машинное обучение

# 4.1 Decision Tree Classifiers
model.rpart <- train(Species ~., method = "rpart", data=trainset)
print(model.rpart)
# просмор classification tree 
plot(model.rpart$finalModel)
text(model.rpart$finalModel)

# Проверка точности с помощю confusion
confusionMatrix(predict(object = model.rpart$finalModel,newdata = trainset[,1:4],type="class"),trainset$Species)

# Проверка точности на test dataset
confusionMatrix(predict(object = model.rpart$finalModel, newdata = testset[,1:4], type="class"),testset$Species)

# 4.2 Random Forest Algorithm похож на Decision Tree Classifiers
model.rf <- train(Species ~., method = "rf", data=trainset)
print(model.rf)

plot(model.rf$finalModel)

# Проверка точности с помощю confusion
confusionMatrix(predict(object = model.rf$finalModel,newdata = trainset[,1:4],type="class"),trainset$Species)

# Проверка точности на test dataset
confusionMatrix(predict(object = model.rf$finalModel, newdata = testset[,1:4], type="class"),testset$Species)

#################################################################################################################
#___________ Кластеризация IRIS набора данных________________________________________________________________

# 4.3. K Means Clustering Model

# 1.Загрузка набора данных

data(iris)
iris.dataset <-iris
View(iris.dataset)

# применение k-means clustering model
irisCluster <- kmeans(iris.dataset[, 1:4], centers = 3, nstart = 20)
irisCluster

# проверка точности
table(irisCluster$cluster, iris$Species)

# построение кластеров и их центроидов
plot(iris[c("Sepal.Length", "Sepal.Width")], col=irisCluster$cluster)
points(irisCluster$centers[,c("Sepal.Length", "Sepal.Width")], col=1:3, pch=8, cex=2)
