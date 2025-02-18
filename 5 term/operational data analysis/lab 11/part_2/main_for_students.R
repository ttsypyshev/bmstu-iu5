
library("ggplot2")

# 2.1 Построение scatter plot
##############################################
# Использовать базовую функцию plot()
View(mtcars)
plot(mtcars$hp, mtcars$cyl)

# Использовать функцию ggplot
ggplot(mtcars, aes(x=hp, y=cyl)) + geom_point()
###############################################


# 2.2 Построение a Line Graph
########################################################
# add points and/or multiple lines
plot(pressure$temperature, pressure$pressure, type="l")
points(pressure$temperature, pressure$pressure)
lines(pressure$temperature, pressure$pressure/2, col="red")
points(pressure$temperature, pressure$pressure/2, col="red")

#Using ggplot2 if two vectors are already in the same data frame
ggplot(pressure, aes(x=temperature, y=pressure)) + geom_line() + geom_point()
#####################################################################


#2.3 Creating a Bar Graph
####################################################################
# Using barplot()
barplot(BOD$demand, names.arg=BOD$Time)

# Using ggplot2 If the vector is in a data frame
# Bar graph of values. This uses the BOD data frame, with the
#"Time" column for x values and the "demand" column for y values.
ggplot(BOD, aes(x=Time, y=demand)) + geom_bar(stat="identity")
##################################################################


# 2.4 Creating a Histogram
##################################################################
# Using hist()
hist(mtcars$mpg)
# Specify approximate number of bins with breaks
hist(mtcars$mpg, breaks=10)

ggplot(mtcars, aes(x=mpg)) + geom_histogram(binwidth=4)
##################################################################


# 2.5 Creating a Box Plot
####################################################################
# Using plot()
plot(ToothGrowth$supp, ToothGrowth$len)

# If the two vectors are in the same data frame
# Formula syntax
boxplot(len ~ supp, data = ToothGrowth)
# Put interaction of two variables on x-axis
boxplot(len ~ supp + dose, data = ToothGrowth)

# Пример 1. Создание базового Box Plot с использованием ggplot2
# Если у вас есть набор данных, например, ToothGrowth, и вы хотите построить Box Plot для переменной len по группам supp, то код будет следующим:
# Создаем Box Plot для переменной 'len' по группам 'supp' в данных ToothGrowth
ggplot(ToothGrowth, aes(x = supp, y = len)) +
  geom_boxplot() +
  labs(title = "Box Plot of ToothGrowth Length by Supplement", 
       x = "Supplement Type", 
       y = "Tooth Length")

# Пример 2. Добавление второго фактора, например, переменной dose
# Чтобы добавить второй фактор, например, dose, на ось x, и увидеть взаимодействие между переменными, можно использовать следующий код:
# Box Plot с двумя факторами: 'supp' и 'dose'
ggplot(ToothGrowth, aes(x = interaction(supp, dose), y = len)) +
  geom_boxplot() +
  labs(title = "Box Plot of ToothGrowth Length by Supplement and Dose", 
       x = "Supplement and Dose", 
       y = "Tooth Length")

# Здесь функция interaction(supp, dose) создает комбинацию значений двух факторов на оси x, что позволяет визуализировать их взаимодействие.

# Пример 3. Создание диаграммы с цветовой кодировкой
# Вы можете также добавить цветовую кодировку для различных уровней факторов, например, для supp:
# Box Plot с цветовой кодировкой по 'supp'
ggplot(ToothGrowth, aes(x = supp, y = len, fill = supp)) +
  geom_boxplot() +
  labs(title = "Box Plot of ToothGrowth Length by Supplement", 
       x = "Supplement Type", 
       y = "Tooth Length") +
  scale_fill_manual(values = c("orange", "blue"))

# Здесь добавлена настройка цветов для различных типов supp с использованием scale_fill_manual().

# Пример 4. Настройка внешнего вида и добавление дополнительных элементов
# Для того чтобы улучшить визуализацию, можно добавить горизонтальные линии, отобразить медиану и настроить внешний вид диаграммы:
ggplot(ToothGrowth, aes(x = supp, y = len, fill = supp)) +
  geom_boxplot(outlier.shape = 1, outlier.colour = "red") +  # выделяем выбросы
  geom_jitter(width = 0.2, shape = 16, colour = "black") +  # добавление точек
  labs(title = "Box Plot of ToothGrowth Length by Supplement", 
       x = "Supplement Type", 
       y = "Tooth Length") +
  theme_minimal()  # использование минималистичной темы

# В этом примере добавляются точки, чтобы увидеть отдельные наблюдения (с помощью geom_jitter()) и выделяются выбросы красным цветом.

# Пример 5. Визуализация Box Plot с множественными группами (например, по обеим переменным)
# Если вы хотите строить график для нескольких групп одновременно, то можно просто использовать несколько уровней на оси x:
# Box Plot для 'supp' и 'dose' в одном графике
ggplot(ToothGrowth, aes(x = supp, y = len, fill = factor(dose))) +
  geom_boxplot() +
  labs(title = "Box Plot of ToothGrowth Length by Supplement and Dose", 
       x = "Supplement Type", 
       y = "Tooth Length") +
  scale_fill_manual(values = c("lightgreen", "purple", "pink"))

# Здесь мы используем переменную dose для цветовой кодировки (с помощью fill = factor(dose)).

####################################################################

