library(neuralnet)

# 1. Создание исходных данных
mydata <- data.frame(
  input_1 = c(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10),
  input_2 = c(0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100),  # Второй входной вектор (возведение во вторую степень)
  output = c(0, 2, 6, 12, 20, 30, 42, 56, 72, 90, 110)  # Выходные данные
)

# Просмотр структуры данных
attach(mydata)
names(mydata)

# Обучение модели на основе входных данных (input_1 и input_2)
model <- neuralnet(formula = output ~ input_1 + input_2, 
                   data = mydata, 
                   hidden = c(5, 3),  # Два скрытых слоя с 5 и 3 нейронами
                   threshold = 0.01)  # Порог для сходимости

# Печать модели
print(model)

# Построение графика модели
plot(model)

# Проверка результатов - фактические и предсказанные
final_output = cbind(input_1, input_2, output, as.data.frame(model$net.result))
colnames(final_output) = c("input_1", "input_2", "expected output", "neural net output")

print(final_output)
